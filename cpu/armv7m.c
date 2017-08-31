#include "xboot.h"
#include "armv7m.h"

/* from LIBC */
extern void __libc_init_array(void);

void exception_handler(void);
void NMI_handler(void);
void hardfault_handler(void);
void busfault_handler(void);
void usagefault_handler(void);
void reset_handler(void);
extern int main();

/* Addresses pulled in from the linker script */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

/* Stack top and vector handler table */
__attribute__ ((section(".vectors"))) 
const struct {
	void*          stack;
	nvic_handler_t handlers[15];
} __vector_table = {
	.stack = (void *)(&_estack),
	.handlers = {
		reset_handler,
		NMI_handler,
		hardfault_handler,
		exception_handler,
		busfault_handler,
		usagefault_handler,
		0, /* reserved */
		0, /* reserved */
		0, /* reserved */
		0, /* reserved */
		exception_handler,
		exception_handler,
		0, /* reserved */
		exception_handler,
		exception_handler, /* systick */
	}
};

/*  This is the code that gets called on processor reset, to initialize the device, and call the main() routine */
void reset_handler(void)
{
	asm volatile ("cpsid i");

	uint32_t *src, *dst;

	/* zero BSS */
	for (dst = (uint32_t*)&_szero; dst < (uint32_t*)&_ezero; dst++)
		*dst = 0;

	/* copy data */
	for (dst = (uint32_t*)&_srelocate, src = (uint32_t*)&_etext; dst < (uint32_t*)&_erelocate; dst++, src++)
		*dst = *src;

	/* initialize the C library */
	__libc_init_array();

	/* Branch to main function */
	main();
}

/* Delay loop is put to SRAM so that FWS will not affect delay time */
__attribute__ ((section(".ramfunc"))) __attribute__((optimize(s)))
void portable_delay_cycles(unsigned long n)
{
	__asm (
		"loop: DMB	\n"
		"SUBS R0, R0, #1  \n"
		"BNE.N loop         "
	);
}

static inline uint8_t __CLZ(uint32_t value)
{
    uint32_t result;

	__asm volatile ("clz %0, %1" : "=r" (result) : "r" (value) );

	return ((uint8_t) result);    /* Add explicit type cast here */
}


void armv7m_icache_disable()
{
    uint32_t ccr;
    
	ARM_DSB();
	ARM_ISB();

	writel(0, SCB_BASE + ICIALLU);				/* invalidate I-Cache */

	ccr = readl(SCB_BASE + CCR);
	ccr &= ~SCB_CCR_IC_Msk;
	writel(ccr, SCB_BASE + CCR);			/* disable I-Cache */

	ARM_DSB();
	ARM_ISB();
}

#if 0
void armv7m_icache_enable()
{
    uint32_t ccr;
    
	ARM_DSB();
	ARM_ISB();

	writel(0, SCB_BASE + ICIALLU);				/* invalidate I-Cache */

	ccr = readl(SCB_BASE + CCR);
	writel(ccr | SCB_CCR_IC_Msk, SCB_BASE + CCR);		/* enable I-Cache */

	ARM_DSB();
	ARM_ISB();
}

void armv7m_dcache_enable()
{
    uint32_t ccsidr, sshift, wshift, sw;
    uint32_t sets, ways;
    uint32_t tmp;

	ccsidr  = readl(SCB_BASE + CCSIDR);

	sets    = CCSIDR_SETS(ccsidr);
	sshift  = CCSIDR_LSSHIFT(ccsidr) + 4;
	ways    = CCSIDR_WAYS(ccsidr);
	wshift  = __CLZ(ways) & 0x1f;

	ARM_DSB();

	do {                                    // invalidate D-Cache
    	    int32_t tmpways = ways;
         
            do {
        	sw = ((tmpways << wshift) | (sets << sshift));
		writel(sw, SCB_BASE + DCISW);

            } while(tmpways--);
    
        } while(sets--);

	ARM_DSB();

	tmp = readl(SCB_BASE + CCR);
	writel(tmp | SCB_CCR_DC_Msk, SCB_BASE + CCR);		/* enable D-Cache */

	ARM_DSB();
	ARM_ISB();
}

