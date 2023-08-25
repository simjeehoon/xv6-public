xv6에 시스템콜 추가하기
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
