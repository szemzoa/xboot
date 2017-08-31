#ifndef __AT91_USART_H__
#define __AT91_USART_H__

#include "xboot.h"

#define USART_CR         0x00    /* Control Register */
#define USART_MR         0x04    /* Mode Register */
#define USART_IDR        0x0C    /* Interrupt Disable Register */
#define USART_CSR        0x14    /* Channel Status Register */
#define USART_RHR        0x18    /* Receiver Holding Register */
#define USART_THR        0x1C    /* Transmitter Holding Register */
#define USART_BRGR       0x20    /* Baud Rate Generator Register */

#define US_CR_RSTRX 	(0x1u << 2) /* Reset Receiver */
#define US_CR_RSTTX 	(0x1u << 3) /* Reset Transmitter */
#define US_CR_RXEN 	(0x1u << 4) /* Receiver Enable */
#define US_CR_RXDIS 	(0x1u << 5) /* Receiver Disable */
#define US_CR_TXEN 	(0x1u << 6) /* Transmitter Enable */
#define US_CR_TXDIS 	(0x1u << 7) /* Transmitter Disable */
#define US_CR_RSTSTA 	(0x1u << 8) /* Reset Status Bits */

#define US_MR_CHRL_8_BIT 		(0x3u << 6)  /* Character length is 8 bits */
#define US_MR_PAR_NO 			(0x4u << 9)  /* No parity */
#define US_MR_NBSTOP_1_BIT 		(0x0u << 12) /* 1 stop bit */
#define US_MR_CHMODE_NORMAL 		(0x0u << 14) /* Normal mode */

#define US_CSR_RXRDY 		(0x1u << 0) /* Receiver Ready (cleared by reading US_RHR) */
#define US_CSR_TXRDY 		(0x1u << 1) /* Transmitter Ready (cleared by writing US_THR) */
#define US_CSR_TXEMPTY 		(0x1u << 9) /* Transmitter Empty (cleared by writing US_THR) */

static inline void write_usart(unsigned int offset, const unsigned int value)
{
	writel(value, offset + CONFIG_USART_BASE);
}

static inline unsigned int read_usart(unsigned int offset)
{
	return readl(offset + CONFIG_USART_BASE);
}

void usart_putc(void *arg, char c) ;
char usart_getch(void);
int usart_is_received(void);

#endif /* __USART_H__ */
