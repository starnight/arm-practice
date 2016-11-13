#if MACHINE==raspi2
#define	PBASE		0x3F000000
#elif MACHINE==raspi
#define	PBASE		0x20000000
#endif
#define	GPIO_BASE	(PBASE + 0x00200000)
#define UART0_BASE	(PBASE + 0x00201000)

volatile unsigned int * const GPFSEL0 = (unsigned int *)(GPIO_BASE + 0x0);

volatile unsigned int * const GPPUD = (unsigned int *)(GPIO_BASE +0x94);
volatile unsigned int * const GPPUDCLK0 = (unsigned int *)(GPIO_BASE + 0x98);

volatile unsigned int * const UART0DR = (unsigned int *)(UART0_BASE + 0x0);
volatile unsigned int * const UART0FR = (unsigned int *)(UART0_BASE + 0x18);
volatile unsigned int * const UART0IBRD = (unsigned int *)(UART0_BASE + 0x24);
volatile unsigned int * const UART0FBED = (unsigned int *)(UART0_BASE + 0x28);
volatile unsigned int * const UART0LCRH = (unsigned int *)(UART0_BASE + 0x2C);
volatile unsigned int * const UART0CR = (unsigned int *)(UART0_BASE + 0x30);
volatile unsigned int * const UART0IMSC = (unsigned int *)(UART0_BASE + 0x38);

void uart_init() {
	/* Disable UART0. */
	*UART0CR = 0;

	/* Disable pull up/down for all GPIO pin. */
	*GPPUD = 0;

	/* Divider = 3000000 / (16 * 115200) = 1.627 */
	/* Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40. */
	*UART0IBRD = 1;
	*UART0FBED = 40;

	/* 8 data bits, no parirty bit, 1 stop bit. */
	*UART0LCRH = (1 << 4) | (1 << 5) | (1 << 6);

	/* Mask all interrupts. */
	*UART0IMSC = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
				 (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10);

	/* Enable UART0 TX, RX. */
	*UART0CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_putc(unsigned char byte) {
	while(*UART0FR & (1 << 5));
	*UART0DR = byte;
}

void print_uart0(const char *s) {
	while(*s != '\0') { /* Loop until end of string */
		uart_putc(*s); /* Transmit char */
		s++; /* Next char */
	}
}

void main() {
	uart_init();
	print_uart0("Hello world!\n");
}
