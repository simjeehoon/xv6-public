xv6에 SSU Scheduler 추가
===

xv6에 SSU Scheduler를 추가하여 스케줄링을 더 효율적으로 개선한다.


## 개요
 xv6에 가중치(weight)와 우선순위(priority)를 이용하여 다음 프로세스를 결정하는 SSU Scheduler를 구현한다. 그 후 스케쥴링 함수의 동작 과정을 확인하기 위해 sdebug 명령어와 디버깅 기능을 xv6에 추가한다.

## 상세 설계 및 구현 과정

```
이번 작업에서 수정한 소스 코드에는 주석에 [os-prj3]를 붙여 달았다.
```

### xv6에 SSU Scheduler를 추가하는 과정

 xv6에서 프로세스는 proc 구조체에 의해 관리된다.

#### `proc.h` 의 `struct proc`
```c
// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

  unsigned long priority;	   // [os-prj3] priority variable for scheduling
  unsigned long weight;				   // [os-prj3] weight variable for scheduling
};
```

#### `proc.c` 의 `ptable`
```c
struct {
  struct spinlock lock;
  struct proc proc[NPROC];
  unsigned long minpriority;			// [os-prj3] min priority for new process
} ptable;
```

 * `proc` 구조체는 프로세스에 대한 여러 가지 정보들이 담겨있다. `proc` 구조체 변수들은 배열의 형태로 `ptable`에 담긴다. 
 
 * 결국 처음에는 `NPROC` 개수만큼의, 상태가 `UNUSED`인 `proc` 구조체 변수가 생기게 된다. 이 `ptable`은 전역 변수이고, 동시에 여러 곳에서 접근하므로 `acquire(&ptable.lock)` 및 `require(&ptable.lock)`을 이용해 접근을 제한해야 한다.
 
 * SSU Scheduler에서 모든 프로세스는 각자의 가중치(`weight`)와 우선순위(`priority`)를 가지므로 이에 해당하는 변수를 `proc` 구조체에 추가하였다.
 
 * 또한 프로세스 생성 또는 wake up시 `proc`의 `priority`에 할당할 가장 작은 `priority` 값을 `ptable`의 `minpriority` 변수로 추가하였다.

---


#### `proc.c`의 `allocproc`
```c
//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
  p->weight = nextweight++; // [os-prj3] Set weight
  p->priority = ptable.minpriority; // [os-prj3] Set min priority

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}
 ```

 
 `allocproc()`은 `ptable`의 `proc` 배열에서 상태가 `UNUSED`인 것을 하나 골라 `EMBRYO`로 바꾼다. 그 후 이것을 커널에서 요구하는 상태로 바꿔서 프로세스를 반환한다. `allocproc`은 `fork`를 수행할 때, `userinit`을 이용하여 최초의 프로세스를 생성할 때 사용된다.

---
#### `proc.c`의 전역변수 `nextweight`
```c 
int nextpid = 1;
unsigned long nextweight = 1;  // [os-prj3] weight value for new process
extern void forkret(void);
```

 SSU Scheduler의 구현을 위해 전역변수 `nextweight`을 추가하고 1로 할당하였다. 수정한 `allocproc`에서는 이 `nextweight`과 `ptable.minpriority`를 새로운 프로세스에 할당한다. 이후 `nextweight`은 1을 증가시킨다.

---
#### `proc.c`의 `userinit`
```c
//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  acquire(&ptable.lock); 
  ptable.minpriority = 3; // [os-prj3] Set minpriority
  release(&ptable.lock);

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
}
```


`userinit`은 `allocproc`으로 `proc`을 할당받고, 최초의 유저 프로세스 `initcode`를 실행한다. `initcode`는 `init`을 생성하고, `init`은 `sh`을 생성하게 된다. 최초의 유저 프로세스는 `priority` 값이 3이어야 하므로, 그림과 같이 `ptable.minpriority`를 3으로 할당하는 코드를 추가하였다.

