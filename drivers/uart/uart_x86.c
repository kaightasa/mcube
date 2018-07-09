/**
 * @file drivers/uart/uart_x86.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

static unsigned long uart_wait_tsc = 0x10000;

uint8_t uart_pol_getc(uint8_t ch)
{
	while (!(inb(COM1_LINE_STATUS) & UART_LINE_STATUS_RECV_DATA))
		;
	wait(uart_wait_tsc);
	return inb(COM1_START);
}

void uart_pol_putc(uint8_t c, int32_t ch)
{
	while (!(inb(COM1_LINE_STATUS) & UART_LINE_STATUS_SEND_DATA_COMP))
    ;
	wait(uart_wait_tsc);
	outb(c, COM1_START);
	wait(uart_wait_tsc);
	/* wait until sending character */
	while (!(inb(COM1_LINE_STATUS) &
					 (UART_LINE_STATUS_SEND_DATA_EMPTY | UART_LINE_STATUS_BREAK_RECV)))
		;
	wait(uart_wait_tsc);
}


void init_uart(void)
{
	/* set speed */
	outb(UART_LINE_CTRL_DLAB, COM1_LINE_CTRL);
	//outb(BAUDRATE_MSB(38400), COM1_BAUDRATE_MSB);
	outb(BAUDRATE_38400_MSB, COM1_BAUDRATE_MSB);
	//outb(BAUDRATE_LSB(38400), COM1_BAUDRATE_MSB);
	outb(BAUDRATE_38400_LSB, COM1_BAUDRATE_LSB);
	/* # of data bits */
	outb(UART_LINE_CTRL_SEND_RECV_DATA_8BIT, COM1_LINE_CTRL);
	/* control pin */
	outb(UART_MODEM_CTRL_INT_ENABLE | UART_MODEM_CTRL_ASSERT_RTS |
			 UART_MODEM_CTRL_ASSERT_DTR, COM1_MODEM_CTRL);
	/* clear interrupt */
	//	outb(0x00, COM1_INT_ENABLE);
	/* init uart_data */
	uart_data[0].ch = 0;
	uart_data[0].baudrate = 38400;
}
