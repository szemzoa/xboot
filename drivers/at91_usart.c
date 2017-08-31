#include "at91_usart.h"

void usart_putc(void *arg, char c) 
{
	while (!(read_usart(USART_CSR) & US_CSR_TXRDY))
	    ;

	write_usart(USART_THR, c);
}
