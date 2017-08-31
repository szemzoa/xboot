#ifndef __MPU_H__
#define __MPU_H__

#define DISABLE   0
#define ENABLE    1

#define MPU_BASE	(SCS_BASE +  0x0D90UL)	/* Memory Protection Unit */
#define TYPE		0x00	/* MPU Type Register                              */
#define CTRL		0x04	/* MPU Control Register                           */
#define RNR		0x08	/* MPU Region RNRber Register                     */
#define RBAR		0x0C	/* MPU Region Base Address Register               */
#define RASR		0x10	/* MPU Region Attribute and Size Register         */

#define MPU_QSPI_REGION		15

#define MPU_REGION_VALID        0x10
#define MPU_REGION_ENABLE       0x1
#define MPU_REGION_DISABLE      0x0
#define MPU_ENABLE			( 0x1 << MPU_CTRL_ENABLE_Pos)
#define MPU_HFNMIENA			( 0x1 << MPU_CTRL_HFNMIENA_Pos )
#define MPU_PRIVDEFENA			( 0x1 << MPU_CTRL_PRIVDEFENA_Pos )
#define MPU_RASR_AP_Pos			24                                             /*!< MPU RASR: ATTRS.AP Position */
#define MPU_AP_FULL_ACCESS		( 0x03 << MPU_RASR_AP_Pos )
#define MPU_CTRL_PRIVDEFENA_Pos		2                                             /*!< MPU CTRL: PRIVDEFENA Position */
#define MPU_CTRL_HFNMIENA_Pos		1                                             /*!< MPU CTRL: HFNMIENA Position */
#define MPU_CTRL_ENABLE_Pos		0                                             /*!< MPU CTRL: ENABLE Position */
#define MPU_RASR_TEX_Pos		19                                             /*!< MPU RASR: ATTRS.TEX Position */
#define MPU_RASR_S_Pos			18                                             /*!< MPU RASR: ATTRS.S Position */
#define MPU_RASR_C_Pos			17                                             /*!< MPU RASR: ATTRS.C Position */
#define MPU_RASR_B_Pos			16                                             /*!< MPU RASR: ATTRS.B Position */

#define CACHEABLE_REGION	(( 0x01 << MPU_RASR_TEX_Pos ) | ( 0x01  << MPU_RASR_C_Pos ) | ( 0x01  << MPU_RASR_B_Pos ) | ( 0x00 << MPU_RASR_S_Pos ))
#define STRONGLY_ORDERED	((0x00 << MPU_RASR_TEX_Pos) | (DISABLE << MPU_RASR_C_Pos) | (DISABLE << MPU_RASR_B_Pos))     // DO not care //

#define QSPI_START_ADDRESS                   0x80000000UL
#define QSPI_END_ADDRESS                     0x9FFFFFFFUL

void mpu_debug_regions(void);
uint32_t mpu_cal_mpu_region_size(uint32_t dw_actual_size_in_bytes);
void mpu_update_regions(uint32_t dw_region_num, uint32_t dw_region_base_addr, uint32_t dw_region_attr);
void mpu_set_region(uint32_t dw_region_base_addr, uint32_t dw_region_attr);
void mpu_enable(uint32_t dw_mpu_enable);

#endif 
