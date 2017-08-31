#include "xboot.h"
#include "mpu.h"

/**
 * \addtogroup mmu MMU Initialization
 *
 * \section Usage
 *
 * Translation Look-aside Buffers (TLBs) are an implementation technique that
 * caches translations or translation table entries. TLBs avoid the requirement
 * for every memory access to perform a translation table lookup.
 * The ARM architecture does not specify the exact form of the TLB structures
 * for any design. In a similar way to the requirements for caches, the
 * architecture only defines certain principles for TLBs:
 *
 * The MMU supports memory accesses based on memory sections or pages:
 * Super-sections Consist of 16MB blocks of memory. Support for Super sections
 * is optional.
 * -# Sections Consist of 1MB blocks of memory.
 * -# Large pages Consist of 64KB blocks of memory.
 * -# Small pages Consist of 4KB blocks of memory.
 *
 * Access to a memory region is controlled by the access permission bits and
 * the domain field in the TLB entry.
 * Memory region attributes
 * Each TLB entry has an associated set of memory region attributes. These
 * control accesses to the caches,
 * how the write buffer is used, and if the memory region is Shareable and
 * therefore must be kept coherent.
 *
 */

/**
 * \brief Enables the MPU module.
 *
 * \param dwMPUEnable  Enable/Disable the memory region.
 */
void mpu_enable(uint32_t dw_mpu_enable)
{
	writel(dw_mpu_enable, MPU_BASE + CTRL);
}

/**
 * \brief Set active memory region.
 *
 * \param dwRegionNum  The memory region to be active.
 */
void mpu_set_region_num(uint32_t dw_region_num)
{
	writel(dw_region_num, MPU_BASE + RNR);
}

/**
 * \brief Disable the current active region.
 */
void mpu_disable_region(void)
{
    uint32_t tmp;

	tmp = readl(MPU_BASE + RASR);
	tmp &= 0xfffffffe;
	writel(tmp, MPU_BASE + RASR);
}

/**
 * \brief Setup a memory region.
 *
 * \param dwRegionBaseAddr  Memory region base address.
 * \param dwRegionAttr  Memory region attributes.
 */
void mpu_set_region(uint32_t dw_region_base_addr, uint32_t dw_region_attr)
{
	writel(dw_region_base_addr, MPU_BASE + RBAR);
	writel(dw_region_attr, MPU_BASE + RASR);
}


/**
 * \brief Calculate region size for the RASR.
 */
uint32_t mpu_cal_mpu_region_size(uint32_t dw_actual_size_in_bytes)
{
	uint32_t dwRegionSize = 32;
	uint32_t dwReturnValue = 4;

	while( dwReturnValue < 31 ) {
		if( dw_actual_size_in_bytes <= dwRegionSize ) {
			break;
		} else {
			dwReturnValue++;
		}
		dwRegionSize <<= 1;
	}

	return ( dwReturnValue << 1 );
}


/**
 *  \brief Update MPU regions.
 *
 *  \return Unused (ANSI-C compatibility).
 */
void mpu_update_regions(uint32_t dw_region_num, uint32_t dw_region_base_addr, uint32_t dw_region_attr)
{

	/* Clean up data and instruction buffer */
	ARM_DSB();
	ARM_ISB();

	/* Set active region */
	mpu_set_region_num(dw_region_num);

	/* Disable region */
	mpu_disable_region();

	/* Update region attribute */
	mpu_set_region( dw_region_base_addr, dw_region_attr);

	/* Clean up data and instruction buffer to make the new region taking
	   effect at once */
	ARM_DSB();
	ARM_ISB();

}
