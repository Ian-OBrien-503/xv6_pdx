#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#ifdef PDX_XV6
#include "pdx-kernel.h"
#endif // PDX_XV6
#ifdef CS333_P2
#include "uproc.h"
#endif  // CS333_P2


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      return -1;
    }
    sleep(&ticks, (struct spinlock *)0);
  }
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  xticks = ticks;
  return xticks;
}

#ifdef PDX_XV6
// Turn off the computer
int
sys_halt(void)
{
  cprintf("Shutting down ...\n");
  outw( 0x604, 0x0 | 0x2000);
  return 0;
}
#endif // PDX_XV6

#ifdef CS333_P1
int
sys_date(void)
{
  struct rtcdate *d;

  if(argptr(0, (void*)&d, sizeof(struct rtcdate)) < 0)
    return -1;
  else{
    cmostime(d);
    return 0;
  }
}
#endif //cs333_P1

#ifdef CS333_P2
// function checks for valid uid and returns error if not valid else it returns process uid
int
sys_getuid(void)
{
  return myproc()->uid;
}
#endif

#ifdef CS333_P2
// function checks for valid gid and returns error if not valid else it  returns process gid
int
sys_getgid(void)
{
  return myproc()->gid;
}
#endif

#ifdef CS333_P2
// function checks for null ppid and if it is gives it the pid as the ppid, this is only the 
// case for the init process other than that it returns the "ppid" 
int
sys_getppid(void)
{
  if(myproc()->parent == NULL)
    return myproc()->pid; 
  else
    return myproc()->parent->pid;
}
#endif

#ifdef CS333_P2
// function checks for valid range of available uid's if all are taken then return error flag
// else set the uid to the next available one
int
sys_setuid(void)
{
  int test;
  if(argint(0, &test)<0)
    return -1;
  if(test < 0 || test >32767)
    return -1;
  else{
    myproc()->uid = test;
    return 0;
  }
}
#endif

#ifdef CS333_P2
// function checks for valid range of gid avaiable if all are taken then return error flag
// else set the gid to the next available one
int
sys_setgid(void)
{
  int test;
  if(argint(0, &test)<0)
    return -1;
  if(test < 0 || test >32767)
    return -1;
  else{
    myproc()->gid = test;
    return 0;
  }
}
#endif

// function is called from ps.c to pass arguments to getprocs in proc.c
#ifdef CS333_P2
int 
sys_getprocs(void)
{
  struct uproc *p;
  int max;

  if(argint(0,&max)<0){
    return -1;
  }
  if(argptr(1, (void*)&p, max*sizeof(struct uproc)<0))
    return -1;
  return getprocs(max, p);
}
#endif  //CS333_P2

#ifdef CS333_P4
int
sys_setpriority(void)
{
  //find proc in runnable, running, sleeping, or embryo and update pid
  //return 0 on success return -1 for fail
  int priority;
  int pid;
  // if specify negative pid
  if(argint(0, &pid) < 0)
    return -1;
  // if specify negative priority
  if(argint(1, &priority) < 0)
    return -1;
  // if specify priority greater than max
  if(priority > MAXPRIO)
    return -1;
  else
    return setpriority(pid, priority);
}

int
sys_getpriority(void)
{
  //return pid if proc exists return 01 if failure
  int test;
  // if specify a negative pid we fail
  if(argint(0, &test) < 0)
    return -1;
  else 
    return getpriority(test);
}
#endif  //CS333_P4
