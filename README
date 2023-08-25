xv6 살펴보기
===

xv6로 작업하기에 앞서 xv6를 살펴본다.


## 개요
 교육용 운영체제 xv6를 설치하고 컴파일하여 쉘 명령어를 추가한다. 명령어를 추가하는 과정을 통해 xv6 환경에 익숙해지도록 한다.

## 상세설계
### 1. xv6 설치 및 컴파일

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

