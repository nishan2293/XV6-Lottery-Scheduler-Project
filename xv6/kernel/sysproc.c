#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;


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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/*modifications introduced by nsd160330 */

int sys_settickets(void)
{
  int number_of_tickets;

  // Retrieve the number of tickets.
  if(argint(0, &number_of_tickets) < 0)
    return -1;

  // Validate the ticket number.
  if(number_of_tickets < 1)
    return -1;

  // Set the tickets for the current process.
  proc->tickets = number_of_tickets;

  return 0;
}

int sys_getpinfo(void)
{
  struct pstat *info;
  struct proc *current_proc;
  int index;

  // Retrieve the pointer to the information table.
  argptr(0, (void *)&info, sizeof(*info));

  // Validate the provided pointer.
  if(!info)
    return -1;

  index = 0;

  // Iterate over the process table to gather info.
  for(current_proc = ptable.proc; current_proc < &ptable.proc[NPROC]; current_proc++)
  {
    if(current_proc->state != UNUSED)
    {
      info->inuse[index] = current_proc->inuse;
      info->tickets[index] = current_proc->tickets;
      info->pid[index] = current_proc->pid;
      info->ticks[index] = current_proc->ticks;
    }
    index++;
  }

  return 0;
}
/* End of nsd160330  modifications */

