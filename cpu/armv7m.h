#ifndef __ARMV7M_H__
#define __ARMV7M_H__

#include "common.h"
#include "debug.h"

#define SCS_BASE        0xE000E000UL          		/* System Control Space Base Address  */
#define SCB_BASE        (SCS_BASE +  0x0D00UL)  	/* System Control Block Base Address  */
#define VTOR            0x08				/* Vector Table Offset Register */
#define ICIALLU		0x250 				/* I-Cache Invalidate All to PoU */
#define CCR		0x14 				/* Configuration Control Register */
#define SHCSR           0x24 				/* System Handler Control and State Register */
#define CFSR		0x28				/* Configurable Fault Status Register */
#define HFSR		0x2C				/* HardFault Status Register */
#define DFSR		0x30				/* Debug Fault Status Register */
#define MMFAR		0x34				/* MemManage Fault Address Register */
#define BFAR		0x38				/* BusFault Address Register */
#define AFSR		0x3C				/* Auxiliary Fault Status Register */
#define CCSIDR          0x80 				/* Cache Size ID Register */
#define DCISW           0x260 				/* D-Cache Invalidate by Set-way */
#define DCCISW		0x274 				/* D-Cache Clean and Invalidate by Set-way */
#define ITCMCR		0x290 				/* Instruction Tightly-Coupled Memory Control Register */
#define DTCMCR		0x294 				/* Data Tightly-Coupled Memory Control Registers */

/* Instruction Tightly-Coupled Memory Control Register*/
#define SCB_ITCMCR_SZ_Pos                   3                                             /*!< SCB ITCMCR: SZ Position */
#define SCB_ITCMCR_SZ_Msk                  (0xFUL << SCB_ITCMCR_SZ_Pos)                   /*!< SCB ITCMCR: SZ Mask */

#define SCB_ITCMCR_RETEN_Pos                2                                             /*!< SCB ITCMCR: RETEN Position */
#define SCB_ITCMCR_RETEN_Msk               (0x1UL << SCB_ITCMCR_RETEN_Pos)                /*!< SCB ITCMCR: RETEN Mask */

#define SCB_ITCMCR_RMW_Pos                  1                                             /*!< SCB ITCMCR: RMW Position */
#define SCB_ITCMCR_RMW_Msk                 (0x1UL << SCB_ITCMCR_RMW_Pos)                  /*!< SCB ITCMCR: RMW Mask */

#define SCB_ITCMCR_EN_Pos                   0                                             /*!< SCB ITCMCR: EN Position */
#define SCB_ITCMCR_EN_Msk                  (0x1UL << SCB_ITCMCR_EN_Pos)                   /*!< SCB ITCMCR: EN Mask */

/* Data Tightly-Coupled Memory Control Registers */
#define SCB_DTCMCR_SZ_Pos                   3                                             /*!< SCB DTCMCR: SZ Position */
#define SCB_DTCMCR_SZ_Msk                  (0xFUL << SCB_DTCMCR_SZ_Pos)                   /*!< SCB DTCMCR: SZ Mask */

#define SCB_DTCMCR_RETEN_Pos                2                                             /*!< SCB DTCMCR: RETEN Position */
#define SCB_DTCMCR_RETEN_Msk               (1UL << SCB_DTCMCR_RETEN_Pos)                   /*!< SCB DTCMCR: RETEN Mask */

#define SCB_DTCMCR_RMW_Pos                  1                                             /*!< SCB DTCMCR: RMW Position */
#define SCB_DTCMCR_RMW_Msk                 (1UL << SCB_DTCMCR_RMW_Pos)                    /*!< SCB DTCMCR: RMW Mask */

#define SCB_DTCMCR_EN_Pos                   0                                             /*!< SCB DTCMCR: EN Position */
#define SCB_DTCMCR_EN_Msk                  (1UL << SCB_DTCMCR_EN_Pos)                     /*!< SCB DTCMCR: EN Mask */


#define SCB_CCR_IC_Pos		17				/* Instruction cache enable bit Position */
#define SCB_CCR_IC_Msk		(1UL << SCB_CCR_IC_Pos)		/* Instruction cache enable bit Mask */

#define SCB_CCSIDR_NUMSETS_Pos             13                                             /*!< SCB CCSIDR: NumSets Position */
#define SCB_CCSIDR_NUMSETS_Msk             (0x7FFFUL << SCB_CCSIDR_NUMSETS_Pos)           /*!< SCB CCSIDR: NumSets Mask */

#define SCB_CCSIDR_ASSOCIATIVITY_Pos        3                                             /*!< SCB CCSIDR: Associativity Position */
#define SCB_CCSIDR_ASSOCIATIVITY_Msk       (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Pos)      /*!< SCB CCSIDR: Associativity Mask */