void armv7m_dcache_flush()
{
    uint32_t ccsidr, sshift, wshift, sw;
    uint32_t sets, ways;

	ccsidr  = readl(SCB_BASE + CCSIDR);

	sets    = CCSIDR_SETS(ccsidr);
	sshift  = CCSIDR_LSSHIFT(ccsidr) + 4;
	ways    = CCSIDR_WAYS(ccsidr);
	wshift  = __CLZ(ways) & 0x1f;

	ARM_DSB();

	do {                                    // invalidate D-Cache
    	    int32_t tmpways = ways;
         
            do {
        	sw = ((tmpways << wshift) | (sets << sshift));
		writel(sw, SCB_BASE + DCCISW);

            } while(tmpways--);
    
        } while(sets--);

	ARM_DSB();
	ARM_ISB();
}
#endif

void armv7m_dcache_disable()
{
    uint32_t ccsidr, sshift, wshift, sw;
    uint32_t sets, ways;
    uint32_t tmp;

	ccsidr  = readl(SCB_BASE + CCSIDR);

	sets    = CCSIDR_SETS(ccsidr);
	sshift  = CCSIDR_LSSHIFT(ccsidr) + 4;
	ways    = CCSIDR_WAYS(ccsidr);
	wshift  = __CLZ(ways) & 0x1f;

	ARM_DSB();

	tmp = readl(SCB_BASE + CCR);		/* disable D-Cache */
	tmp &= ~SCB_CCR_DC_Msk;
	writel(tmp, SCB_BASE + CCR);		

	do {                                    // invalidate D-Cache
    	    int32_t tmpways = ways;
         
            do {
        	sw = ((tmpways << wshift) | (sets << sshift));
		writel(sw, SCB_BASE + DCISW);

            } while(tmpways--);
    
        } while(sets--);

	ARM_DSB();
	ARM_ISB();
}

void armv7m_dcache_invalidate()
{
    uint32_t ccsidr, sshift, wshift, sw;
    uint32_t sets, ways;

	ccsidr  = readl(SCB_BASE + CCSIDR);

	sets    = CCSIDR_SETS(ccsidr);
	sshift  = CCSIDR_LSSHIFT(ccsidr) + 4;
	ways    = CCSIDR_WAYS(ccsidr);
	wshift  = __CLZ(ways) & 0x1f;

	ARM_DSB();

	do {                                    // invalidate D-Cache
    	    int32_t tmpways = ways;
         
            do {
        	sw = ((tmpways << wshift) | (sets << sshift));
		writel(sw, SCB_BASE + DCISW);

            } while(tmpways--);
    
        } while(sets--);

	ARM_DSB();
	ARM_ISB();
}

void armv7m_icache_invalidate()
{
	ARM_DSB();
	ARM_ISB();

	writel(0, SCB_BASE + ICIALLU);				/* invalidate I-Cache */

	ARM_DSB();
	ARM_ISB();
}

void armv7m_caches_invalidate()
{
	armv7m_dcache_invalidate();
	armv7m_icache_invalidate();
}

void armv7m_caches_disable()
{
	armv7m_icache_disable();
	armv7m_dcache_disable();
}

/* Default interrupt handler for unused IRQs */
void exception_handler(void)
{
	kprintf("---exception handler---\r\n");

	while(1);
}

void cpu_halt()
{
	kprintf("cpu halted...\r\n");

	while(1);
}

void NMI_handler(void)
{
	kprintf("\r\n---NMI exception---\r\n");

	while(1);
}

static inline uint32_t StackUnwind(void)
{
    uint32_t faddr;

	asm("mrs r0, msp ");
	asm("ldr %0, [r0,#28]" : "=r" (faddr));

	return faddr;
}