---
#### `proc.c`의 `wakeup1`
```c
//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan){
	  p->priority = ptable.minpriority;	// [os-prj3] Set priority to min priority.
      p->state = RUNNABLE;
	}
}
```

 wake up시에도 `priority`를 가장 작은 값으로 할당해야 하기 때문에 `wakeup1`을 수정하였다. 왼쪽 사진은 원래의 `wakeup1`이고, 오른쪽 사진은 가장 작은 `priority`값을 할당하는 코드를 추가한 사진이다. `wakeup1`은 `wakeup`에서 `ptable`을 잠그고 호출하게 된다.

 `schduler` 관련 함수는 `scheduler`와 `sched`가 있다. 
 
 `scheduler`는 각 CPU가 자신의 설정을 마친 이후에 호출하는 함수이다. 계속 다음에 수행될 프로세스를 선택하며, 반환되지 않는다. 프로세스가 선택되면, `proc` 구조체에 담겨 있는 페이지 테이블 정보, 컨텍스트 정보를 가져와서 커널과 교환한다. 이후 CPU의 제어권은 선택된 프로세스에게 넘어간다. 선택된 프로세스를 수행하다가 적절한 인터럽트가 발생하면 다시 컨텍스트 스위칭이 일어나고, `scheduler`로 제어권이 넘어온다. 이후 커널은 다시 프로세스를 선택하고 동일한 과정을 반복한다.
 
 `sched`는 다시 `scheduler`로 진입하는 역할을 한다. `scheduler`에서 제어권을 선택된 프로세스에게 넘긴 뒤, 나중에 다시 `scheduler`로 돌아갈 때 호출된다.

---
#### `proc.c`의 `scheduler` 원본 코드
```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);

  }
}
```

기존 `scheduler`는 다음 수행될 프로세스를 순차적으로 탐색한다. 이런 경우 특정 프로세스가 집중적으로 수행되어 제어권이 공정하게 전달되지 않을 수 있다. 따라서 프로세스 선정 과정을 수정하였다.

#### 변경된 `scheduler`

```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;

  struct proc *selected; // [os-prj3] proc variable for SSU Scheduler
  unsigned long minpriority;  // [os-prj3] min priority variable for SSU Scheduler
  int updated; // [os-prj3] If ptable.minpriority is updated, this will be set 1.
  
  for(;;){
	selected = (void*)0; // [os-prj3] Set NULL to selected process pointer.
	updated = 0;  // [os-prj3] Set update to 0.
```
 프로세스 선정을 위한 `struct proc` 포인터 `selected`를 추가하였다. 또한 SSU Scheduler는 가장 작은 `priority`를 선택하는 스케줄러이므로 비교를 위한 변수 `minpriority`를 추가하였다. 그 외에 구현을 위해 `flag` 변수인 `updated`를 추가하였다.


```c
    // Enable interrupts on this processor.
    sti();
    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state == RUNNABLE){ // [os-prj3] Only select RUNNABLE process.
		/** 
		   [os-prj3] Select process which has min priority.
		 */
		if(selected == (void*)0 || minpriority > p->priority){
		  minpriority = p->priority;
		  selected = p;
		}
	  } 
	}
```

 RUNNABLE 프로세스 중 가장 작은 `priority`를 가진 프로세스를 선택하여 `selected`에 배정한다.

```c
	if(selected != (void*)0){ // [os-prj3] If process is selected

		/**
		  [os-prj3] If it's debug mode, print process id, name, weight, priority.
		  */
#ifdef DEBUG
		cprintf("PID: %d, NAME: %s, WEIGHT: %d, PRIORITY: ",
				selected->pid, selected->name, selected->weight);
		printul(selected->priority);
		cprintf("\n");
#endif

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = selected; // [os-prj3] Set selected process.
      switchuvm(selected); // [os-prj3] Switch to selected process.
      selected->state = RUNNING; // [os-prj3] Set state to RUNNING.

      swtch(&(c->scheduler), selected->context); // [os-prj3] context switching.
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.

	  // [os-prj3] Calculate new priority.
#define TIME_SLICE 10000000L
	  selected->priority = selected->priority + (TIME_SLICE / selected->weight);

	  /** 
		 [os-prj3] Search min priority.
		 */
	  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
		if(p->state == RUNNABLE){ 
		  if(!updated || minpriority > p->priority){
			updated = 1; // [os-prj3] Set update to 1.
			minpriority = p->priority;
		  }
		}
	  }
	  if(updated){ // [os-prj3] Renew ptable.minpriority.
		ptable.minpriority = minpriority;
	  }

      c->proc = 0;
    }
    release(&ptable.lock);
  }
}
```
 만일 `selected`에 프로세스가 배정되었다면, 사전 작업을 수행하고 해당 프로세스에 제어권을 전달한다. 이후 다시 `scheduler`로 복귀하였다면 수행한 프로세스의 `priority`를 갱신한다. 이후 최소 `priority`를 검색하고 `ptable.minpriority`에 저장한다.

