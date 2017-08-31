#include "xboot.h"
#include "at91_usart.h"

void kprintf(const char *fmt, ...) 
{
	va_list args;
	va_start(args, fmt);
	xvformat(usart_putc, NULL, fmt, args);
	va_end(args);
}
