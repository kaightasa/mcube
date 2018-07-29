/**
 * @file include/arm/machine_raspi3/timer.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef	__MCUBE_ARM_MACHINE_RASPI3_TIMER_H__
#define	__MCUBE_ARM_MACHINE_RASPI3_TIMER_H__


#define TIMER_CTRL_REG (GENERIC_TIMER_BASE + 0x0)
/* 0x4 reserved */
#define TIMER_CORE_TIMER_PRESCALER (GENERIC_TIMER_BASE + 0x8)
#define TIMER_GPU_INTERRUPTS_ROUTING (GENERIC_TIMER_BASE + 0xc)
#define TIMER_PERFORMANCE_MONITOR_INTERRUPTS_ROUTING_SET (GENERIC_TIMER_BASE + 0x10)
#define TIMER_PERFORMANCE_MONITOR_INTERRUPTS_ROUTING_CLEAR (GENERIC_TIMER_BASE + 0x14)
/* 0x18 reserved */
#define TIMER_CORE_TIMER_ACCESS_LOWER_32BITS (GENERIC_TIMER_BASE + 0x1c)
#define TIMER_CORE_TIMER_ACCESS_HIGHER_32BITES (GENERIC_TIMER_BASE + 0x20)
#define TIMER_LOCAL_INTERRUPT_ROUTING (GENERIC_TIMER_BASE + 0x24)
/* 0x28 reserved */
#define TIMER_AXI_OUTSTANDING_COUNTERS (GENERIC_TIMER_BASE + 0x2c)
#define TIMER_AXI_OUTSTANDING_IRQ (GENERIC_TIMER_BASE + 0x30)
#define TIMER_LOCAL_TIMER_CTRL_STATUS (GENERIC_TIMER_BASE + 0x34)
#define TIMER_LOCAL_TIMER_WRITE_FLAGS (GENERIC_TIMER_BASE + 0x38)
/* 0x3c reserved */
#define TIMER_CORE0_TIMERS_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x40)
#define TIMER_CORE1_TIMERS_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x44)
#define TIMER_CORE2_TIMERS_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x48)
#define TIMER_CORE3_TIMERS_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x4c)
#define TIMER_CORE0_MAILBOXES_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x50)
#define TIMER_CORE1_MAILBOXES_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x54)
#define TIMER_CORE2_MAILBOXES_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x58)
#define TIMER_CORE3_MAILBOXES_INTERRUPT_CTRL (GENERIC_TIMER_BASE + 0x5c)
#define TIMER_CORE0_IRQ_SOURCE (GENERIC_TIMER_BASE + 0x60)
#define TIMER_CORE1_IRQ_SOURCE (GENERIC_TIMER_BASE + 0x64)
#define TIMER_CORE2_IRQ_SOURCE (GENERIC_TIMER_BASE + 0x68)
#define TIMER_CORE3_IRQ_SOURCE (GENERIC_TIMER_BASE + 0x6c)
#define TIMER_CORE0_FIQ_SOURCE (GENERIC_TIMER_BASE + 0x70)
#define TIMER_CORE1_FIQ_SOURCE (GENERIC_TIMER_BASE + 0x74)
#define TIMER_CORE2_FIQ_SOURCE (GENERIC_TIMER_BASE + 0x78)
#define TIMER_CORE3_FIQ_SOURCE (GENERIC_TIMER_BASE + 0x7c)
#define TIMER_CORE0_MAILBOX0_WRITE_SET (GENERIC_TIMER_BASE + 0x80)
#define TIMER_CORE0_MAILBOX1_WRITE_SET (GENERIC_TIMER_BASE + 0x84)
#define TIMER_CORE0_MAILBOX2_WRITE_SET (GENERIC_TIMER_BASE + 0x88)
#define TIMER_CORE0_MAILBOX3_WRITE_SET (GENERIC_TIMER_BASE + 0x8c)
#define TIMER_CORE1_MAILBOX0_WRITE_SET (GENERIC_TIMER_BASE + 0x90)
#define TIMER_CORE1_MAILBOX1_WRITE_SET (GENERIC_TIMER_BASE + 0x94)
#define TIMER_CORE1_MAILBOX2_WRITE_SET (GENERIC_TIMER_BASE + 0x98)
#define TIMER_CORE1_MAILBOX3_WRITE_SET (GENERIC_TIMER_BASE + 0x9c)
#define TIMER_CORE2_MAILBOX0_WRITE_SET (GENERIC_TIMER_BASE + 0xa0)
#define TIMER_CORE2_MAILBOX1_WRITE_SET (GENERIC_TIMER_BASE + 0xa4)
#define TIMER_CORE2_MAILBOX2_WRITE_SET (GENERIC_TIMER_BASE + 0xa8)
#define TIMER_CORE2_MAILBOX3_WRITE_SET (GENERIC_TIMER_BASE + 0xac)
#define TIMER_CORE3_MAILBOX0_WRITE_SET (GENERIC_TIMER_BASE + 0xb0)
#define TIMER_CORE3_MAILBOX1_WRITE_SET (GENERIC_TIMER_BASE + 0xb4)
#define TIMER_CORE3_MAILBOX2_WRITE_SET (GENERIC_TIMER_BASE + 0xb8)
#define TIMER_CORE3_MAILBOX3_WRITE_SET (GENERIC_TIMER_BASE + 0xbc)
#define TIMER_CORE0_MAILBOX0_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xc0)
#define TIMER_CORE0_MAILBOX1_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xc4)
#define TIMER_CORE0_MAILBOX2_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xc8)
#define TIMER_CORE0_MAILBOX3_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xcc)
#define TIMER_CORE1_MAILBOX0_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xd0)
#define TIMER_CORE1_MAILBOX1_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xd4)
#define TIMER_CORE1_MAILBOX2_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xd8)
#define TIMER_CORE1_MAILBOX3_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xdc)
#define TIMER_CORE2_MAILBOX0_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xe0)
#define TIMER_CORE2_MAILBOX1_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xe4)
#define TIMER_CORE2_MAILBOX2_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xe8)
#define TIMER_CORE2_MAILBOX3_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xec)
#define TIMER_CORE3_MAILBOX0_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xf0)
#define TIMER_CORE3_MAILBOX1_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xf4)
#define TIMER_CORE3_MAILBOX2_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xf8)
#define TIMER_CORE3_MAILBOX3_READ_WRITE_HIGH_TO_CLEAR (GENERIC_TIMER_BASE + 0xfc)


#endif /*	__MCUBE_ARM_MACHINE_RASPI3_TIMER_H__ */

