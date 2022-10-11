#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5
#define PRINT_CYCLE 100000000
#define TOTAL_COUNTER 500000000

void sdebug_func(void)
{
  int i;
  int pid;
  long start;
  volatile long counter = 0;

  printf(1, "start sdebug command\n");
  for(i = 1 ; i <= PNUM ; i++){
	weightset(i); // [20172644] Set weight to i
	pid = fork();
	start = uptime(); // [20172644] Check start time
	if(pid == 0){ // [20172644] Child process
	  /*
		 [20172644] Count PRINT_CYCLE
		 and print this process information.
	  */
	  while(counter < PRINT_CYCLE)
		++counter;
	  printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), i, (uptime()-start)*10);

	  /*
		 [20172644] Count TOTAL_COUNTER
		 and exit this process.
	  */
	  while(counter < TOTAL_COUNTER)
		++counter;
	  printf(1, "PID: %d terminated\n", getpid());
	  exit();
	}
	else if(pid > 0) // [20172644] Parent process
	  continue; // [20172644] Loop for making child process.
	else{ // Error
	  printf(1, "ERROR: fork\n");
	  break;
	}
  }
  for(i = 1 ; i <= PNUM ; i++) // [20172644] Wait childs.
	wait();

  printf(1, "end of sdebug command\n");
}

int main(void)
{
  sdebug_func();
  exit();
}
