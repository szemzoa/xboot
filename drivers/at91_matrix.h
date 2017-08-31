#ifndef __AT91_MATRIX_H__
#define __AT91_MATRIX_H__

#define REG_CCFG_SYSIO                     (0x40088114U) /**< \brief (MATRIX) System I/O and CAN1 Configuration Register */
#define REG_CCFG_SMCNFCS                   (0x40088124U) /**< \brief (MATRIX) SMC NAND Flash Chip Select Configuration Register */
#define REG_MATRIX_WPMR                    (0x400881E4U) /**< \brief (MATRIX) Write Protection Mode Register */
#define REG_MATRIX_WPSR                    (0x400881E8U) /**< \brief (MATRIX) Write Protection Status Register */
#define CCFG_SYSIO_SYSIO4 		(0x1u << 4) 		/* PB4 or TDI Assignment */
#define CCFG_SMCNFCS_SDRAMEN 		(0x1u << 4) 		/* SDRAM Enable */
#define MATRIX_WPMR_WPKEY_PASSWD	(0x4D4154u << 8) 	/* Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
#define MATRIX_WPMR_WPEN (0x1u << 0) 

#endif