--- 

 ```Makefile
 ifndef CPUS
# [os-prj3] change cpus to 1 for ssu scheduler
CPUS := 1
endif
 ```

최종적으로 스케줄링 함수의 동작 과정을 잘 살펴보기 위해 `Makefile`에서 `CPUS`를 1로 수정하였다.

---
### 스케줄링 과정 확인을 위해 `sdebug` 명령어를 추가

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj3/image02.png?raw=true" title="image02.png" alt="image02.png"></img><br/>
</center>

 * `sdebug`의 flow chart는 위와 같다. 
 * 반복문을 이용하여 `PNUM`만큼 프로세스를 만든다. 
 * 생성된 자식 프로세스는 `weightset` 시스템콜로 프로세스의 가중치를 임의로 설정한다. 
 * 이후 반복적으로 `counter` 변수를 증가시킨다. 변수를 `PRINT_CYCLE`만큼 증가시켰다면, 프로세스의 ID, 가중치, 출력까지 소요된 시간을 출력한다. 
 * 최종적으로 `TOTAL_COUNTER`만큼 증가시켰다면, 해당 프로세스는 종료된다. 
 * 부모 프로세스는 자식을 모두 생성했다면, `wait` 시스템콜을 이용하여 자식이 모두 종료될 때까지 기다린다.
 * 인자로 들어온 `weight`값으로 프로세스의 가중치를 결정하는 `weightset` 시스템콜을 구현하기 위해 `proc.c`에 `do_weightset` 함수를 만들었다. 구현부는 아래와 같다.

#### `proc.c`에 추가한 `do_weightset`의 구현부
```c
/**
 [os-prj3]
  This is called by system call weightset.
  Set weight in caller's proc struct to w
  */
void do_weightset(unsigned long w){
  acquire(&ptable.lock);
  struct proc *p = myproc(); 
  p->weight = w;
  release(&ptable.lock);
}
```

#### `defs.h`에 추가한 `do_weightset`의 선언

```c
void	do_weightset(unsigned long w); // [os-prj3] for weightset system call
```

 `do_weightset`은 `ptable`을 잠그고 해당 프로세스의 가중치를 인자값으로 할당한다. `sysproc.c`의 `sys_weightset`에서 이를 사용하기 때문에 `defs.h`에 선언도 추가하였다. 

 `sysproc.c`에서는 다음과 같이 `do_weightset`으로 `weight`을 설정한다. `weight`이 0 이하이면 –1을 리턴하며 작업을 중지한다.

#### `sysproc.c`의 `sys_weightset`의 구현부

```c
/**
  [os-prj3] It is used for sdebug.
  Set proc's weight to user's argument.
   */
int
sys_weightset(void)
{
  int weight;
  if(argint(0, &weight) < 0)
    return -1;
  if(weight <= 0)
	return -1; 
  do_weightset((unsigned long)weight);
  return weight;
}
```

 마지막으로 이 `weightset` 시스템콜 등록을 위한 코드들을 아래와 같이 `syscall.h`, `syscall.c`, `user.h`, `usys.S`, `Makefile`에 추가한다.


#### `syscall.c`
```c
extern int sys_weightset(void); // [os-prj3]
```
```c
[SYS_weightset]   sys_weightset, // [os-prj3]
```

#### `syscall.h`
```c
// [os-prj3] 
#define SYS_weightset 22
```

#### `user.h`
```c
int weightset(int weight); // [os-prj3] weight set sys call
```

#### `usys.S`
```c
SYSCALL(weightset)
```

#### `Makefile`
```Makefile
EXTRA=\
	mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
	ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c\
	printf.c umalloc.c\
	sdebug.c\ # <--- this
	README dot-bochsrc *.pl toc.* runoff runoff1 runoff.list\
	.gdbinit.tmpl gdbutil\
```
```Makefile
UPROGS=\
	_cat\
	_echo\
	_forktest\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_stressfs\
	_usertests\
	_wc\
	_zombie\
	_sdebug\ # <--- this
```

