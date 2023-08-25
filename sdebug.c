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
