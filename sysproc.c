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

// intialize uints to generate unique uid and pid in setuid() and getuid()
#ifdef CS333_P2
uint uid_gen = 0;
uint gid_gen = 0;
#endif //CS333_P2

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
uint
sys_getuid(void)
{
  //if(argptr(0, (void*)&p, sizeof(struct proc)) < 0)
  //  return -1;
  //if(p->uid < 0 || p->uid > 32767)
  //  return -1;
  //else
    return proc->uid;
}
#endif

#ifdef CS333_P2
// function checks for valid gid and returns error if not valid else it  returns process gid
uint
sys_getgid(void)
{

  //if(argptr(0, (void*)&p, sizeof(struct proc)) < 0)
  //  return -1;
  //if(p->gid < 0 || p->gid > 32767)
  //  return -1;
  //else
    return proc->gid;
}
#endif

#ifdef CS333_P2
// function checks for null ppid and if it is gives it the pid as the ppid, this is only the 
// case for the init process other than that it returns the "ppid" 
uint
sys_getppid(void)
{
  struct proc *p;

  //if(argptr(0, (void*)&p, sizeof(struct proc)) < 0)
  //  return -1;
  if(proc->parent == NULL)
    return proc->pid; 
  return proc->parent->pid;
}
#endif

#ifdef CS333_P2
// function checks for valid range of available uid's if all are taken then return error flag
// else set the uid to the next available one
int
sys_setuid(void)
{

  //if(argptr(0, (void*)&p, sizeof(struct proc)) < 0)
  //  return -1;
  if(uid_gen < 0 || uid_gen > 32767)
    return -1;
  else{
    ++uid_gen;
    proc->uid = uid_gen;
    return proc->uid;
  }
}
#endif

#ifdef CS333_P2
// function checks for valid range of gid avaiable if all are taken then return error flag
// else set the gid to the next available one
int
sys_setgid(void)
{
  //if(argptr(0, (void*)&p, sizeof(struct proc)) < 0)
  //  return -1;
  if(gid_gen < 0 || gid_gen > 32767)
    return -1;
  else{
    ++gid_gen;
    proc->gid = gid_gen;
    return proc->gid;
  }
}
#endif

