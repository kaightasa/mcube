/**
 * @file arch/aarch64/dump.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>


void dump_registers(struct full_regs *regs)
{
  for (int i = 0; i < 32; i += 2) {
    printk("x%02d: 0x%016lx  x%02d: 0x%016lx\n",
           i, regs->gpr[i], i + 1, regs->gpr[i + 1]);
  }
}

