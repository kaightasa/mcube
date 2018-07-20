/**
 * @file arch/x86/init.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>


void init_arch(void)
{
#if 1
  disable_interrupt();
  /* initialize console */
  init_tty();
  //  tty_set_textcolor(TTY_ID, TEXTCOLOR_LTGRAY, TEXTCOLOR_BLACK);
  tty_clear(TTY_ID);
  /* initialize memory */
  init_acpi();
  init_pmap();
  init_page();
  //print_pmap();
  init_irq();
  init_exception();

  //  timer_init(100);

  tty_clear(TTY_ID);
  //  init_keyboard();
  //  enable_interrupt();
  //  print_cpu_brand();
  print_cpu_frequency();
  //  print_vendor_id();
  for (;;)
    ;
#else
  //	init_shell();
  init_uart();
	init_console();

	init_key();
  //	init_processor();

	init_buffer();

  //	init_ipc();
	/* use printk after init_ipc() */

  //	init_bss();

  //	init_overhead();

	init_dsctbl();
	init_irq();

#if CONFIG_DEV_MOUSE
	init_mouse();
#endif /* CONFIG_DEV_MOUSE */

	init_apic();
  init_timer(0);

	init_cache(); 

	/* enable interrupt */
	sti();
#endif
}


void exit_arch(void)
{
}