#define SCB_CCSIDR_LINESIZE_Pos             0                                             /*!< SCB CCSIDR: LineSize Position */
#define SCB_CCSIDR_LINESIZE_Msk            (7UL << SCB_CCSIDR_LINESIZE_Pos)               /*!< SCB CCSIDR: LineSize Mask */

#define SCB_CCR_DC_Pos                      16                                            /*!< SCB CCR: Cache enable bit Position */
#define SCB_CCR_DC_Msk                     (1UL << SCB_CCR_DC_Pos)                        /*!< SCB CCR: Cache enable bit Mask */

#define SCB_CFSR_USGFAULTSR_Pos            16U                                            /*!< SCB CFSR: Usage Fault Status Register Position */
#define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)          /*!< SCB CFSR: Usage Fault Status Register Mask */

#define SCB_CFSR_BUSFAULTSR_Pos             8U                                            /*!< SCB CFSR: Bus Fault Status Register Position */
#define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)            /*!< SCB CFSR: Bus Fault Status Register Mask */

#define SCB_CFSR_MEMFAULTSR_Pos             0U                                            /*!< SCB CFSR: Memory Manage Fault Status Register Position */
#define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL /*<< SCB_CFSR_MEMFAULTSR_Pos*/)        /*!< SCB CFSR: Memory Manage Fault Status Register Mask */

/* SCB Hard Fault Status Registers Definitions */
#define SCB_HFSR_DEBUGEVT_Pos              31U                                            /*!< SCB HFSR: DEBUGEVT Position */
#define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)                 /*!< SCB HFSR: DEBUGEVT Mask */

#define SCB_HFSR_FORCED_Pos                30U                                            /*!< SCB HFSR: FORCED Position */
#define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)                   /*!< SCB HFSR: FORCED Mask */

#define SCB_HFSR_VECTTBL_Pos                1U                                            /*!< SCB HFSR: VECTTBL Position */
#define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)                  /*!< SCB HFSR: VECTTBL Mask */

/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> SCB_CCSIDR_ASSOCIATIVITY_Pos)
#define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> SCB_CCSIDR_NUMSETS_Pos      )
#define CCSIDR_LSSHIFT(x)      (((x) & SCB_CCSIDR_LINESIZE_Msk     ) >> SCB_CCSIDR_LINESIZE_Pos     )

#define SCB_VTOR_TBLOFF_Pos     7                       		/* SCB VTOR: TBLOFF Position */
#define SCB_VTOR_TBLOFF_Msk     (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)	/* SCB VTOR: TBLOFF Mask */

/**
 * \brief Delay loop to delay n number of cycles
 *
 * \note The function runs in internal RAM so that flash wait states
 *       will not affect the delay time.
 *
 * \param n Number of cycles
 */

void portable_delay_cycles(unsigned long n);

#define cpu_ms_2_cy(ms, f_cpu)  \
	(((uint64_t)(ms) * (f_cpu) + (uint64_t)(5.932e3 - 1ul)) / (uint64_t)5.932e3)
#define cpu_us_2_cy(us, f_cpu)  \
	(((uint64_t)(us) * (f_cpu) + (uint64_t)(5.932e6 - 1ul)) / (uint64_t)5.932e6)

#define delay_cycles               portable_delay_cycles

#define cpu_delay_ms(delay, f_cpu) delay_cycles(cpu_ms_2_cy(delay, f_cpu))
#define cpu_delay_us(delay, f_cpu) delay_cycles(cpu_us_2_cy(delay, f_cpu))

/**
 * @def delay_s
 * @brief Delay in seconds.
 * @param delay Delay in seconds
 */
#define delay_s(delay)      cpu_delay_ms(1000 * delay, CONFIG_CPU_HZ)

/**
 * @def delay_ms
 * @brief Delay in milliseconds.
 * @param delay Delay in milliseconds
 */
#define delay_ms(delay)     cpu_delay_ms(delay, CONFIG_CPU_HZ)

/**
 * @def delay_us
 * @brief Delay in microseconds.
 * @param delay Delay in microseconds
 */
#define delay_us(delay)     cpu_delay_us(delay, CONFIG_CPU_HZ)


inline void ARM_DMB(void)
{
	asm volatile ("dmb" ::: "memory");
}

inline void ARM_DSB(void)
{
	asm volatile ("dsb" ::: "memory");
}

inline void ARM_ISB(void)
{
	asm volatile ("isb" ::: "memory");
}

typedef void (*nvic_handler_t)(void);


void armv7m_caches_invalidate(void);
void armv7m_caches_disable(void);
void cpu_halt(void);

#endif