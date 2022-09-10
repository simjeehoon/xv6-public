#include "types.h"
#include "stat.h"
#include "user.h"

int maxrow;
int currow=0;
int ismax=0;

char buf[512];

void
cat(int fd)
{
  int n;
  int i;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
	//check '\n' in buf read
	for(i=0;i<n;i++){
	  if(buf[i] == '\n')
		++currow;
	  if(maxrow <= currow){//over maxrow
		++i;
		ismax = 1;
		break;
	  }
	}
    if (write(1, buf, i) != i) {
      printf(1, "cat: write error\n");
      exit();
    }
	if(ismax)
	  break;
	else
	  memset(buf, 0, sizeof(buf));
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 2){
    printf(1, "usage: %s number_of_line files...\n", argv[0]);
    exit();
  }
  maxrow = atoi(argv[1]);
  for(i = 2; i < argc; i++){
    if(ismax)//over maxrow
		break;
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