static void HardFault_reason(void)
{
    uint32_t CFSRValue;

	kprintf("In Hard Fault Handler\n\r");
	kprintf("SCB->HFSR = 0x%08x\n\r", readl(SCB_BASE + HFSR));

	if ((readl(SCB_BASE + HFSR) & SCB_HFSR_DEBUGEVT_Msk)) {
		kprintf("Debug Event Hard Fault\n\r");
		kprintf("SCB->DFSR = 0x%08x\n", readl(SCB_BASE + DFSR));
	}

	if ((readl(SCB_BASE + HFSR) & SCB_HFSR_VECTTBL_Msk)) {
		kprintf("Fault was due to vector table read on \
			exception processing\n\r");
	}

	// Forced HardFault
	if ((readl(SCB_BASE + HFSR) & SCB_HFSR_FORCED_Msk)) {
		kprintf("Forced Hard Fault\n\r");
		kprintf("SCB->CFSR = 0x%08x\n\r", readl(SCB_BASE + CFSR));

		// Usage Fault
		if ((readl(SCB_BASE + CFSR) & SCB_CFSR_USGFAULTSR_Msk)) {
			CFSRValue = readl(SCB_BASE + CFSR);
			kprintf("Usage fault: ");
			CFSRValue >>= SCB_CFSR_USGFAULTSR_Pos;

			if ((CFSRValue & (1 << 9)))
				kprintf("Divide by zero\n\r");

			if ((CFSRValue & (1 << 8)))
				kprintf("Unaligned access error\n\r");

			if ((CFSRValue & (1 << 3)))
				kprintf("Coprocessor access error\n\r");

			if ((CFSRValue & (1 << 2)))
				kprintf("Integrity check error on EXC_RETURN\n\r");
		}

		// Bus Fault
		if ((readl(SCB_BASE + CFSR) & SCB_CFSR_BUSFAULTSR_Msk)) {
			CFSRValue = readl(SCB_BASE + CFSR);
			kprintf("Bus fault: ");
			CFSRValue >>= SCB_CFSR_BUSFAULTSR_Pos;

			if ((CFSRValue & (1 << 7)) && (CFSRValue & (1 << 1))) {
				kprintf("Precise data access error. Bus Fault Address \
					Register is: %x \n\r", readl(SCB_BASE + BFAR));
			}

			if ((CFSRValue & (1 << 4)))
				kprintf("Bus fault has occurred on exception entry\n\r");

			if ((CFSRValue & (1 << 3)))
				kprintf("bus fault has occurred on exception return\n\r");

			if ((CFSRValue & (1 << 2)))
				kprintf("Imprecise data access error\n\r");

			if ((CFSRValue & (1 << 0))) {
				kprintf("This bit indicates a bus fault on an instruction \
					pre-fetch. \n\r");
			}
		}
	}

	// MemoryFault
	if ((readl(SCB_BASE + CFSR) & SCB_CFSR_MEMFAULTSR_Msk)) {
		CFSRValue = readl(SCB_BASE + CFSR);
		kprintf("Memory fault: ");
		CFSRValue >>= SCB_CFSR_MEMFAULTSR_Pos;

		if ((CFSRValue & (1 << 9)) != 0)
			kprintf("Divide by zero\n\r");
	}

	ARM_ISB();
	ARM_DMB();

	asm volatile("BKPT #01");
}

void hardfault_handler(void)
{
	kprintf("\n\rHardFault at address 0X%x\n\r", (int)StackUnwind());

	ARM_ISB();
	ARM_DMB();

	HardFault_reason();
}

void busfault_handler(void)
{
	asm("nop");
	asm("nop");

	kprintf("\n\rBus Fault at address 0X%x\n\r", (int)StackUnwind());

	ARM_ISB();
	ARM_DMB();

	asm volatile("BKPT #01");
}

void usagefault_handler(void)
{
	kprintf("\r\nUsage fault at address 0X%x", (int)StackUnwind());

	ARM_ISB();
	ARM_DMB();

	asm volatile("BKPT #01");
}
