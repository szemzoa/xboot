#include "xboot.h"
#include "at91_pmc.h"

void pmc_enable_periph_clk(uint32_t ul_id)
{
	if (ul_id < 32) {
		writel(1 << ul_id, PMC_PCER0);
	} else {
		ul_id -= 32;
		writel(1 << ul_id, PMC_PCER1);
	}
}

void pmc_disable_periph_clk(uint32_t ul_id)
{
	if (ul_id < 32) {
		writel(1 << ul_id, PMC_PCDR0);
	} else {
		ul_id -= 32;
		writel(1 << ul_id, PMC_PCDR1);
	}
}
