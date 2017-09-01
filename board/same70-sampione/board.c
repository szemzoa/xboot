#include "xboot.h"
#include "board.h"
#include "at91_eefc.h"
#include "at91_matrix.h"
#include "at91_pmc.h"
#include "gpio.h"
#include "at91_pio.h"
#include "at91_usart.h"
#include "at91_sdramc.h"
#include "at91_wdt.h"
#include "mpu.h"

/* Convert nanoseconds to clock cycles for given master clock in Hz */
#define NS2CY(ns, clk) ((((ns) * (clk / 1000 / 1000)) + 999) / 1000)

static void at91_init_system(void)
{
    uint32_t read_MOR;

	/* Set FWS according to SYS_BOARD_MCKR configuration */
	eefc_set_flash_wait_states(EEFC, CONFIG_FLASH_WAIT_STATES);

	/* Before switching MAIN OSC on external crystal : enable it and don't
	 * disable at the same time RC OSC in case of if MAIN OSC is still using RC
	 * OSC
	 */
	read_MOR = readl(REG_CKGR_MOR);
	/* enable external crystal - enable RC OSC */
	read_MOR |= (CKGR_MOR_KEY_PASSWD | CKGR_MOR_XT32KFME);
	writel(read_MOR, REG_CKGR_MOR);

	/* Initialize main oscillator */
	if (!(readl(REG_CKGR_MOR) & CKGR_MOR_MOSCSEL)) {

		writel(CKGR_MOR_KEY_PASSWD | CONFIG_CPU_OSCOUNT | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN, REG_CKGR_MOR);

		while (!(readl(REG_PMC_SR) & PMC_SR_MOSCXTS)) {
		}
	}

	/* Switch to 3-20MHz Xtal oscillator */
	writel(CKGR_MOR_KEY_PASSWD | CONFIG_CPU_OSCOUNT | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL, REG_CKGR_MOR);

	while (!(readl(REG_PMC_SR) & PMC_SR_MOSCSELS))
	    ;

	writel((readl(REG_PMC_MCKR) & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK, REG_PMC_MCKR);

	while (!(readl(REG_PMC_SR) & PMC_SR_MCKRDY))
	    ;

	/* Initialize PLLA */
	writel(CONFIG_CPU_PLLAR, REG_CKGR_PLLAR);

	while (!(readl(REG_PMC_SR) & PMC_SR_LOCKA))
	    ;

	/* Switch to main clock: DO NOT modify MDIV and CSS feild at the same access */
	writel((readl(REG_PMC_MCKR) & ~(uint32_t)PMC_MCKR_MDIV_Msk) | CONFIG_CPU_MCKR_MDIV, REG_PMC_MCKR);
	writel((CONFIG_CPU_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK, REG_PMC_MCKR);

	while (!(readl(REG_PMC_SR) & PMC_SR_MCKRDY))
	    ;

	/* Switch to PLLA */
	writel(CONFIG_CPU_MCKR, REG_PMC_MCKR);

	while (!(readl(REG_PMC_SR) & PMC_SR_MCKRDY))
	    ;
} 

static void at91_init_usart(void)
{
	/* disable the MATRIX registers write protection */
	writel(MATRIX_WPMR_WPKEY_PASSWD, REG_MATRIX_WPMR);
	uint32_t reg = readl(REG_CCFG_SYSIO);
	reg |= CCFG_SYSIO_SYSIO4;
	writel(reg, REG_CCFG_SYSIO);

        /* Configure USART1 pins */
        const struct pio_desc dbgu_pins[] = {
            {"RXD", AT91C_PIN_PA(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"TXD", AT91C_PIN_PB(4),  0, PIO_DEFAULT, PIO_PERIPH_D},
            {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
        };
                                                                                                                                                        
        pio_configure(dbgu_pins);
        
	/* Disable interrupts */
	write_usart(USART_IDR, -1);

	/* Reset the receiver and transmitter */
	write_usart(USART_CR, US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA | US_CR_RXDIS | US_CR_TXDIS);

	pmc_enable_periph_clk(CONFIG_USART_ID);

	/* Configure the baudrate */
	write_usart(USART_BRGR, (CONFIG_MCK_HZ / CONFIG_USART_BAUDRATE) / 16);

	/* Configure USART in Asynchronous mode */
	write_usart(USART_MR, US_MR_PAR_NO | US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT);

	/* Enable RX and Tx */
	write_usart(USART_CR, US_CR_RXEN | US_CR_TXEN);
} 



/* configure sdram */ 
static void at91_init_sdram(void)
{
    volatile uint32_t i;
    volatile uint16_t *pSdram = (uint16_t *)(SDRAM_CS_ADDR);

	/* configure SDRAM pins */
        const struct pio_desc sdram_pins[] = {
            {"BA0",  AT91C_PIN_PA(20), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"BA1",  AT91C_PIN_PA(0),  0, PIO_DEFAULT, PIO_PERIPH_C},
            {"SDCK", AT91C_PIN_PD(23), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"SDCKE",AT91C_PIN_PD(14), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"SDCS", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"RAS",  AT91C_PIN_PD(16), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"CAS",  AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"SDWE", AT91C_PIN_PD(29), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"NBS0", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"NBS1", AT91C_PIN_PD(15), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"A2",   AT91C_PIN_PC(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A3",   AT91C_PIN_PC(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A4",   AT91C_PIN_PC(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A5",   AT91C_PIN_PC(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A6",   AT91C_PIN_PC(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A7",   AT91C_PIN_PC(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A8",   AT91C_PIN_PC(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A9",   AT91C_PIN_PC(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A10",  AT91C_PIN_PC(28), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A11",  AT91C_PIN_PC(29), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"SDA10",   AT91C_PIN_PD(13), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"A13",   AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"A14",   AT91C_PIN_PA(18), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"D0",   AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D1",   AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D2",   AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D3",   AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D4",   AT91C_PIN_PC(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D5",   AT91C_PIN_PC(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D6",   AT91C_PIN_PC(6), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D7",   AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D8",   AT91C_PIN_PE(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D9",   AT91C_PIN_PE(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D10",  AT91C_PIN_PE(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D11",  AT91C_PIN_PE(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D12",  AT91C_PIN_PE(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D13",  AT91C_PIN_PE(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D14",  AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"D15",  AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
        };

	/* configure SDRAM pins */
        pio_configure(sdram_pins);

	/* enable SDRAM access */
	writel(CCFG_SMCNFCS_SDRAMEN, REG_CCFG_SMCNFCS);

	/* enable SMC peripheral clock */
	pmc_enable_periph_clk(ID_SDRAMC);

	/* SDRAM device configuration */
	/* Set the features of SDRAM device into the Configuration Register */
	writel(	SDRAMC_CR_NC_COL10     | /* 10 column bits. */
		SDRAMC_CR_NR_ROW13     | /* 13 row bits (8K). */
		SDRAMC_CR_NB_BANK4     | /* SDRAM 4 bank. */
		SDRAMC_CR_CAS_LATENCY3 | /* CAS Latency 3. */
		SDRAMC_CR_DBW          				| /* Data bus width 16 bits. */
		SDRAMC_CR_TWR(NS2CY(30, CONFIG_MCK_HZ))       	| /* Write Recovery Delay. */
		SDRAMC_CR_TRC_TRFC(NS2CY(60, CONFIG_MCK_HZ)) 	| /* Row Cycle Delay and Row Refresh Cycle. */
		SDRAMC_CR_TRP(NS2CY(18, CONFIG_MCK_HZ))       	| /* Row Precharge Delay. */
		SDRAMC_CR_TRCD(NS2CY(18, CONFIG_MCK_HZ))      	| /* Row to Column Delay. */
		SDRAMC_CR_TRAS(NS2CY(42, CONFIG_MCK_HZ))      	| /* Active to Precharge Delay. */
		SDRAMC_CR_TXSR(NS2CY(66, CONFIG_MCK_HZ)),       /* Exit from Self Refresh to Active Delay. */
		REG_SDRAMC_CR);

	/* enable unaligned support */
	writel(SDRAMC_CFR1_UNAL | SDRAMC_CFR1_TMRD(2), REG_SDRAMC_CFR1);

	/* Program the memory device type into the Memory Device Register */
	writel(SDRAMC_MDR_MD_SDRAM, REG_SDRAMC_MDR);

	/* A minimum pause of 200 µs is provided to precede any signal toggle.
	   (6 core cycles per iteration) */
	delay_us(200);

	/* A NOP command is issued to the SDR-SDRAM. Program NOP command into
	   Mode Register, and the application must set Mode to 1 in the Mode
	   Register. Perform a write access to any SDR-SDRAM address to
	   acknowledge this command. Now the clock which drives SDR-SDRAM
	   device is enabled. */
	writel(SDRAMC_MR_MODE_NOP, REG_SDRAMC_MR);
	*pSdram = 0x0;

	delay_us(200);

	/* An all banks precharge command is issued to the SDR-SDRAM. Program
	   all banks precharge command into Mode Register, and the application
	   must set Mode to 2 in the Mode Register. Perform a write access to
	   any SDRSDRAM address to acknowledge this command. */
	writel(SDRAMC_MR_MODE_ALLBANKS_PRECHARGE, REG_SDRAMC_MR);
	*pSdram = 0x0;

	/* Add some delays after precharge */
	delay_us(200);

	/* Eight auto-refresh (CBR) cycles are provided. Program the auto
	   refresh command (CBR) into Mode Register, and the application
	   must set Mode to 4 in the Mode Register. Once in the idle state,
	   eight AUTO REFRESH cycles must be performed. */
	for(i=0; i < 8; i++ ) {
	    writel(SDRAMC_MR_MODE_AUTO_REFRESH, REG_SDRAMC_MR);
	    *pSdram = i;
	}

	delay_us(200);

	/* A Mode Register Set (MRS) cycle is issued to program the parameters
	   of the SDRAM devices, in particular CAS latency and burst length. */
	writel(SDRAMC_MR_MODE_LOAD_MODEREG, REG_SDRAMC_MR);
	*(pSdram + 0x30) = 0xcafe;

	delay_us(200);

	/* The application must go into Normal Mode, setting Mode to 0 in the
	   Mode Register and perform a write access at any location in the\
	   SDRAM to acknowledge this command. */
	writel(SDRAMC_MR_MODE_NORMAL, REG_SDRAMC_MR);
	*pSdram = 0x0;

	delay_us(200);

	/*    Write the refresh rate into the count field in the SDRAMC Refresh
	*     Timer register. (Refresh rate = delay between refresh cycles). The
	*     SDRAM device requires a refresh every 15.625 usec or 7.81 usec.
	*
	*  For IS42S16320B, 8192 refresh cycle every 64 ms, every 7.81 usec
	*/
	i = (64 * (CONFIG_MCK_HZ / 1000)) / 8192;
	writel(SDRAMC_TR_COUNT(i), REG_SDRAMC_TR);
} 

static void at91_init_qspi(void)
{
        /* Configure QSPI pins */
        const struct pio_desc qspi_pins[] = {
            {"QSCK", AT91C_PIN_PA(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"QCS",  AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"QIO0", AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"QIO1", AT91C_PIN_PA(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"QIO2", AT91C_PIN_PA(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {"QIO3", AT91C_PIN_PD(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
            {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
        };

	/* configure QSPI pins */
        pio_configure(qspi_pins);

	/* enable QSPI peripheral clock */
	pmc_enable_periph_clk(ID_QSPI);

}

static void at91_init_hsmci(void)
{
        /* Configure HSMCI pins */
        const struct pio_desc hsmci_pins[] = {
            {"MCCDA", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"MCCK",  AT91C_PIN_PA(25), 0, PIO_DEFAULT, PIO_PERIPH_D},
            {"MCDA0", AT91C_PIN_PA(30), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"MCDA1", AT91C_PIN_PA(31), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"MCDA2", AT91C_PIN_PA(26), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {"MCDA3", AT91C_PIN_PA(27), 0, PIO_DEFAULT, PIO_PERIPH_C},
            {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
        };

	/* configure HSMCI pins */
        pio_configure(hsmci_pins);

	/* enable HSMCI peripheral clock */
	pmc_enable_periph_clk(ID_HSMCI);
}

static void at91_init_mpu(void)
{
    uint32_t dw_region_base_addr;
    uint32_t dw_region_attr;

	ARM_DSB();
/**
 *	QSPI memory region --- Strongly ordered
 *	START_Addr:-  0x80000000UL
 *	END_Addr:-    0x8FFFFFFFUL
 */
	dw_region_base_addr = 
		QSPI_START_ADDRESS | 
		MPU_REGION_VALID | 
		MPU_QSPI_REGION;

	dw_region_attr = MPU_AP_FULL_ACCESS | 
			 STRONGLY_ORDERED |
			 mpu_cal_mpu_region_size(QSPI_END_ADDRESS - QSPI_START_ADDRESS) |
			 MPU_REGION_ENABLE;

	mpu_set_region( dw_region_base_addr, dw_region_attr);

	/* Enable the MPU with default regions */
	mpu_enable( MPU_ENABLE | MPU_PRIVDEFENA);

	ARM_DSB();
	ARM_ISB();
}

unsigned int board_bootsel_pin_state()
{
	/* Configure RECOVERY pins */
	const struct pio_desc bootsel_pins[] = {
	    {"BOOT", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_INPUT},
	    {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pmc_enable_periph_clk(ID_PIOA);

	/* configure boot select pins */
        pio_configure(bootsel_pins);

	return pio_get_value(AT91C_PIN_PA(2));
}

void board_init()
{
	#ifdef CONFIG_WATCHDOG_DISABLE
	    /* disable WDT */
	    at91_disable_wdt(AT91C_BASE_WDT);
	#endif

    	/* initialize internal flash, clocks */
	at91_init_system();

	/* initalize debug usart */
	at91_init_usart();
	
	/* initialize SDRAM */
	at91_init_sdram();

	/* initialize MPU */
	at91_init_mpu();

	/* initialize QSPI */
	at91_init_qspi();

	/* initialize HSMCI */
	at91_init_hsmci();
}

