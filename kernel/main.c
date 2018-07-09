/**
 * @file kernel/main.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

unsigned int Debug = FALSE;
//unsigned int Debug = TRUE;

unsigned long CPU_CLOCK;
unsigned long CPU_CLOCK_MHZ_PER_USEC;
#if !CONFIG_ARCH_AXIS
double CPU_USEC_PER_CLOCK_MHZ;
double CPU_CLOCK_MHZ_PER_NSEC;
double CPU_NSEC_PER_CLOCK_MHZ;
#endif /* !CONFIG_ARCH_AXIS */


int main(int argc, char *argv[])
{
#if 0
  for (;;)
    ;
#endif
  init_arch();
  //  putchar('b');
  //  console_write("hoge", 4, NULL);
  //  putchar('c');
  printk("main()\n");
  init_rq();
  printk("main()2\n");
  init_sched();
  printk("main()3\n");
  
  user_main();
  exit_arch();
  return 0;
}

