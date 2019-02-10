/**
 * @file arch/x86/thread.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>



void __attribute__((noreturn)) run_user_thread(void)
{
#if 0
  unsigned long cpu = get_cpu_id();
  void *ret = NULL;
  unsigned long rsp;
  printk("run_user_thread()\n");
  printk("current_th[cpu]->id = %lu\n", current_th[cpu]->id);
  asm volatile("mov %%rsp, %0" : "=r"(rsp));
  printk("rsp = 0x%lx\n", rsp);
  if (current_th[cpu]->run_user_func) {
    ret = (*current_th[cpu]->run_user_func)(current_th[cpu]->arg);
  }
  if (ret) {
    printk("ret = 0x%lx\n", (unsigned long) ret);
  }
#endif
  hlt();
  inf_loop();
}

void wait(unsigned long count)
{
  while (get_current_cpu_time() < count)
    ;
}


void __attribute__((noreturn)) exit(int status)
{
  cli();
  hlt();
  inf_loop();
}
