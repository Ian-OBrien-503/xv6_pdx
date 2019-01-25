#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char * argv [])
{
  // start timer once command is initaited
  int timer = uptime();
  // fork to run command
  int pid = fork();
  // check return value of child process
  if(pid == 0){
    // if child process we throw error
    if(exec(argv[1], &argv[1])<0)
      printf(1, "\n\tDANGER WILL ROBINSION, ERROR!\n");
  }
  if(pid == -1){
      printf(1, "\n\tDANGER WILL ROBINSION, FAILURE!\n");
  }
  else{ 
    // else wait for program to finish running and print it's data
    if(wait() >=0)
      printf(1, "%s ran in %d.%d seconds\n", argv[1], ((uptime() - timer)/1000), ((uptime() - timer)%1000));
  }
  exit();
}

#endif  //cs333_P2