#### `sdebug.c`
```c
#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5
#define PRINT_CYCLE 10000000
#define TOTAL_COUNTER 500000000

void sdebug_func(void)
{
  int i;
  int pid;
  long start;
  volatile long counter = 0;

  printf(1, "start sdebug command\n");
  for(i = 1 ; i <= PNUM ; i++){
	pid = fork();
	start = uptime(); // [os-prj3] Check start time
	if(pid == 0){ // [os-prj3] Child process
	  if(weightset(i) < 0){
		printf(1, "PID:%d, weightset error\n", getpid());	
		exit();
	  } // [os-prj3] Set weight to i
	  /*
		 [os-prj3] Count PRINT_CYCLE
		 and print this process information.
	  */
	  while(counter < PRINT_CYCLE)
		++counter;
	  printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), i, (uptime()-start)*10);

	  /*
		 [os-prj3] Count TOTAL_COUNTER
		 and exit this process.
	  */
	  while(counter < TOTAL_COUNTER)
		++counter;
	  printf(1, "PID: %d terminated\n", getpid());
	  exit();
	}
	else if(pid > 0) // [os-prj3] Parent process
	  continue; // [os-prj3] Loop for making child process.
	else{ // Error
	  printf(1, "ERROR: fork\n");
	  break;
	}
  }
  for(i = 1 ; i <= PNUM ; i++) // [os-prj3] Wait childs.
	wait();

  printf(1, "end of sdebug command\n");
}

int main(void)
{
  sdebug_func();
  exit();
}

```

 flow chart와 같이 자식 프로세스를 생성하여 `weightset`으로 `weight`을 지정하고, 프로세스 정보를 출력한 뒤 종료하는 코드를 `sdebug.c`에 작성하였다. 

 ---
### 다음에 실행될 프로세스 선정 과정 디버깅 기능 구현
 `make`에서 `debug=1` 옵션을 주면 프로세스 선정 과정을 확인할 수 있는 화면이 나오도록 구현한다. 

#### `Makefile`에 디버그 코드 추가
```Makefile
# [os-prj3] debug option
ifeq ($(debug), 1)
CFLAGS += -DDEBUG
endif
```

 `Makefile`에서 `debug=1`일 때 `CFLAGS`에 `–DDEBUG`가 추가되도록 한다. 이는 컴파일할 때 코드의 처음에 `#define DEBUG`를 작성해주는 것과 같다.

#### `console.c`에 printul 구현
```c
/*
   [os-prj3] function to print unsigned long integer in cernel
   */
void
printul(unsigned long x)
{
  static char digits[] = "0123456789abcdef";
  char buf[48];
  int i = 0;
  do{
    buf[i++] = digits[x % 10];
  }while((x /= 10) != 0);

  while(--i >= 0)
    consputc(buf[i]);
}
```

#### `defs.h`에 `printul` 선언
```c
void	printul(unsigned long); // [os-prj3] for debug option
```

 `priority`를 부호 있는 integer 형식으로 출력하게 되면 오버플로우가 발생한 상태로 출력될 수 있다. 이를 방지하기 위해 `unsigned long`을 출력할 수 있는 `printul` 함수를 `console.c`에 구현한다. 이후 `defs.h`에 함수의 선언을 작성한다.

#### `proc.c`에 있는 `scheduler`에서 프로세스가 선택되었을 때 프로세스 정보를 출력
```c
if(selected != (void*)0){ // [os-prj3] If process is selected

		/**
		  [os-prj3] If it's debug mode, print process id, name, weight, priority.
		  */
#ifdef DEBUG
		cprintf("PID: %d, NAME: %s, WEIGHT: %d, PRIORITY: ",
				selected->pid, selected->name, selected->weight);
		printul(selected->priority);
		cprintf("\n");
#endif
```

 `proc.c`의 `scheduler`에서 프로세스가 선택되었을 때 해당 프로세스 정보를 출력하고, `PRIORITY`는 `printul`을 이용하여 출력한다.

## 실행 결과
#### `sdebug` 명령

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj3/image002c.png?raw=true" title="image002c.png" alt="image002c.png"></img><br/>
</center>

`sdebug` 명령이 잘 출력되는 모습을 확인할 수 있다.

#### `debug=1` 옵션 컴파일
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj3/image03.png?raw=true" title="image03.png" alt="image03.png"></img><br/>
</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj3/image002d.png?raw=true" title="image002d.png" alt="image002d.png"></img><br/>
</center>

상태가 잘 출력되는 모습을 확인할 수 있다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj3/image04.png?raw=true" title="image04.png" alt="image04.png"></img><br/>
</center>

`sdebug` 명령 수행 후에도 `priority`가 오버플로없이 잘 출력된다.