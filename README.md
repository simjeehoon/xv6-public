xv6에 CS File System을 추가
===

xv6에 새로운 **CS 파일 시스템**을 추가한다.


## 개요
 CS 파일 시스템은 파일에 연속적인 데이터 블록을 할당함으로써, 파일의 최대 크기를 늘리고 디스크 탐색시간을 단축하는 파일 시스템이다. 이번 과제에서는 XV6의 기존 파일 시스템은 그대로 유지하면서 CS 파일 시스템을 추가한다. CS 파일 시스템을 이용할 때, inode 구조체에 있는 direct block에 기존 파일 시스템과 다른 방식으로 값을 부여한다.

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