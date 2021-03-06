/**
 * @file arch/axis/irq.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

/**
 * @fn static void increment_wait_interrupt_program_counter(void)
 * @brief increment wait interrupt program counter.
 */
static void increment_wait_interrupt_program_counter(void)
{
  extern unsigned long __wait_until_next_interrupt;

  if (get_interrupt_program_counter()
      == (unsigned long) &__wait_until_next_interrupt) {
    /* add instruction length to interrupt program counter. */
    set_interrupt_program_counter((unsigned long) &__wait_until_next_interrupt + 4);
  }
}


void wait_until_next_interrupt(void)
{
  asm volatile("__wait_until_next_interrupt:");
  asm volatile("wi");
}

void do_switch_thread(void)
{
  unsigned long cpu = get_cpu_id();
  PDEBUG("%s()\n", __func__);

  if (current_th[cpu] != prev_th[cpu]) {
    /* save program counter. */
    prev_th[cpu]->interrupt_program_counter = get_interrupt_program_counter();
    /* save $fp for Clang/GCC. */
    asm volatile("move %0, $fp" : "=r"(prev_th[cpu]->current_fp));
    /* save $sp for GCC. */
    asm volatile("move %0, $sp" : "=r"(prev_th[cpu]->current_sp));
    printk("cpu = %lu prev_th: id = %lu current_fp = 0x%lx current_sp = 0x%lx\n",
           cpu, prev_th[cpu]->id, prev_th[cpu]->current_fp, prev_th[cpu]->current_sp);
    prev_th[cpu] = current_th[cpu];

    if (!(current_th[cpu]->thflags & THFLAGS_START_TH)) {
      /* start thread. */
      current_th[cpu]->thflags |= THFLAGS_START_TH;
      PDEBUG("get_context_top(current_th[%lu])) = 0x%lx\n",
             cpu, (unsigned long) get_context_top(current_th[cpu]));
      set_interrupt_program_counter((unsigned long) current_th[cpu]->run_func);
      PDEBUG("get_interrupt_program_counter() = 0x%lx\n",
             get_interrupt_program_counter());
      asm volatile("move $sp, %0" :: "r"(get_context_top(current_th[cpu])));
      asm volatile("ert");
    }

    /* resume program counter and frame/stack pointer. */
    set_interrupt_program_counter(current_th[cpu]->interrupt_program_counter);
    printk("cpu = %lu current_th: id = %lu current_fp = 0x%lx current_sp = 0x%lx\n",
           cpu, current_th[cpu]->id, current_th[cpu]->current_fp,
           current_th[cpu]->current_sp);
    asm volatile("move $sp, %0" :: "r"(current_th[cpu]->current_sp));
    asm volatile("move $fp, %0" :: "r"(current_th[cpu]->current_fp));
  }
}

int handle_timer_interrupt(void)
{
  unsigned long cpu = get_cpu_id();
  PDEBUG("%s()\n", __func__);
  printk("sys_jiffies = %lu\n", sys_jiffies);
  //    printk("get_interrupt_program_counter() = 0x%lx\n", get_interrupt_program_counter());
  //    printk("__wait_until_next_interrupt = 0x%lx\n", &__wait_until_next_interrupt);
  //  printk("get_timer_count() = %d\n", get_timer_count());
  pdebug_array(run_tq[cpu].array);

  if (current_th[cpu] != &kernel_th[cpu]) {
    PDEBUG("current_th: id = %lu sched.remaining = %ld\n",
           current_th[cpu]->id, current_th[cpu]->sched.remaining);
#if 1
    /* set remaining to forcelly zero for debug. */
    current_th[cpu]->sched.remaining = 0;
#else
    /* subtract elapsed time from remaining. */
    current_th[cpu]->sched.remaining -= CPU_CLOCK_TO_USEC(get_timer_period()
                                                          - current_th[cpu]->sched.begin_cpu_time);
#endif

    if (current_th[cpu]->sched.remaining <= 0) {
      do_end_job(current_th[cpu]);
    }
  }

  update_jiffies();

  /* clear timer interrupt */
  set_timer_status(1);

  if (get_current_jiffies() >= sched_time) {
    printk("sched_time expires!!!!\n");
    sched_end = true;
    disable_timer_interrupt();
    current_th[cpu] = &kernel_th[cpu];
  } else {
    do_release();
    do_sched();
  }

  increment_wait_interrupt_program_counter();
  return 0;
}

int handle_dmac_interrupt(void)
{
  PDEBUG("%s()\n", __func__);
  increment_wait_interrupt_program_counter();
  disable_dmac_interrupt();
  set_dmac_status_clear(1);
  return 0;
}

void do_sched_by_software_interrupt(void)
{
  unsigned long cpu = get_cpu_id();
  unsigned long current_timer_count;
  current_timer_count = get_timer_count();

  if (current_th[cpu] != &kernel_th[cpu]) {
    current_th[cpu]->sched.remaining -= CPU_CLOCK_TO_USEC(current_timer_count
                                                          - current_th[cpu]->sched.begin_cpu_time);
  }

  if (current_th[cpu] != &kernel_th[cpu]) {
    /* end current_th and call do_sched() */
    do_end_job(current_th[cpu]);
  }

  /* software interrupt for scheduler */
  do_sched();
}

int handle_software_interrupt(unsigned long id)
{
  PDEBUG("%s(): id = %lu\n", __func__, id);
  set_common_interrupt_clear(id);

  /* do processing... */
  switch (id) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
    if (Callback[id]) {
      Callback[id]();
    }

    break;

  default:
    printk("Error: Unknown id %lu\n", id);
    break;
  }

  return 0;
}

asmlinkage int do_irq(struct full_regs *regs)
{
  unsigned long status;
  unsigned long id;
  disable_local_irq();
  /* check if this is timer interrupt. */
  status = get_interrupt_status();
  printk("do_irq()\n");
  printk("get_interrupt_status() = 0x%lx\n", status);

  if (status & (0x1 << 0)) {
    handle_timer_interrupt();
    goto end;
  }

  /* check if this is DMAC interrupt. */
  if (status & (0x1 << 1)) {
    handle_dmac_interrupt();
    goto end;
  }

  /* check if this is software interrupt. */
  status = get_common_interrupt_status();
  printk("get_common_interrupt_status() = 0x%lx\n", status);
  id = ffb32(status);

  if (id > NR_SOFTWARE_INTERRUPTS) {
    printk("Error: Unknown id %lu\n", id);
    dump_registers(regs);
  } else {
    handle_software_interrupt(id);
  }

end:
  do_switch_thread();
  PDEBUG("get_interrupt_program_counter() = 0x%lx\n",
         get_interrupt_program_counter());
  //  asm volatile("move %0, $sp" : "=r"(tmp));
  //  printk("sp = 0x%lx\n", tmp);
  enable_local_irq();
  return IRQ_HANDLED;
}

