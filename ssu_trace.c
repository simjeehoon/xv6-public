#include "types.h"
#include "stat.h"
#include "user.h"

char *execargv[256];

int main(int argc, char *argv[]){
  int i;
  if(argc <= 2){
	printf(1, "usage: %s [mask] [command]\n", argv[0]);
	exit();
  }
  trace(atoi(argv[1]));
  for(i=2;i<argc;i++){
	execargv[i-2] = argv[i];
  }
  exec(argv[2], execargv);
  exit();
}
