#ifndef __COMMON_H__
#define __COMMON_H__

/* I/O Function Macros */
#define writel(value, addr) (*(volatile unsigned int *)(addr)) = (value)
#define readl(addr) (*(volatile unsigned int *)(addr))

#define writew(value, addr) (*(volatile unsigned short *)(addr) = (value))
#define readw(addr) (*(volatile unsigned short *)(addr))

#define writeb(value, addr) (*(volatile unsigned char *)(addr) = (value))
#define readb(addr) (*(volatile unsigned char *)(addr))

#ifndef NULL
#define	NULL	0
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#define ALIGN(size, align)	(((size) + (align) - 1) & (~((align) - 1)))
#define OF_ALIGN(size)		ALIGN(size, 4)

/**
 *  Returns the minimum value between two integers.
 *  \param a First integer to compare
 *  \param b Second integer to compare
 */
static inline uint32_t min_u32(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

static inline unsigned int swap_uint32(unsigned int data)
{
	volatile unsigned int a, b, c, d;

	a = ((data) & 0xff000000) >> 24;
	b = ((data) & 0x00ff0000) >> 8;
	c = ((data) & 0x0000ff00) << 8;
	d = ((data) & 0x000000ff) << 24;

	return a | b | c | d;
}

#endif
