#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit() //Lab1
{ 
  int status;
  argint(0, &status);
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void) //Lab1
{
  int *status;
  if (argptr(0, (void*)&status, sizeof(*status)) < 0) {
    return -1;
  }
  return wait(status);
} 

int
sys_waitpid(void) //Lab1
{ 
  int pid;
  argint(0, &pid);
  int *status;
  if (argptr(1, (void*)&status, sizeof(*status)) < 0) {
    return -1;
  }
  return waitpid(pid, status, 0); 
} 

void
sys_changepriority(void) //Lab2
{
  int priority;
  argint(0, &priority);
  return changepriority(priority);
}

int 
sys_getpriority(void) //Lab2
{
  return getpriority();
}

void
sys_yield(void) //Lab2
{
  return yield();
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
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
