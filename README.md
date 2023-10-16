XV6 Feature Improvements
===
**XV6**는
* 미국 MIT에서 멀티프로세서 x86 및 RISC-V 시스템을 위해 개발한 교육용 운영체제이다.
* UNIX V6를 ANSI C 기반으로 구현했다.
* 리눅스나 BSD와 달리 xv6는 단순하지만 UNIX 운영체제의 중요 개념과 구성을 포함하고 있다.

XV6의 CPU 관리(스케줄링), 메모리 관리(페이징), 파일 시스템을 살펴보고, 각각에 새로운 구성요소를 추가해본다.

### 구성

본 프로젝트는 기능마다 브랜치를 만들었으므로, 기능을 조회하려면 checkout이 필요합니다.

1. [xv6 살펴보기](https://github.com/simjeehoon/xv6-public/tree/os/prj1)
2. [xv6에 시스템콜 추가하기](https://github.com/simjeehoon/xv6-public/tree/os/prj2)
3. [xv6에 SSU Scheduler를 추가하여 스케줄링을 더 효율적으로 개선](https://github.com/simjeehoon/xv6-public/tree/os/prj3)
4. [페이징 알고리즘 시뮬레이션](https://github.com/simjeehoon/page-simulator)
5. [xv6에 CS File System을 추가](https://github.com/simjeehoon/xv6-public/tree/os/prj5)

</br>

(1) xv6 살펴보기
===

xv6 운영체제를 대략적으로 살펴본다.


## 개요
 교육용 운영체제 xv6를 설치하고 컴파일하여 쉘 명령어를 추가한다. 명령어를 추가하는 과정을 통해 xv6 환경에 익숙해지도록 한다.

## 상세설계
### 1. XV6 설치 및 컴파일

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image02.png?raw=true" title="image02.png" alt="image02.png"></img><br/>

깃허브 웹페이지 화면(
                [https://github.com/mit-pdos/xv6-public](https://github.com/mit-pdos/xv6-public)
                )

</center>

 미국 MIT에서 멀티프로세서 x86 및 RISC-V 시스템을 위해 개발한 교육용 운영체제 xv6를 `git clone`으로 다운로드한다. 이후 `qemu x86` 에뮬레이터를 설치한다. 이후 `make` 명령어로 컴파일한 후 실행한다.

### 2. Helloworld 쉘 프로그램 작성
리눅스 환경에서 쉘 프로그램 `Helloworld.c`를 작성한 후 xv6상에서 동작하도록 한다.

### 3. hcat 쉘 프로그램 작성
리눅스 환경에서 기존의 `cat.c`를 복사한 후 수정하여 파일의 처음 n행만 출력하는 프로그램을 제작한다. 행 수 n과 파일 이름은 인자로 입력받는다.

### 4. 부팅 시 로그인 구현
Username과 Password가 기록된 `list.txt`를 작성한다. xv6 부팅시 Username과 Password를 입력받고, `list.txt`와 비교하여 일치하는 정보가 있을 때만 쉘 프롬프트를 출력하도록 한다.


## 구현 방법 및 결과
### 1. xv6 설치 및 컴파일
#### (1) `git clone` 명령어로 xv6를 다운로드한다.
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image03.png?raw=true" title="image03.png" alt="image03.png"></img><br/>
</center>

#### (2) `apt-get install qemu-kvm` 명령어로 qemu 에뮬레이터를 설치한다.
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image04.png?raw=true" title="image04.png" alt="image04.png"></img><br/>
</center>

#### (3) xv6 디렉토리에서 make를 이용해 컴파일한다.
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image05.png?raw=true" title="image05.png" alt="image05.png"></img><br/>
</center>

#### (4) `make qemu`를 이용하여 에뮬레이터를 실행한다.
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image06.png?raw=true" title="image06.png" alt="image06.png"></img><br/>
</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image07.png?raw=true" title="image07.png" alt="image07.png"></img><br/>
</center>

### 2. Helloworld 쉘 프로그램 작성
#### (1) xv6 디렉토리에 `helloworld.c`를 작성한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image08.png?raw=true" title="image08.png" alt="image08.png"></img><br/>
</center>

#### (2) `Makefile`의 `UPROGS`에 `_helloworld`를 추가하고 `EXTRA`에 `helloworld.c`를 추가한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image09.png?raw=true" title="image09.png" alt="image09.png"></img><br/>
</center>

#### (3) `make` 명령어를 통해 컴파일 후 실행한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image10.png?raw=true" title="image10.png" alt="image10.png"></img><br/>

`make clean` 및 `make`

</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image11.png?raw=true" title="image11.png" alt="image11.png"></img><br/>

helloworld 명령어 실행 화면

</center>

### 3. hcat 쉘 프로그램 작성
#### (1) xv6 디렉토리 내 `cat.c`를 `hcat.c`로 복사한 후 수정한다.
#### (2) `argument`에서 `atoi`로 출력할 행 수 값을 얻고 전역변수에 저장한다.
#### (3) 이 전역변수로 출력을 제한한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image12.png?raw=true" title="image12.png" alt="image12.png"></img><br/>

전역변수 `maxrow`에 출력할 행 수를 저장한다.

</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image13.png?raw=true" title="image13.png" alt="image13.png"></img><br/>

전역변수 `maxrow`를 이용하여 행 수 출력을 제한한다.

</center>

#### (4) `Makefile`의 `UPROGS`에 `_hcat`를 추가하고 `EXTRA`에 `hcat.c`를 추가한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image14.png?raw=true" title="image14.png" alt="image14.png"></img><br/>
</center>

#### (5) `make` 명령어를 통해 컴파일 후 실행한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image15a.png?raw=true" title="image15a.png" alt="image15a.png"></img><br/>
</center>

### 4. 부팅 시 로그인 구현
#### (1) `init.c`에서 `ssu_login`을 fork-exec 하도록 수정한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image17.png?raw=true" title="image17.png" alt="image17.png"></img><br/>
</center>

#### (2) `list.txt`에 `[Username] [Password]` 형식으로 사용자 정보를 줄 단위로 저장한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image18.png?raw=true" title="image18.png" alt="image18.png"></img><br/>
</center>

#### (3) `list.txt`를 참조하여 로그인을 수행하는 `ssu_login.c`를 작성한다. 로그인 성공 시 sh를 fork-exec으로 호출한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image19.png?raw=true" title="image19.png" alt="image19.png"></img><br/>
</center>

#### (4) `Makefile`을 수정하여 `list.txt`와 `ssu_login` 프로그램이 xv6에서 읽히도록 한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image20.png?raw=true" title="image20.png" alt="image20.png"></img><br/>
</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image21.png?raw=true" title="image21.png" alt="image21.png"></img><br/>
</center>

#### (5) `make`를 이용하여 컴파일 후 실행한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image22.png?raw=true" title="image22.png" alt="image22.png"></img><br/>
</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image23.png?raw=true" title="image23.png" alt="image23.png"></img><br/>
        
정상적으로 **로그인**하는 경우

</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj1/image24.png?raw=true" title="image24.png" alt="image24.png"></img><br/>

정보가 잘못된 경우
 
</center>

---

(2) xv6에 시스템콜 추가하기
===


## 개요
 xv6에 프로세스의 메모리 사용량을 출력하는 memsize 시스템콜과 프로세스가 호출한 시스템콜을 추적할 수 있는 trace 시스템콜을 추가한다. memsize를 이용하여 malloc 사용 전, 후의 메모리 사용량을 비교해보고 malloc을 분석한다.

## 상세설계

https://jehwanyoo.net/2020/10/19/xv6%EC%9D%98-%EC%8B%9C%EC%8A%A4%ED%85%9C-%EC%BD%9C-%ED%98%B8%EC%B6%9C-%EA%B3%BC%EC%A0%95/

위 사이트를 참고하여 시스템콜 호출 과정을 이해하였다.

#### 시스템콜 호출 과정

1. 사용자 프로그램에서 시스템콜을 호출하면 **시스템콜 인터럽트**가 발생한다. 
2. 이후 **인터럽트**를 처리하는 과정에서 `trap`을 호출하고, `trap`은 다시 `syscall`을 호출하며, 최종적으로 `syscalls[num]()`을 호출한다. 
3. 시스템콜을 등록하기 위해선 `num`에 해당하는 시스템콜 번호를 정의하고, 시스템콜에 대한 구현 역시 작성해야 한다.
 등록을 위한 절차는 아래와 같다.
    1. `sysproc.c`에 시스템콜 구현부를 추가한다.
    2. `syscall.h`에 `#define`을 이용해 시스템콜 번호를 등록한다.
    3. `syscall.c`에서 시스템콜 선언을 하고, `syscalls` 함수 포인터 배열에 시스템콜 함수 포인터를 등록한다. 인덱스는 시스템콜 번호를 따른다.
    4. `user.h`에 사용자에게 보여지는 시스템콜을 등록한다.
    5. `usys.S`에 매크로를 이용하여 시스템콜을 등록한다.

## 구현 방법 및 실행 결과
#### (1) memsize 시스템콜 추가

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image01.png?raw=true" title="image01.png" alt="image01.png"></img><br/>

</center>

`syscall.h`에 `SYS_memsize`를 등록한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image01b.png?raw=true" title="image01b.png" alt="image01b.png"></img><br/>
</center>

`syscall.c`에 시스템콜 함수 선언을 작성하고 `syscalls` 배열에 추가한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image02.png?raw=true" title="image02.png" alt="image02.png"></img><br/>
</center>

`user.h`에 사용자에게 보여지는 시스템콜 선언을 추가한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image03.png?raw=true" title="image03.png" alt="image03.png"></img><br/>
</center>

`usys.S`에 시스템콜을 등록한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image04.png?raw=true" title="image04.png" alt="image04.png"></img><br/>
</center>

  `sysproc.c`의 시스템콜 구현부에서 `myproc()`을 이용해 현재 프로세스의 `proc 구조체`를 얻는다. 이 구조체의 `sz`값을 시스템콜의 반환값으로 설정한다.


<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image05.png?raw=true" title="image05.png" alt="image05.png"></img><br/>
</center>

 `memsize` 시스템콜 테스트를 위해 `memsizetest` 쉘 프로그램을 작성한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image06.png?raw=true" title="image06.png" alt="image06.png"></img><br/>
</center>

쉘 프로그램 `memsizetest`가 잘 동작하고 있다.

#### (2) memsizetest에서 malloc 전, 후 차이가 2048 바이트가 아닌 이유

  `umalloc.c`을 분석하였다.
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image07.png?raw=true" title="image07.png" alt="image07.png"></img><br/>
</center>

 * `malloc`의 동작 방식은 힙 영역에 `nbytes`를 할당할 수 있을 만큼의 여유 공간이 존재하면, 해당 공간의 헤더를 설정하고 사용자에게 실제 사용할 수 있는 메모리 공간을 제공하는 것이다. 
 * 만약 여유 공간이 존재하지 않으면 `malloc`의 87번째 줄처럼 `morecore`을 호출하여 여유공간을 확보한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image08.png?raw=true" title="image08.png" alt="image08.png"></img><br/>
</center>

 * `morecore`은 52번째 줄에서 보듯 새로 할당할 공간이 4096 바이트보다 적으면 4096 바이트만큼의 힙 영역을 확장한다. 
 * 그 이유는 `sbrk` 시스템콜의 비용이 비싸기 때문이다. `sbrk`는 메모리 공간의 데이터영역을 확장하는 시스템콜이다. 확장한 부분을 동적할당을 위한 공간(힙 영역)으로 사용하는 것이다.

#### (3) trace 시스템콜 추가

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image09.png?raw=true" title="image09.png" alt="image09.png"></img><br/>
</center>

 `trace` 시스템콜 구현을 위해 `proc.h`의 `proc` 구조체에 `uint tracemask`를 추가했다. 

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image10.png?raw=true" title="image10.png" alt="image10.png"></img><br/>
</center>

 `sys_trace`에서 이 값을 사용자가 설정한 시스템콜 마스크값으로 설정한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image11.png?raw=true" title="image11.png" alt="image11.png"></img><br/>
</center>

 시스템콜을 추적하기 위해 `syscall.c`의 `syscall`에서 마스크값을 검사한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image12.png?raw=true" title="image12.png" alt="image12.png"></img><br/>
</center>

 시스템콜의 이름을 얻기 위해 문자열 배열인 `syscall_names`을 추가하였다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image13.png?raw=true" title="image13.png" alt="image13.png"></img><br/>
</center>

 `proc.c`의 `fork`에서 자식 프로세스의 `proc` 구조체에 마스크값을 복사한다. 이로써 `fork`를 통해 만든 자식 프로세스에서도 시스템콜 추적이 유지된다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image13b.png?raw=true" title="image13b.png" alt="image13b.png"></img><br/>
</center>

최종적으로 `syscall.h`, `syscall.c`, `usys.S`에 등록 작업을 한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image14.png?raw=true" title="image14.png" alt="image14.png"></img><br/>
</center>

시스템콜 추적을 위하여 쉘 프로그램인 `ssu_trace`을 작성한다. `trace`를 먼저 호출한 후 `exec`을 호출한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image16.png?raw=true" title="image16.png" alt="image16.png"></img><br/>
</center>

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj2/image17.png?raw=true" title="image17.png" alt="image17.png"></img><br/>
</center>

`ssu_trace`가 정상적으로 동작한다.

---
(3) xv6 스케줄러를 SSU Scheduler로 개선
===

xv6의 기존 프로세스 스케줄러를 수정하여 개선한다.


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

---

(4) 페이징 알고리즘 시뮬레이션
===
페이지 교체 알고리즘을 시뮬레이션하여 각 알고리즘의 성능을 비교한다.


## 1. 개요
 현대 OS는 메모리를 가상화하기 위해 페이징 기법을 사용한다. 페이징 기법에서는 페이지 교체 알고리즘에 따라 성능이 좌우된다. 다양한 페이지 교체 알고리즘을 동일한 페이지 스트링과 RW 비트를 사용하여 시뮬레이션한 후, 각각의 페이지 폴트 횟수를 측정한다. 최종적으로 각 알고리즘의 시뮬레이션 결과를 Optimal 알고리즘과 비교하여 분석한다.

## 2. 알고리즘의 입력 및 출력

|알고리즘에 필요한 사전 요소|설정 방법|
|---|---|
|페이지 스트링|프로그램에서 무작위로 생성하거나 파일로부터 읽음.<br/>원칙상 **최소 500개**|
|ESC의 R, W 비트|무작위로 생성하거나 파일로부터 읽음.|
|프레임 수|**3 이상 10 이하의 정수**를 사용자로부터 입력받음|
|참조 페이지 스트림|**1 이상 30 이하**의 정수로 고정|

* 페이지 교체 알고리즘에 필요한 사전 요소 : `페이지 스트링`, `프레임 개수`
* ESC 알고리즘의 경우 추가로 RW 비트가 필요하다. 
 페이지 스트링은 파일로부터 읽거나 프로그램에서 임의로 생성할 수 있게 하였다. 
- 페이지 스트링을 이루는 페이지 번호는 **1부터 30까지의 정수**이다. 
- 프레임 개수는 **3부터 10까지**의 제한된 범위 내에서 사용자가 직접 설정한다.
- ESC 알고리즘의 RW 비트는 페이지 스트링과 마찬가지로 파일로부터 읽거나 임의로 생성할 수 있다.
---
<center><img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/out_ex_pagesimul.png?raw=true" title="출력예시" alt="image01"></img><br/></center>
* 시뮬레이션 결과는 stdout과 output 파일로 출력된다. 테이블 형태로 출력되는데, 각 열에는 페이지 프레임이, 행은 요구 페이지와 변화된 프레임 상태, 페이지 폴트 여부가 출력된다. 마지막 줄에는 총 페이지 폴트 횟수가 출력된다.

## 3. 알고리즘 설명
 페이지 교체 알고리즘에서 발생하는 상황은 다음과 같이 3가지가 있다.

 1. 페이지가 이미 프레임에 있을 때
 2. 페이지가 프레임에 없고(Page fault), 비어있는 프레임이 있을 때
 3. 페이지가 프레임에 없고(Page fault), 비어있는 프레임이 없어서 교체해야 할 때
   
 효율적인 페이징 운영을 위해 페이지 폴트 횟수를 최대한 줄여야 한다.
 
  즉, ③의 상황에서 어떤 페이지 프레임을 교체 대상으로 선택하냐에 따라 알고리즘의 성능이 좌우된다.

### 1. Optimal
#### (1) 동작 방식
 Optimal 알고리즘은 가장 이상적인 페이지 교체 알고리즘이다. 앞으로 가장 오랫동안 사용되지 않을 페이지를 교체하기 때문이다. 

 즉 미래의 페이지 스트링을 조회하여 가장 나중에 등장하거나 등장하지 않는 프레임의 페이지를 교체 대상으로 선택한다.

---

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image01.png?raw=true" title="이미지1" alt="image01"></img></center>

<center>(예시 그림) 교체 전 프레임에서 2가 가장 나중에 사용되므로 2를 교체한다.</center>

---
Optimal 구현방식은 명품 운영체제(황기태 저)를 참고하였다.
  
#### (2) pseudo code
```
    page_string: 페이지 스트링
    frame: 프레임
    for new_page in page_string: # 페이지 스트링에서 각 페이지 번호를 불러옴
        for each_page in frame: 
            if each_page == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
        found[frame.count] 배열을 False로 초기화
        fcnt = 0

    # 이 pseudo 코드에서 page_string의 끝값을 NULL이라고 가정        
        for (pre_page = new_page의 다음 페이지; pre_page != NULL; pre_page = pre_page의 다음 페이지):
            for i in range(frame.count):  # 모든 페이지 프레임의 페이지 탐색
                if pre_page == frame[i] and not found[i]:  # 현재 페이지가 미래에 발견되었다면
                    found[i] = True # 기록
                    fcnt += 1
                    break
            if fcnt + 1 >= pgf_cnt:   # 하나의 페이지를 제외하고 다 찾았다면 탐색 중단
                break
        for i in range(frame.count): 
            if not found[i]:  # 미래 탐색 과정중 발견되지 않은 페이지
                frame[i] = new_page  # 해당 페이지 교체
                break
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력
```

### 2. FIFO
#### (1) 동작 방식
 FIFO 알고리즘은 가장 오래된 페이지를 교체하는 알고리즘이다. 페이지가 프레임에 배치될 때 프레임 번호를 큐에 삽입하고, 교체 대상을 찾을 때 큐에서 프레임 번호를 꺼낸다.

---
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image02.png?raw=true" title="이미지2" alt="image02"></img>
(예시 그림) 6을 프레임에 배치하려는 상황에서 큐에 있는 프레임 번호 0을 확인하고,
이것을 다시 큐에 삽입하게 된다. 따라서 0번째 프레임은 교체 대상이 된다.
</center>

---

FIFO 구현방식은 명품 운영체제(황기태 저)를 참고하였다.

#### (2) pseudo code
```
    page_string: 페이지 스트링
    frame: 프레임
    queue: 큐
    for new_page in page_string: # 페이지 스트링에서 각 페이지 번호를 불러옴
        for each_page in frame: 
            if each_page == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
		queue.push(i)    # 큐에 프레임번호 삽입
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
	frame_number = queue.pop()   # 큐에서 프레임번호 추출
	queue.push(frame_number)    # 다시 큐에 프레임번호 삽입
	frame[frame_number] = new_page    # 페이지 교체
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력
```

### 3. LIFO
#### (1) 동작 방식
 LIFO 알고리즘은 가장 최근에 삽입된 페이지를 교체하는 알고리즘이다. 페이지가 프레임에 배치될 때 프레임 번호를 스택에 삽입하고, 교체 대상을 찾을 때 스택에서 프레임 번호를 꺼낸다. 계속 교체되는 프레임의 페이지를 제외하고는, 대다수의 페이지가 한번 배치되면 교체되지 않는다.

---
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image03.png?raw=true" title="이미지3" alt="image03"></img>

(예시 그림) 6을 프레임에 배치하려는 상황에서 스택에 있는 프레임 번호 3을 확인하고,
이것을 다시 스택에 삽입하게 된다. 따라서 3번째 프레임은 교체 대상이 된다.
</center>

---

LIFO의 구현은 gatevidyalay 사이트
 (https://www.gatevidyalay.com/page-replacement-algorithms-page-fault)를 참고하였다.


#### (2) pseudo code
```
    page_string: 페이지 스트링
    frame: 프레임
    stack: 스택
    for new_page in page_string: # 페이지 스트링에서 각 페이지 번호를 불러옴
        for each_page in frame: 
            if each_page == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
		stack.push(i)    # 스택에 프레임번호 삽입
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
	frame_number = stack.pop()   # 스택에서 프레임번호 추출
	stack.push(frame_number)    # 다시 스택에 프레임번호 삽입
	frame[frame_number] = new_page    # 페이지 교체
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력
```

### 4. LRU
#### (1) 동작 방식
 LRU 알고리즘은 가장 오랫동안 참조되지 않은 페이지를 교체하는 알고리즘이다. 리스트를 이용해 가장 오랫동안 참조되지 않은 페이지를 관리하였다. 페이지 폴트가 발생할 때에는 FIFO 방식과 동일하다. 리스트를 큐처럼 생각하여 프레임 번호를 맨 뒤에 삽입한다. 그러나 페이지가 이미 프레임에 존재할 경우, 리스트에서 해당 프레임 번호를 맨 뒤로 옮긴다. 이로써 리스트의 맨 앞에는 가장 오랫동안 참조되지 않은 페이지가 남게 된다.

---
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image04.png?raw=true" title="이미지4" alt="image04"></img>

(예시 그림)
</center>

---
 LRU는 이 외에도 타임스탬프를 기록하여 구현할 수도 있다. 루보미르 빅과 앨런 C. 쇼의 책인 Operating Systems Principles의 내용을 참고하여 구현하였다.
 
### 5. LFU
#### (1) 동작 방식
 LFU 알고리즘은 참조 횟수가 가장 적은 페이지를 교체하는 알고리즘이다. 참조 횟수를 저장하는 변수를 프레임마다 두었다. 참조하고자 하는 페이지가 프레임에 이미 존재할 때마다 이 변수를 증가시키게 된다. 나중에 페이지를 교체해야 할 때, 가장 적은 참조 횟수를 교체 대상으로 선정한다.

---
<center> 
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image05.png?raw=true" title="이미지5" alt="image05"></img>

(예시 그림)
</center>

---

참고한 사이트는 아래와 같다.

1. https://blog.naver.com/xowns4817/221226671491 
2. https://en.wikipedia.org/wiki/Least_frequently_used
   
#### (2) pseudo code
```
    page_string: 페이지 스트링
    frame: 프레임
    ref_cnt: 참조 횟수 배열
    for new_page in page_string: # 페이지 스트링에서 각 페이지 번호를 불러옴
        for i in range(frame.count): 
            if frame[i] == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
		ref_cnt[i] += 1        # 참조 횟수 1 증가
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
		ref_cnt[i] = 1     # 참조 횟수 1로 설정
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
	minpf = 0        # 참조 횟수가 최소인 프레임 번호
	minref = ref_cnt[0]        # 참조 횟수의 최솟값
	for i in range(1, frame.count):
            if ref_cnt[i] < minref:  # 참조 횟수의 최솟값 탐색
                minref = ref_cnt[i]
		minpf = i
	frame[minpf] = new_page    # 페이지 교체
	refcnt[minpf] = 1         # 참조 횟수 1로 설정
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력
```

### 6. SC
#### (1) 동작 방식
 SC 알고리즘(Second Chance/One handed Clock)은 프레임마다 참조 비트를 두어 교체 시 활용하는 알고리즘이다. 참조 비트는 프레임에 존재하는 페이지를 참조하거나, 새로 배치할 때 1로 설정된다. 교체 시에는 환형 큐 방식으로 대상을 탐색하는데, 포인터가 가리키는 페이지의 참조 비트가 1이면 0으로 설정하여 포인터를 넘기게 되고, 0일 경우 교체 대상으로 선정한다. 교체하거나 배치할 경우 포인터는 그 다음 위치를 가리키게 된다.
 알고리즘은 루보미르 빅과 앨런 C. 쇼의 책인 Operating Systems Principles의 내용을 참고하여 구현하였다.

---

<center> 
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image06.png?raw=true" title="이미지6" alt="image06"></img>

(예시 그림)
</center>

---

#### (2) pseudo code
```
    page_string: 페이지 스트링
    frame: 프레임
    clock: 참조 횟수 배열
    pointer: 환형 큐 방식으로 순환할 포인터
    for new_page in page_string: # 페이지 스트링에서 각 페이지 번호를 불러옴
        for i in range(frame.count): 
            if frame[i] == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
		clock[i] = 1        # 참조 비트를 1로 설정
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
		clock[i] = 1        # 참조 비트를 1로 설정
		pointer = (i+1) % frame.count   # 포인터 순환
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
	while True:
	    if clock[pointer] == 1:  # 참조 비트가 1이면
		clock[pointer] = 0   # 참조 비트를 0으로 설정
	    else:    # 참조 비트가 0이면
	        break    # 선택
	    pointer = (pointer+1) % frame.count   # 포인터 순환
	frame[pointer] = new_page   # 교체
	clock[pointer] = 1    # 참조 비트를 1로 설정
	pointer = (pointer+1) % frame.count  # 포인터 순환
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력

```

### 7. ESC
#### (1) 동작 방식
 ESC 알고리즘(Enhanced Second Chance/Two handed Clock/NUR)은 프레임마다 Reference 비트와 Write 비트를 두는 알고리즘이다. 페이지 참조가 쓰기 요청일 때는 Reference, Write 비트가 11로, 읽기 요청일 때는 10으로 설정된다. 따라서 이 알고리즘에서는 쓰기/읽기 요청에 관한 정보가 페이지마다 필요하다.
 페이지를 배치할 때 설정한 Reference, Write 비트는 SC와 마찬가지로 포인터가 환형 큐 방식으로 전환될 때마다 변경된다. 변경 방식은 아래와 같다.

---
<center> 
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image07.png?raw=true" title="이미지7" alt="image07"></img>

(ESC의 교체 과정 중 포인터가 페이지를 가리킬 때 R, W 비트 변경 방법)

---

</center>

 비트가 00일 때에 페이지가 선택되고, 나머지는 위의 표와 같이 변경된다. 따라서 쓰기 요청일 경우 대상으로 선택될 때까지 2번의 기회가 주어지고, 읽기 요청일 경우 1번의 기회가 주어진다. 
 ESC 알고리즘은 페이지 스트링과 동일한 길이의 비트 스트링을 입력받도록 구현하였다. 1은 쓰기 요청을 의미하여 해당하는 페이지가 배치될 때 R, W 비트가 11로 설정되고, 0은 R, W 비트가 10으로 설정된다. 따라서 알고리즘은 아래의 예시 그림처럼 동작한다. 

---
<center> 
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image08.png?raw=true" title="이미지8" alt="image08"></img>
(예시 그림) 프레임에서 좌측은 RW 비트를 의미함.

---

 알고리즘은 루보미르 빅과 앨런 C. 쇼의 책인 Operating Systems Principles의 내용을 참고하여 구현하였다.

</center> 

#### (2) pseudo code

```
    page_string: 페이지 스트링 및 해당 페이지의 쓰기 요청 여부. 
    frame: 프레임
    bit: reference bit과 dirty(write) bit를 저장할 배열
    pointer: 환형 큐 방식으로 순환할 포인터
    for new_page, new_bit in page_string: # 페이지와 페이지의 쓰기 요청 비트를 불러옴
        for i in range(frame.count): 
            if frame[i] == new_page:  # 페이지가 이미 있는 경우
                is_page_fault = False  # 페이지 폴트가 아님
		if new_bit == 1:  # 쓰기 요청이면
		    bit[i] = 3  # RW 비트는 11
		else:
		    bit[i] = 2  # RW 비트는 10
                goto PrintInfo   # 정보 출력

        is_page_fault = True  # 여기서부터 페이지 폴트
        for i in range(frame.count):
            if frame[i] is empty:  # 비어있는 페이지 프레임이 있는 경우
                frame[i] = new_page  # 페이지 설정
		if new_bit == 1:  # 쓰기 요청이면
		    bit[i] = 3  # RW 비트는 11
		else:
		    bit[i] = 2  # RW 비트는 10
		pointer = (i+1) % frame.count   # 포인터 순환
                goto PrintInfo    # 정보 출력
        
	# 모든 페이지 프레임이 사용중이라면
	while True:
	    if bit[pointer] == 3:  #  RW 비트가 11이면
		bit[pointer] = 1   # RW 비트를 01로 설정
	    elif bit[pointer] == 2 or bit[pointer] == 1:    # RW 비트가 10이거나 01이면
		bit[pointer] = 0    #RW 비트를 00으로 설정
	    else:    # RW 비트가 00이면
	        break    # 선택
	    pointer = (pointer+1) % frame.count   # 포인터 순환
	frame[pointer] = new_page   # 교체
	if new_bit == 1: # 쓰기 요청이면
	    bit[pointer] = 3  # RW 비트는 11
	else:
	    bit[pointer] = 2   # RW 비트는 10
	pointer = (pointer+1) % frame.count  # 포인터 순환
    PrintInfo:
	new_page와 교체된 프레임의 상태, 페이지 폴트 여부를 출력
```

## 4. 프로그램 사용 메뉴얼
 make 명령어를 입력하면 2개의 실행파일 simulator과 maker이 생성된다.
 시뮬레이터(simulator)를 작동시키기 위해서는 페이지 스트링이 필요하다. 또한 ESC 알고리즘의 경우 쓰기 요청 여부를 의미하는 비트 스트링도 필요하다. 각각은 input, bitinput이라는 이름의 텍스트 파일로 작성하면 된다. 페이지 번호 혹은 비트 숫자마다 공백 혹은 개행 문자로 구분하면 된다.
 simulator 프로그램 내부에서 임의의 길이가 500인 페이지 스트링을 생성할 수도 있다. 하지만 길이를 임의로 설정하여 페이지 스트링 파일(input) 혹은 비트 스트링 파일(bitinput)을 제작하고 싶을 때는 maker이라는 프로그램을 이용하면 된다.

### 1. maker

 maker의 실행 화면은 아래와 같다.

---
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/maker.png?raw=true" title="maker" alt="maker"></img>
</center>

---

  1을 입력하면 페이지 스트링의 개수를 입력하는 화면이 나온다. 개수를 입력하면 1 이상 30 이하의 임의의 정수가 줄 단위로 적힌 input 파일이 생성된다. 2를 입력했을 때도 마찬가지이다. 개수를 입력하면 0 또는 1이 줄 단위로 적힌 bitinput 파일이 생성된다. 3을 입력하면 종료되며, 각 상황에서 비정상적인 입력을 하게 되면 예외 메시지가 출력된다.

### 2. simulator

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image10.png?raw=true" title="이미지10" alt="image10"></img>
</center>

 simulator를 실행하면 다음과 같이 알고리즘을 선택하는 메뉴가 나온다. 수행 방법은 다음과 같이 3가지가 
 있다.
1. 1개 이상, 3개 이하의 알고리즘(1번~7번)을 선택

2. 8번 메뉴인 ALL을 입력
 
3. 종료

 1의 경우 알고리즘 번호를 스페이스로 구분하여 입력하면 된다. 2와 3의 경우에는 각각 8 혹은 0을 입력하면 된다. 입력 오류가 발생하면 아래와 같이 에러 메시지가 출력된다.

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image11.png?raw=true?raw=true" title="wrong input" alt="image_wrong"></img>
</center>

---

정상적으로 입력하였다면 페이지 프레임의 개수를 입력하는 화면이 출력된다. 3부터 10까지의 정수를 입력하면 된다.

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image12.png?raw=true" title="12" alt="12"></img>
</center>

잘못 입력하면 위와 같이 출력된다.

---


<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image13.png?raw=true" title="13" alt="13"></img>
</center>

정상적으로 입력하면 데이터 입력 방식을 선택하는 화면이 나온다. 1을 입력하면 길이 500의 페이지 스트링이 임의로 생성되며, 2를 입력하면 input 파일로부터 페이지 스트링을 읽어온다.

---

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image14.png?raw=true" title="14" alt="14"></img>
</center>

알고리즘 중 ESC가 포함되어 있다면 위와 같은 화면이 나온다. 이것도 마찬가지로 1을 입력하면 길이 500의 비트열이 임의로 생성되며, 2를 입력하면 bitinput으로부터 비트열을 읽어온다.

---

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image15.png?raw=true" title="15" alt="15"></img>
</center>

마지막으로 시뮬레이션을 진행할 페이지 스트링과 비트가 확인차 출력된다. y를 입력하면 시뮬레이션을 진행하고, n을 입력하면 취소한다. 이외의 입력은 사용자로부터 재입력을 요구한다.

---
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/print_all.png?raw=true" title="all" alt="all"></img>
</center>

  알고리즘 개수만큼 시뮬레이션 결과가 출력된다. 시뮬레이션 결과는 테이블 형태로 시각화하였다. 
  
  테이블의 첫줄에는 프레임 번호가 표시되고, 둘째줄부터 페이지 번호 및 프레임 상태, 페이지 폴트 여부가 출력된다. 테이블의 끝줄에는 알고리즘의 총 페이지 폴트 수가 출력된다.
  
  SC의 경우 참조 비트 및 포인터의 위치가 행마다 표시되고, ESC의 경우 페이지의 왼쪽에 쓰기 요청 여부(r/w)와 프레임별 RW 비트가 출력된다.

 모든 알고리즘의 시뮬레이션을 출력하였다면, 사진과 같이 마지막엔 알고리즘별 페이지 폴트 수를 비교하여 출력한다. 시뮬레이션 결과는 output이라는 이름의 텍스트 파일로도 저장된다.

## 5. 결과 및 성능 분석


<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image16.png?raw=true" title="16" alt="16"></img>
</center>

 maker로 input과 bitinput을 만들고, 모든 알고리즘의 시뮬레이션을 출력하였다.

---

<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image17.png?raw=true" title="17" alt="17"></img>
</center>
 
<center>
<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/image18.png?raw=true" title="18" alt="18"></img>

 시뮬레이션이 성공적으로 이루어진 것을 확인할 수 있었다.

 이와 같은 방법으로 랜덤 페이지 스트링을 만들고 반복하여 테스트하였다.

</center>

---

<center>

<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/statistics.png?raw=true" title="statistics" alt="statistics"></img>

(진한 녹색일수록 우수한 성능, 진한 빨간색일수록 좋지 못한 성능을 의미한다.)


</center>

 * 임의의 페이지 스트링을 생성하여 표에 나타난 길이별로 200번씩 테스트하였다. 표는 페이지 폴트 발생 횟수의 평균값이다. 
  
 * Optimal이 가장 이상적인 알고리즘인데도 불구하고 페이지 폴트 비율이 37.7%나 되었다. 그 외의 알고리즘을 비교했을 때 66%~67% 성능을 내었다. 페이지 폴트 비율만 보면 특정 알고리즘이 더 효율이 높다고 보기 어려웠다.
  
 * Optimal을 제외하고는 LIFO가 주어진 알고리즘 중 가장 성적이 좋은 것을 알 수 있다. 하지만 LIFO를 실제로 적용하면 특정 페이지 그룹만 페이지 폴트가 일어나지 않는 현상이 발생하므로 실제로 사용하기에는 무리가 있다. 
    
 * 또한 LFU도 전반적으로 우수한 성능을 내었다. 임의로 생성한 페이지 스트링이다 보니 LIFO와 같이 특정 프레임만 교체되는 현상이 발생한 것으로 보인다. LRU 역시 좋은 성능을 내었다. FIFO, LFU, SC, ESC 알고리즘은 평균치가 최악인 경우가 1번씩은 발생하는 것에 반해, LRU는 꾸준히 최악의 성적은 면한 것을 확인할 수 있었다. 
    
 * FIFO의 경우 페이지 스트링의 길이가 증가할수록 페이지 폴트 수가 줄어드는 경향이 있었다. SC와 ESC는 LRU 근사 알고리즘이다 보니 LRU보다 좋지 못한 성능을 확인할 수 있었다. 그리고 ESC의 RW 비트가 무작위인 것도 성능에 악영향을 미쳤다고 생각한다.

 아래 표는 길이가 500인 임의의 페이지 스트링을 생성하여 여러 번 테스트한 뒤, 페이지 폴트수가 최대/최소인 횟수를 기록한 것이다. Optimal은 제외하였다.

<center>

<img src="https://github.com/simjeehoon/src_repository/blob/master/page-simulator/master/pagefault_table.png?raw=true" title="pf_table" alt="pf_table"></img>

</center>

(5) xv6에 CS 파일 시스템 추가
===

xv6의 기존 파일 시스템의 동작 원리를 이해하고 새로운 **CS 파일 시스템**을 추가한다.


## 개요
 CS 파일 시스템은 파일에 연속적인 데이터 블록을 할당함으로써, 파일의 최대 크기를 늘리고 디스크 탐색시간을 단축하는 파일 시스템이다. XV6의 기존 파일 시스템은 그대로 유지하면서 CS 파일 시스템을 추가한다. CS 파일 시스템을 이용할 때, inode 구조체에 있는 direct block에 기존 파일 시스템과 다른 방식으로 값을 부여한다.

## 상세 설계 및 구현 과정

```
이번 작업에서 수정한 소스 코드에는 주석에 [os-prj5]를 붙여 달았다.
```

### 파일 생성 과정

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/image01.png?raw=true" title="image01.png" alt="image01.png"></img><br/>
</center>

 시스템콜 `open`에 인자로 `O_CREATE`를 지정하면 파일이 생성된다. `open`이 호출되는 과정은 위의 그림과 같다. **CS 파일 시스템**을 구현하기 위해서는 가장 먼저 **CS 파일**을 생성하여야 한다. 따라서 파일을 생성하는 코드에 **CS 파일 시스템**에 대한 처리 코드를 삽입하였다.

#### fcntl.h
```h
#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200
#define O_CS 0x020
```

#### stat.h
```h
#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device
#define T_CS 4	   // Continuous Sector based File

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};
```

`fcntl.h`에 `O_CS` 플래그를, `stat.h`에 `T_CS` 매크로를 추가하였다.

#### sysfile.c

```c
    if(omode & O_CREATE){
    // [os-prj5] CS 처리
	if(omode & O_CS)
	  ip = create(path, T_CS, 0, 0);
	else
	  ip = create(path, T_FILE, 0, 0);
	if(ip == 0){
	  end_op();
	  return -1;
	}
```

`sysfile.c`에서 `O_CS` 플래그가 존재하면 `create`에 `type`으로 `T_CS`를 넘긴다.


#### sysfile.c
```c
static struct inode*
create(char *path, short type, short major, short minor)
{
  struct inode *ip, *dp;
  char name[DIRSIZ];

  if((dp = nameiparent(path, name)) == 0)
    return 0;
  ilock(dp);

  if((ip = dirlookup(dp, name, 0)) != 0){
    iunlockput(dp);
    ilock(ip);
    if(type == T_FILE && ip->type == T_FILE)
      return ip;
	else if(type == T_CS && ip->type == T_CS)
	  // [os-prj5] CS 처리
      return ip;
    iunlockput(ip);
    return 0;
  }

  if((ip = ialloc(dp->dev, type)) == 0)
    panic("create: ialloc");
```

`sysfile.c`에서 `T_CS`일 때 `T_FILE`과 같은 방식으로 처리했다. `ialloc`에 `T_CS` 정보가 넘어가면, `type`이 `T_CS`인 `inode` 구조체가 생성된다. `ialloc`의 내용은 `fs.c`에 있다.

#### sysfile.c
```c
  f->type = FD_INODE;
  f->ip = ip;
  f->off = 0;
  f->readable = !(omode & O_WRONLY);
  f->writable = (omode & O_WRONLY) || (omode & O_RDWR);
  return fd;
}
```
`sys_open`에서 생성된 `inode` 구조체는 `file` 구조체에 담긴다. 

최종적으로 `file` 구조체를 가리키는 파일 디스크립터를 반환한다.

---
### 파일 쓰기 과정
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/image02.png?raw=true" title="image02.png" alt="image02.png"></img><br/>
</center>

 * 시스템콜 `write`를 이용하여 파일에 내용을 기록할 때 호출되는 순서를 표로 나타내었다. 
 * `sys_write`, `filewrite`까지는 코드를 수정하지 않았다. 
 * `writei`부터는 코드 내용을 일부 수정했다. 파일이 **CS 파일 시스템**에 해당할 경우 기존과 다른 방식으로 쓰기 처리를 한다. 
 * **CS 파일 시스템**에서는 디스크 블록을 매핑할 때 오른쪽 노란색으로 칠해져 있는 함수들을 이용하고, 일반 파일 시스템에선 왼쪽의 매핑 함수들을 이용한다.


#### sysfile.c
```c
int
sys_write(void)
{
  struct file *f;
  int n;
  char *p;

  if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  return filewrite(f, p, n); // <--this
}
```

#### file.c
```c
int
filewrite(struct file *f, char *addr, int n)
{
  int r;

  if(f->writable == 0)
    return -1;
  if(f->type == FD_PIPE)
    return pipewrite(f->pipe, addr, n);
  if(f->type == FD_INODE){
    // write a few blocks at a time to avoid exceeding
    // the maximum log transaction size, including
    // i-node, indirect block, allocation blocks,
    // and 2 blocks of slop for non-aligned writes.
    // this really belongs lower down, since writei()
    // might be writing a device like the console.
    int max = ((MAXOPBLOCKS-1-1-2) / 2) * 512;
    int i = 0;
    while(i < n){
      int n1 = n - i;
      if(n1 > max)
        n1 = max;

      begin_op();
      ilock(f->ip);
      if ((r = writei(f->ip, addr + i, f->off, n1)) > 0) // <--this
        f->off += r;
      iunlock(f->ip);
      end_op();
```

`sysfile.c`의 `sys_write`와 `file.c`의 `filewrite` 코드이다. `filewrite`에서 `writei`를 호출한다.

#### fs.c
```c
int
writei(struct inode *ip, char *src, uint off, uint n)
{
  uint tot, m;
  struct buf *bp;

  if(ip->type == T_DEV){
    if(ip->major < 0 || ip->major >= NDEV || !devsw[ip->major].write)
      return -1;
    return devsw[ip->major].write(ip, src, n);
  }

  if(off > ip->size || off + n < off)
    return -1;

  // [os-prj5] writei for cs
  if(ip->type == T_CS){
	for(tot=0; tot<n; tot+=m, off+=m, src+=m){
	  bp = bread(ip->dev, bcsmap(ip, off, n-tot)); //<--this
	  m = min(n - tot, BSIZE - off%BSIZE);
	  memmove(bp->data + off%BSIZE, src, m);
	  log_write(bp);
	  brelse(bp);
	}
  }
  else {
	if(off + n > MAXFILE*BSIZE)
	  return -1;

	for(tot=0; tot<n; tot+=m, off+=m, src+=m){
	  bp = bread(ip->dev, bmap(ip, off/BSIZE)); //<--this
	  m = min(n - tot, BSIZE - off%BSIZE);
	  memmove(bp->data + off%BSIZE, src, m);
	  log_write(bp);
	  brelse(bp);
	}
  }
```
 `fs.c`의 `writei`이다. 기존 파일 시스템에서는 `bmap`을 이용하여 파일의 `offset`에 따라 디스크 블록을 할당한다. `bmap`은 필요시 디스크 블록을 할당하고, 할당된 블록 주소를 반환하는 함수이다. 이 블록 주소를 `bread`에 넘겨 디스크 블록 정보가 담긴 `struct buf`를 얻어온다. 이곳에 `src`의 내용을 기록하고 `log_write`와 `brelse`를 호출하여 쓰기 작업을 마친다.

 **CS 파일 시스템**을 구현하기 위해서 `inode`의 `type`이 `T_CS`인 경우와 아닌 경우로 흐름을 나누었다. `T_CS`일 때는 **CS 파일 시스템**을 위한 블록 매핑 함수인 `bcsmap` 함수를 호출한다. `bcsmap`은 필요시 디스크 블록을 추가로 할당한다. 그리하여 데이터가 쓰일 단일 블록 주소를 반환한다. 이 주소는 다시 `bread`의 인자로 넘겨진다. 이후 과정은 기존 파일 시스템과 동일하다.

#### fs.c
```c
// If there is no such block, bmap allocates one.
static uint
bmap(struct inode *ip, uint bn)
{
  uint addr, *a;
  struct buf *bp;

  if(bn < NDIRECT){
    if((addr = ip->addrs[bn]) == 0)
      ip->addrs[bn] = addr = balloc(ip->dev);
    return addr;
  }
  bn -= NDIRECT;

  if(bn < NINDIRECT){
    // Load indirect block, allocating if necessary.
    if((addr = ip->addrs[NDIRECT]) == 0)
      ip->addrs[NDIRECT] = addr = balloc(ip->dev);
    bp = bread(ip->dev, addr);
    a = (uint*)bp->data;
    if((addr = a[bn]) == 0){
      a[bn] = addr = balloc(ip->dev);
      log_write(bp);
    }
    brelse(bp);
    return addr;
  }

  panic("bmap: out of range");
}
```

 기존 파일 시스템이 사용하는 `bmap`은 구조가 단순하다. `inode`의 `addrs`에 블록 포인터가 없다면 `balloc`을 이용해 새로 할당하고, 그것을 반환한다. 이미 존재하면 존재하는 블록의 포인터를 반환한다.
 만일 파일 크기가 커질 경우 `INDIRECT` 포인터를 위한 디스크 블록을 할당하고, 그 블록 내부에 블록 포인터를 저장하고 반환한다.

 블록 할당에 이용하는 함수는 `balloc`이다. 이 함수는 디스크에 유효한 블록 1개를 찾아서 반환한다.

#### fs.c
```c
// [os-prj5] CS를 위한 블록 매핑 함수
static uint
bcsmap(struct inode *ip, uint off, uint n)
{
  uint staddr;
  uint prevaddr;
  uint alloclen;

  uint bn;
  uint position = off/BSIZE;
  uint accum;
  uint seqlen;
  uint needlen = n % BSIZE ? n / BSIZE + 1 : n / BSIZE;

  for(bn = 0, accum = 0 ; bn < NDIRECT && ip->addrs[bn] ; bn++){
	accum += ip->addrs[bn] & 255; // [os-prj5] accum 변수에 길이를 더함
	if(accum > position){ // [os-prj5] 위치 발견
	  accum -= ip->addrs[bn] & 255;
	  return (ip->addrs[bn] >> 8) + (position - accum); // [os-prj5] 블럭의 위치를 리턴
	}
  }

  if(bn != 0){ // [os-prj5] 마지막 addrs 확장
	accum -= ip->addrs[bn-1] & 255; 
	staddr = ip->addrs[bn-1] >> 8;
	alloclen = ip->addrs[bn-1] & 255;
	if(alloclen < 255){ // [os-prj5] 255 미만일때만 확장 가능
	  prevaddr = staddr+alloclen - 1;
	  int b;
	  if(255-alloclen < needlen)
		b = bcsalloc(ip->dev, prevaddr, 255-alloclen, &seqlen);
	  else
		b = bcsalloc(ip->dev, prevaddr, needlen, &seqlen);
	  if(b != -1){ // [os-prj5] 확장 성공
		alloclen += seqlen;
		ip->addrs[bn-1] = (staddr << 8) | (alloclen & 255);
		if(accum + alloclen > position){ // [os-prj5] 데이터를 위치시킬 공간을 얻었다면
		  return staddr + (position - accum);
		}
	  }
	}
	accum += alloclen;
  }

  if(bn >= NDIRECT){ // [os-prj5] 블록을 더이상 할당 불가능
	panic("CS : no more block in inode.");
	return -1;
  }

  if(needlen <= 255) // [os-prj5] 최대 연속 할당 길이는 255
	staddr = bcsalloc(ip->dev, -1, needlen, &seqlen); 
  else
	staddr = bcsalloc(ip->dev, -1, 255, &seqlen); 
  alloclen = seqlen;
  ip->addrs[bn] = (staddr << 8) | (alloclen & 255);
  return staddr + (position - accum);
}
```

 * **CS 파일 시스템**에서 사용하는 `bcsmap`의 흐름은 `bmap`과 다르다. `inode` 구조체 내 `addrs`의 각 원소를 해석하는 방법이 다르고, 블록을 할당하는 방식이 다르기 때문이다.

 * **CS 파일 시스템**에서 `addrs`의 각 원소를 해석할 때, **상위 3바이트**는 블록의 주소, **하위 1바이트**는 연속된 블록의 개수를 의미한다. 

    * 이를 이용하여, 인자로 넘겨받은 `offset`이 몇 번째 블록에 해당하는지 `addrs[0]`부터 순차적으로 탐색한다. 만일 `offset`이 위치한 단일 블록이 이미 존재하면, 해당 블록의 주소를 반환한다.</br>

 * 블록이 존재하지 않는 경우, 처리하는 방법은 2가지이다. 마지막 `addrs`의 원소가 가리키는 블록의 길이를 확장하거나, 아예 새로운 블록을 할당하는 것이다. 

    * 전자의 방법을 통하여 확장에 실패하는 경우는 연속 할당에 실패하거나, 블록 길이가 255를 초과하는 경우이다. 

    * 할당에 이용하는 함수는 `bcsalloc`이다. 이 함수에 이전 블록 주소와 필요한 공간의 길이를 인자로 넘겨, 새로 할당한 공간의 시작 주소와 새로 할당한 영역의 길이를 반환한다. 

    * 필요한 공간의 길이는 `bcsmap`의 3번째 인자 n을 이용하여 구한다. n은 실제로 필요한 데이터 용량이다. 

    * 이전 블록 주소와 연속적인 블록을 할당할 수 없다면 `bcsalloc`은 `–1`를 반환한다.

 * 연속 할당에 실패하여 `addrs`에 새로운 값을 할당하는 경우엔 이전 블록 주소를 `–1`로 설정하여 넘긴다.

    * 그러면 `bcsalloc`은 이전 블록과의 연속성을 고려하지 않는다.

 * 두 방법 모두 실패했다면 `panic`을 호출한다.

 
 블록 할당을 비교하기 위해 `balloc`과 `bcsalloc`을 분석하였다.

#### fs.c
```c
// Allocate a zeroed disk block.
static uint
balloc(uint dev)
{
  int b, bi, m;
  struct buf *bp;

  bp = 0;
  for(b = 0; b < sb.size; b += BPB){
    bp = bread(dev, BBLOCK(b, sb));
    for(bi = 0; bi < BPB && b + bi < sb.size; bi++){
      m = 1 << (bi % 8);
      if((bp->data[bi/8] & m) == 0){  // Is block free?
        bp->data[bi/8] |= m;  // Mark block in use.
        log_write(bp);
        brelse(bp);
        bzero(dev, b + bi);
        return b + bi;
      }
    }
    brelse(bp);
  }
  panic("balloc: out of blocks");
}
```

 * `balloc`에서는 가장 먼저 블록의 할당 정보 비트를 읽는다. 이 데이터를 이용하여 할당할 수 있는 블록을 순차적으로 찾는다. 
 * 할당 가능한 블록을 발견하였다면 해당 블록을 0으로 초기화하고, 블록 주소를 반환한다.

#### fs.c
```c
// [os-prj5] CS를 위한 block 할당 함수
static uint
bcsalloc(uint dev, int prevbnum, uint needlen, uint *alloclen)
{
  int b, bi, m;
  struct buf *bp;
  bp = 0;
  if(prevbnum == -1){ // [os-prj5] 완전히 새로운 영역을 할당하려고 할때
	b=0;
	bi=0;
  }
  else{ // [os-prj5] 이전 영역에 이어서 할당하려고 할 때
	int nextbnum = prevbnum+1;
	b = nextbnum / BPB;
	bi = nextbnum % BPB;
  }
  int staddr = -1;
  int length = 0;
  int modified;
  while(b < sb.size){
    bp = bread(dev, BBLOCK(b, sb));
	modified = 0;
	while(bi < BPB && b+bi < sb.size){
      m = 1 << (bi % 8);
	  if(prevbnum == -1) {  // [os-prj5] 완전히 새로운 영역을 할당하는 경우
		if((bp->data[bi/8] & m) == 0) {  // [os-prj5] Is block free?
		  if(staddr == -1)
			staddr = b+bi;
		  bp->data[bi/8] |= m;  // [os-prj5]  Mark block in use.
		  modified = 1;
		  length++;
		  if(needlen <= length){
			log_write(bp);
			brelse(bp);
			for(int i = staddr; i < b + bi; i++)
			  bzero(dev, i);
			*alloclen = length;
			return staddr;
		  }
		}
		else if(staddr != -1){ // [os-prj5] end sequence
		  log_write(bp);
		  brelse(bp);
		  for(int i = staddr; i < b + bi; i++)
			bzero(dev, i);
		  *alloclen = length;
		  return staddr;
		}
	  }
	  else { // [os-prj5] 이전 공간에 이어서 할당하는 경우
		if((bp->data[bi/8] & m) == 0) {  //  [os-prj5] Is block free?
		  if(staddr == -1)
			staddr = b+bi;
		  bp->data[bi/8] |= m;  // [os-prj5]  Mark block in use.
		  modified = 1;
		  length++;
		  if(needlen <= length){
			log_write(bp);
			brelse(bp);
			for(int i = staddr; i < b + bi; i++)
			  bzero(dev, i);
			*alloclen = length;
			return staddr;
		  }
		}
		else{ // [os-prj5] not free
		  if(staddr == -1){ // [os-prj5] not sequence
			brelse(bp);
			return -1;
		  }
		  else{  // [os-prj5] sequence
			log_write(bp);
			brelse(bp);
			for(int i = staddr; i < b + bi; i++) 
			  bzero(dev, i);
			*alloclen = length;
			return staddr;
		  }
		}
	  }
	  ++bi;
	}
	if(modified){ //[os-prj5] 변경 사항 적용
	  log_write(bp);
	  brelse(bp);
	  for(int i = staddr; i < b + bi; i++)
		bzero(dev, i);
	}
	else{
	  brelse(bp);
	}
	b += BPB;
	bi=0;
  }
  if(staddr == -1){ // [os-prj5] 디스크가 꽉참
	panic("CS : no more free block");
	return -1;
  }
  else{  // [os-prj5] 디스크가 꽉 찼고, 할당한 것 반환
	*alloclen = length;
	return staddr;
  }
}

```

 * `bcsalloc`의 블록 탐색 방식은 `balloc`과 동일하지만, 연속된 블록을 반환하여야 하므로 `balloc`보다 코드가 길다. 

 * 이전 블록 주소인 `prevbnum`이 `–1`이 아닌 값으로 설정되었다면, `prevbnum`의 다음 블록 주소로부터 b와 bi 값을 얻어낸다. 이 주소로부터 `needlen`만큼의 연속으로 할당 가능한 블록을 탐색한다. 만일 `prevbnum` 다음 블록이 할당 불가능하다면 `–1`을 반환한다. `needlen`만큼 연속된 블록들을 찾았거나, 탐색 과정중 할당 불가능한 블록을 마주하게 되었다면, 연속적으로 할당한 블록의 길이와 새로 할당한 블록 중 가장 처음 블록의 주소를 반환한다. 

 * `prevbnum`이 `–1`로 설정된 경우에는 더 간단하다. 가장 먼저 할당 가능한 블록을 찾고, 시작 블록으로 설정한다. 이후에 그 시작 블록으로부터 `needlen`만큼 연속으로 할당 가능한 블록들을 탐색한다. `needlen`만큼 연속된 블록들을 찾았거나, 탐색 과정중 할당 불가능한 블록을 마주하게 되었다면, 연속적으로 할당한 블록의 길이와 새로 할당한 블록 중 가장 처음 블록의 주소를 반환한다. 

 * 블록의 할당 정보 비트가 담긴 블록이 수정되었다면 `log_write`와 `brelse`를 순차적으로 호출한다. 만일 수정되지 않았다면 `brelse`만 호출한다.

---

### 파일 읽기 과정
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/image04.png?raw=true" title="image004.png" alt="image004.png"></img><br/>
</center>

 시스템콜 `read`를 이용하여 파일의 내용을 읽을 때의 과정을 표로 나타냈다. 쓰기와 마찬가지로 `sys_read`, `fileread`까지는 코드를 수정하지 않았다. `readi`부터는 코드 내용을 일부 수정했다. 파일이 **CS 파일 시스템**에 해당할 경우 다른 처리를 한다. **CS 파일 시스템**에서 호출하는 디스크 블록 매핑 함수는 `bcsmap`, 일반 파일 시스템에서의 함수는 `bmap`이다.

#### sysfile.c
```c
int
sys_read(void)
{
  struct file *f;
  int n;
  char *p;

  if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  return fileread(f, p, n); //<--this
}
```

#### file.c
```c
int
fileread(struct file *f, char *addr, int n)
{
  int r;

  if(f->readable == 0)
    return -1;
  if(f->type == FD_PIPE)
    return piperead(f->pipe, addr, n);
  if(f->type == FD_INODE){
    ilock(f->ip);
    if((r = readi(f->ip, addr, f->off, n)) > 0) // <--this
      f->off += r;
    iunlock(f->ip);
    return r;
  }
  panic("fileread");
}
```

`sysfile.c`의 `sys_read`와 `file.c`의 `fileread` 코드이다. `fileread`에서 `readi`를 호출한다.

#### fs.c
```c
int
readi(struct inode *ip, char *dst, uint off, uint n)
{
  uint tot, m;
  struct buf *bp;

  if(ip->type == T_DEV){
    if(ip->major < 0 || ip->major >= NDEV || !devsw[ip->major].read)
      return -1;
    return devsw[ip->major].read(ip, dst, n);
  }

  if(off > ip->size || off + n < off)
    return -1;
  if(off + n > ip->size)
    n = ip->size - off;

  // [os-prj5] readi for cs
  if(ip->type == T_CS){
	for(tot=0; tot<n; tot+=m, off+=m, dst+=m){
	  bp = bread(ip->dev, bcsmap(ip, off, n-tot));
	  m = min(n - tot, BSIZE - off%BSIZE);
	  memmove(dst, bp->data + off%BSIZE, m);
	  brelse(bp);
	}
  }
  else{
	for(tot=0; tot<n; tot+=m, off+=m, dst+=m){
	  bp = bread(ip->dev, bmap(ip, off/BSIZE));
	  m = min(n - tot, BSIZE - off%BSIZE);
	  memmove(dst, bp->data + off%BSIZE, m);
	  brelse(bp);
	}
  }
  return n;
}
```

 수정한 `fs.c`의 `readi` 코드이다. `inode`의 `type`이 `T_CS`일 때의 처리가 **CS 파일시스템** 처리이다. `writei`와 반대로 디스크의 내용을 `dst`로 복사한다. 따라서 블록 매핑 함수를 그대로 이용하면 된다.

 `bcsmap`의 경우 `off`에 해당하는 블록이 이미 있을 경우 해당 블록의 주소를 반환한다. 따라서 `readi`가 이상 없이 작동한다.

---
### 파일 제거 과정
<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/image03.png?raw=true" title="image003.png" alt="image003.png"></img><br/>
</center>

 시스템콜 `unlink`를 이용하여 파일을 제거하는 과정을 표로 나타냈다. `iput`에서 `inode`의 `ref`가 1일 경우 `itrunc`를 호출하여 파일을 삭제한다. 따라서 `itrunc`에서 **CS 파일 시스템**을 위한 제거 과정을 추가하면, **CS 파일**을 삭제할 수 있게 된다.

 <center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/image05.png?raw=true" title="image05.png" alt="image05.png"></img><br/>
</center>

 위의 사진은 삭제 과정의 코드들을 나타낸 것이다.

#### fs.c
```c
 static void
itrunc(struct inode *ip)
{
  int i, j;
  struct buf *bp;
  uint addr, length;
  uint *a;
  if(ip->type == T_CS){ // [os-prj5] CS 시스템 전용 삭제 처리
	for(i = 0; i < NDIRECT; i++){
	  if(ip->addrs[i]){
		addr = ip->addrs[i] >> 8;
		length = ip->addrs[i] & 255;
		for(j = 0 ; j < length ; j++)
		  bfree(ip->dev, addr+j);
		ip->addrs[i] = 0;
	  }
	}
	ip->size = 0;
	iupdate(ip);
  }
  else{
	for(i = 0; i < NDIRECT; i++){
	  if(ip->addrs[i]){
		bfree(ip->dev, ip->addrs[i]);
		ip->addrs[i] = 0;
	  }
	}

	if(ip->addrs[NDIRECT]){
	  bp = bread(ip->dev, ip->addrs[NDIRECT]);
	  a = (uint*)bp->data;
	  for(j = 0; j < NINDIRECT; j++){
		if(a[j])
		  bfree(ip->dev, a[j]);
	  }
	  brelse(bp);
	  bfree(ip->dev, ip->addrs[NDIRECT]);
	  ip->addrs[NDIRECT] = 0;
	}

	ip->size = 0;
	iupdate(ip);
  }
}
```
 위 코드처럼 `itrunc`에서 `inode`의 `type`이 `T_CS`일 경우 **CS 파일 시스템**에 맞게 삭제한다. 각 `inode`의 `addr`로부터 블록의 시작 주소와 연속된 블록 개수를 추출하고, 연속된 블록에 대해 `bfree`를 호출한다.

---

### printinfo 구현
 파일 정보를 출력하는 printinfo를 시스템콜로 구현하였다.
```c
//[os-prj5] printinfo
int
sys_printinfo(void)
{
  struct file *f;
  char *fname;
  if(argfd(0, 0, &f) < 0 || argstr(1, &fname) < 0)
    return -1;
  
  int num, length;
  struct inode *ip = f->ip;
  const char *typestr[] = {"X", "DIR", "FILE", "DEV", "CS"};
  cprintf("FILE NAME: %s\n", fname);
  cprintf("INODE NUM: %d\n", ip->inum);
  cprintf("FILE TYPE: %s\n", typestr[ip->type]);
  cprintf("FILE SIZE: %d Bytes\n", ip->size);
  cprintf("DIRECT BLOCK INFO:\n");
  if(ip->type == T_FILE){
	for(int i = 0 ; i < NDIRECT ; i++){
	  if(ip->addrs[i])
		cprintf("[%d] %d\n",i,ip->addrs[i]);
	}
  }
  else if(ip->type == T_CS){
	for(int i = 0 ; i < NDIRECT ; i++){
	  if(!ip->addrs[i])
		continue;
	  num = ip->addrs[i] >> 8;
	  length = ip->addrs[i] & 255;
	  cprintf("[%d] %d (num: %d, length: %d)\n",
		i, ip->addrs[i], num, length);
	}
  }
  cprintf("\n");
  return 0;
}
```

 위와 같이 `printinfo`를 호출하면 
 * 파일 이름
 * inode 번호
 * 파일 타입
 * 파일 크기
 * DIRECT BLOCK 정보
 
 가 출력된다.
 
  기존 파일 시스템의 경우 `DIRECT BLOCK`의 정보로써 사용하고 있는 `block`에 저장된 내용이 출력되고, **CS 파일 시스템**일 경우 내용뿐만 아니라 블록 시작 번호, 연속된 블록 개수 정보가 같이 출력된다.

#### syscall.c
```c
extern int sys_printinfo(void); // [os-prj5] printinfo
```
```c
[SYS_printinfo]   sys_printinfo,  // [os-prj5] printinfo
```
 `printinfo` 시스템콜을 추가하기 위해 `syscall.c`에 해당 시스템콜을 위한 코드를 추가했다.

#### syscall.h
```h
#define SYS_printinfo  22
```

#### user.h
```h
int printinfo(int, const char*); // [os-prj5] printinfo
```

#### usys.S
```S
SYSCALL(printinfo)
```
 `syscall.h`, `user.h`, `usys.S`에도 `printinfo` 시스템콜을 위한 코드를 추가했다.

---
### 테스트 파일 실행
#### 1. 연속적으로 데이터 쓰기

CS 기반 파일을 생성하여 데이터를 1024B씩 130번 write 한다. 이후 이 파일에 대해 `printinfo`를 호출한다.

 <center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p1.png?raw=true" title="p1.png" alt="p1.png"></img><br/>
</center>

오른쪽 사진과 같이 2개의 **DIRECT BLOCK**을 사용하여 할당한 것을 확인할 수 있다.

#### 2. 불연속적으로 데이터 쓰기

 1과 마찬가지로 CS 기반 파일을 생성하여 데이터를 1024B씩 130번 write한다. 단, 51번째에 기존 파일 시스템 기반 파일을 생성하여 데이터를 1024B씩 2번 write한 뒤 이 파일에 대해 `printinfo`를 호출한다. CS파일도 130번 write를 한 뒤 `printinfo`를 호출한다. 

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p2.png?raw=true" title="p2.png" alt="p2.png"></img><br/>
</center>

오른쪽 사진과 같이 출력된다. 일반 파일은 4개의 `DIRECT` 블록이 할당되었다. 이는 2048B만큼 데이터를 write하였기 때문이다. CS 기반 파일은 1번부터 51번째까지 총 51KB를 write했다. 따라서 0번째 `direct block`에 102개의 연속 블록이 할당되었다. 이후 새로운 `direct block`을 할당받아 52번부터 130번까지 총 79KB를 write했다. 따라서 158개의 연속 블록이 할당되었다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p3.png?raw=true" title="p3.png" alt="p3.png"></img><br/>
</center>

 `ls`와 `wc` 명령어를 사용하여 파일의 크기를 확인하였다. 모두 정상적으로 쓰기 작업이 수행되었다.

#### 3. 파일 읽기

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p4.png?raw=true" title="p4.png" alt="p4.png"></img><br/>
</center>

정상적으로 읽히는 것을 확인할 수 있었다.

#### 4. 파일 제거

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p5.png?raw=true" title="p5.png" alt="p5.png"></img><br/>
</center>
 정상적으로 제거되는 것을 확인할 수 있었다.

#### 5. 할당할 수 있는 데이터 블록이나 direct 블록의 범위를 초과할 경우 범위 내까지만 데이터 할당 후 에러 메시지 출력



할당할 수 있는 데이터 블록을 초과한 경우 `bcsalloc`에서 `panic`을 호출한다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p6.png?raw=true" title="p6.png" alt="p6.png"></img><br/>
</center>

또는 CS 파일 시스템의 블록 포인터를 모두 사용해서 더 이상 할당이 불가능하면 `bcsmap`에서 다음과 같이 `panic`이 호출된다.

<center>
        <img src="https://github.com/simjeehoon/src_repository/blob/master/xv6-public/os-prj5/p7.png?raw=true" title="p7.png" alt="p7.png"></img><br/>
</center>
