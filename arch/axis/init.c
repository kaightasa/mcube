/**
 * @file arch/axis/init.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>


void init_irq(void)
{
  int i;
  set_interrupt_vector_base_address((unsigned long) interrupt_vector);

  for (i = 0; i < NR_SOFTWARE_INTERRUPTS; i++) {
    enable_software_interrupt(i);
  }

  register_callback_handler(do_sched_by_software_interrupt, 0);
  enable_previous_irq();
  enable_local_irq();
}

void exit_irq(void)
{
  disable_local_irq();
  disable_previous_irq();
}

void clear_bss(void)
{
  extern unsigned long __bss_begin, __bss_end;
  printk("&__bss_begin = 0x%lx &__bss_end = 0x%lx\n", &__bss_begin, &__bss_end);
  memset64(&__bss_begin, 0, (&__bss_end - &__bss_begin) / sizeof(unsigned long));
}

/**
 * The init_arch() function initializes architecture-dependent features.
 */
void init_arch(void)
{
  unsigned long cpu = get_cpu_id();
  //  clear_bss();
  init_spinlock();
  init_irq();
  init_cpu();


  /* One-core one-thread execution model (serialized cluster + cpu ID == thread ID). */
  current_th[cpu] = &kernel_th[cpu];
  current_th[cpu]->id = cpu;

  // NOTE: if needed
  //  init_kmalloc();
  //  init_socket();
}

void init_arch_ap(void)
{
  unsigned long cpu = get_cpu_id();
  /* One-core one-thread execution model (serialized cluster + cpu ID == thread ID). */
  current_th[cpu]->id = cpu;
}

/**
 * The exit_arch() function exits architecture-dependent features.
 */
void exit_arch(void)
{
  exit_irq();
}

void exit_arch_ap(void)
{
  exit_irq();
}
