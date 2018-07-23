#ifndef __SAMX7_H__
#define __SAMX7_H__

#include <inttypes.h>
#include "armv7m.h"
#include "at91_qspi.h"

#define AT91C_BASE_PIOA		0x400E0E00 		/* PIOA Base Address */
#define AT91C_BASE_PIOB		0x400E1000 		/* PIOB Base Address */
#define AT91C_BASE_PIOC		0x400E1200 		/* PIOC Base Address */
#define AT91C_BASE_PIOD		0x400E1400 		/* PIOD Base Address */
#define AT91C_BASE_PIOE		0x400E1600 		/* PIOE Base Address */
#define AT91C_BASE_USART1	0x40028000 		/* USART1 Base Address */
#define AT91C_BASE_HSMCI   	0x40000000 		/* HSMCI Base Address */
#define AT91C_BASE_WDT     	0x400E1850 		/* WDT Register */
#define AT91C_BASE_RST     	0x400E1800 		/* RESET Base Address */
#define QSPI0   		((Qspi*)0x4007C000U) 
#define EEFC			((Eefc*)0x400E0C00U) 

#define ID_USART1	14 
#define ID_SDRAMC	62
#define ID_PIOA		10
#define ID_PIOB		11
#define ID_PIOC		12
#define ID_PIOD		16
#define ID_PIOE		17
#define ID_QSPI		43
#define ID_HSMCI  	18 

/* for at91_gpio.c */
#define CPU_HAS_PIO3
#define AT91C_NUM_PIO	5

#define IFLASH_ADDR	0x00400000 	/* Internal Flash base address */
#define SDRAM_CS_ADDR 	0x70000000 	/* SDRAM Chip Select base address */
#define QSPIMEM_ADDR	0x80000000	/* QSPI MEMORY MAPPED base address */

#define MPU_SDRAM_REGION	13
#define MPU_DMA_REGION		14
#define MPU_QSPI_REGION		15

#define SDRAM_START_ADDRESS                  0x70000000
#define SDRAM_END_ADDRESS                    0x73dfffff

#define DMA_START_ADDRESS                    0x73e00000
#define DMA_END_ADDRESS                      0x73FFFFFF

/******* QSPI macros ***************************/
#define QSPI_START_ADDRESS                   0x80000000UL
#define QSPI_END_ADDRESS                     0x9FFFFFFFUL

#endif
