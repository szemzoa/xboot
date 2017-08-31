#ifndef _AT91_PMC_H__
#define _AT91_PMC_H__

/* PMC peripherial */
#define PMC_PCER0      		0x400E0610U 	/* Peripheral Clock Enable Register 0 */
#define PMC_PCDR0      		0x400E0614U 	/* Peripheral Clock Disable Register 0 */
#define PMC_PCER1      		0x400E0700U	/* Peripheral Clock Enable Register 1 */
#define PMC_PCDR1      		0x400E0704U 	/* Peripheral Clock Disable Register 1 */
#define PMC_PCKx		0x400E0640U	/* Programmable Clock Register */
#define PMC_SCER		0x400E0600U	/* Programmable Clock out enable Register */

#define REG_CKGR_MOR                        (0x400E0620U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_PLLAR                      (0x400E0628U) /**< \brief (PMC) PLLA Register */
#define REG_CKGR_UCKR                       (0x400E061CU) /**< \brief (PMC) UTMI Clock Register */
#define REG_PMC_MCKR                        (0x400E0630U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_SR                          (0x400E0668U) /**< \brief (PMC) Status Register */
#define REG_PMC_SCER                        (0x400E0600U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                        (0x400E0604U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                        (0x400E0608U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_USB                         (0x400E0638U) /**< \brief (PMC) USB Clock Register */

/* -------- CKGR_MOR : (PMC Offset: 0x0020) Main Oscillator Register -------- */
#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
#define CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CKGR_MOR) Main Crystal Oscillator Bypass */
#define CKGR_MOR_WAITMODE (0x1u << 2) /**< \brief (CKGR_MOR) Wait Mode Command (Write-only) */
#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */
#define CKGR_MOR_MOSCRCF_Pos 4
#define CKGR_MOR_MOSCRCF_Msk (0x7u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Frequency Selection */
#define CKGR_MOR_MOSCRCF(value) ((CKGR_MOR_MOSCRCF_Msk & ((value) << CKGR_MOR_MOSCRCF_Pos)))
#define   CKGR_MOR_MOSCRCF_4_MHz (0x0u << 4) /**< \brief (CKGR_MOR) Fast RC oscillator frequency is at 4 MHz (default) */
#define   CKGR_MOR_MOSCRCF_8_MHz (0x1u << 4) /**< \brief (CKGR_MOR) Fast RC oscillator frequency is at 8 MHz */
#define   CKGR_MOR_MOSCRCF_12_MHz (0x2u << 4) /**< \brief (CKGR_MOR) Fast RC oscillator frequency is at 12 MHz */
#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
#define CKGR_MOR_KEY_Pos 16
#define CKGR_MOR_KEY_Msk (0xffu << CKGR_MOR_KEY_Pos) /**< \brief (CKGR_MOR) Write Access Password */
#define CKGR_MOR_KEY(value) ((CKGR_MOR_KEY_Msk & ((value) << CKGR_MOR_KEY_Pos)))
#define   CKGR_MOR_KEY_PASSWD (0x37u << 16) /**< \brief (CKGR_MOR) Writing any other value in this field aborts the write operation.Always reads as 0. */
#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */
#define CKGR_MOR_XT32KFME (0x1u << 26) /**< \brief (CKGR_MOR) Slow Crystal Oscillator Frequency Monitoring Enable */

/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
#define CKGR_MCFR_MAINF_Pos 0
#define CKGR_MCFR_MAINF_Msk (0xffffu << CKGR_MCFR_MAINF_Pos) /**< \brief (CKGR_MCFR) Main Clock Frequency */
#define CKGR_MCFR_MAINF(value) ((CKGR_MCFR_MAINF_Msk & ((value) << CKGR_MCFR_MAINF_Pos)))
#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Frequency Measure Ready */
#define CKGR_MCFR_RCMEAS (0x1u << 20) /**< \brief (CKGR_MCFR) RC Oscillator Frequency Measure (write-only) */
#define CKGR_MCFR_CCSS (0x1u << 24) /**< \brief (CKGR_MCFR) Counter Clock Source Selection */



/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
#define CKGR_PLLAR_DIVA_Pos 0
#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) PLLA Front End Divider */
#define CKGR_PLLAR_DIVA(value) ((CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos)))
#define   CKGR_PLLAR_DIVA_0 (0x0u << 0) /**< \brief (CKGR_PLLAR) Divider output is 0 and PLLA is disabled. */
#define   CKGR_PLLAR_DIVA_BYPASS (0x1u << 0) /**< \brief (CKGR_PLLAR) Divider is bypassed (divide by 1) and PLLA is enabled. */
#define CKGR_PLLAR_PLLACOUNT_Pos 8
#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
#define CKGR_PLLAR_MULA_Pos 16
#define CKGR_PLLAR_MULA_Msk (0x7ffu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
#define CKGR_PLLAR_ONE (0x1u << 29) /**< \brief (CKGR_PLLAR) Must Be Set to 1 */

/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
#define PMC_MCKR_CSS_Pos 0
#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master Clock Source Selection */
#define PMC_MCKR_CSS(value) ((PMC_MCKR_CSS_Msk & ((value) << PMC_MCKR_CSS_Pos)))
#define   PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_MCKR) Slow Clock is selected */
#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */
#define   PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_MCKR) PLLA Clock is selected */
#define   PMC_MCKR_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_MCKR) Divided UPLL Clock  is selected */
#define PMC_MCKR_PRES_Pos 4
#define PMC_MCKR_PRES_Msk (0x7u << PMC_MCKR_PRES_Pos) /**< \brief (PMC_MCKR) Processor Clock Prescaler */
#define PMC_MCKR_PRES(value) ((PMC_MCKR_PRES_Msk & ((value) << PMC_MCKR_PRES_Pos)))
#define   PMC_MCKR_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_MCKR) Selected clock */
#define   PMC_MCKR_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 2 */
#define   PMC_MCKR_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 4 */
#define   PMC_MCKR_PRES_CLK_8 (0x3u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 8 */
#define   PMC_MCKR_PRES_CLK_16 (0x4u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 16 */
#define   PMC_MCKR_PRES_CLK_32 (0x5u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 32 */
#define   PMC_MCKR_PRES_CLK_64 (0x6u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 64 */
#define   PMC_MCKR_PRES_CLK_3 (0x7u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 3 */
#define PMC_MCKR_MDIV_Pos 8
#define PMC_MCKR_MDIV_Msk (0x3u << PMC_MCKR_MDIV_Pos) /**< \brief (PMC_MCKR) Master Clock Division */
#define PMC_MCKR_MDIV(value) ((PMC_MCKR_MDIV_Msk & ((value) << PMC_MCKR_MDIV_Pos)))
#define   PMC_MCKR_MDIV_EQ_PCK (0x0u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 1. */
#define   PMC_MCKR_MDIV_PCK_DIV2 (0x1u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 2. */
#define   PMC_MCKR_MDIV_PCK_DIV4 (0x2u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 4. */
#define   PMC_MCKR_MDIV_PCK_DIV3 (0x3u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 3. */
#define PMC_MCKR_UPLLDIV2 (0x1u << 13) /**< \brief (PMC_MCKR) UPLL Divisor by 2 */

/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB Input Clock Selection */
#define PMC_USB_USBDIV_Pos 8
#define PMC_USB_USBDIV_Msk (0xfu << PMC_USB_USBDIV_Pos) /**< \brief (PMC_USB) Divider for USB Clock */
#define PMC_USB_USBDIV(value) ((PMC_USB_USBDIV_Msk & ((value) << PMC_USB_USBDIV_Pos)))

/* -------- PMC_PCK[7] : (PMC Offset: 0x0040) Programmable Clock 0 Register -------- */
#define PMC_PCK_CSS_Pos 0
#define PMC_PCK_CSS_Msk (0x7u << PMC_PCK_CSS_Pos) /**< \brief (PMC_PCK[7]) Master Clock Source Selection */
#define PMC_PCK_CSS(value) ((PMC_PCK_CSS_Msk & ((value) << PMC_PCK_CSS_Pos)))
#define   PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_PCK[7]) Slow Clock is selected */
#define   PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_PCK[7]) Main Clock is selected */
#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[7]) PLLA Clock is selected */
#define   PMC_PCK_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_PCK[7]) Divided UPLL Clock is selected */
#define   PMC_PCK_CSS_MCK (0x4u << 0) /**< \brief (PMC_PCK[7]) Master Clock is selected */
#define PMC_PCK_PRES_Pos 4
#define PMC_PCK_PRES_Msk (0xffu << PMC_PCK_PRES_Pos) /**< \brief (PMC_PCK[7]) Programmable Clock Prescaler */
#define PMC_PCK_PRES(value) ((PMC_PCK_PRES_Msk & ((value) << PMC_PCK_PRES_Pos)))

/* -------- PMC_SR : (PMC Offset: 0x0068) Status Register -------- */
#define PMC_SR_MOSCXTS (0x1u << 0) /**< \brief (PMC_SR) Main Crystal Oscillator Status */
#define PMC_SR_LOCKA (0x1u << 1) /**< \brief (PMC_SR) PLLA Lock Status */
#define PMC_SR_MCKRDY (0x1u << 3) /**< \brief (PMC_SR) Master Clock Status */
#define PMC_SR_LOCKU (0x1u << 6) /**< \brief (PMC_SR) UTMI PLL Lock Status */
#define PMC_SR_OSCSELS (0x1u << 7) /**< \brief (PMC_SR) Slow Clock Oscillator Selection */
#define PMC_SR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY3 (0x1u << 11) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY4 (0x1u << 12) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY5 (0x1u << 13) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY6 (0x1u << 14) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_MOSCSELS (0x1u << 16) /**< \brief (PMC_SR) Main Oscillator Selection Status */
#define PMC_SR_MOSCRCS (0x1u << 17) /**< \brief (PMC_SR) Main On-Chip RC Oscillator Status */
#define PMC_SR_CFDEV (0x1u << 18) /**< \brief (PMC_SR) Clock Failure Detector Event */
#define PMC_SR_CFDS (0x1u << 19) /**< \brief (PMC_SR) Clock Failure Detector Status */
#define PMC_SR_FOS (0x1u << 20) /**< \brief (PMC_SR) Clock Failure Detector Fault Output Status */
#define PMC_SR_XT32KERR (0x1u << 21) /**< \brief (PMC_SR) Slow Crystal Oscillator Error */


#define PMC_SCER_USBCLK (0x1u << 5) /**< \brief (PMC_SCER) Enable USB FS Clock */
#define PMC_SCDR_USBCLK (0x1u << 5) /**< \brief (PMC_SCDR) Disable USB FS Clock */
#define PMC_SCSR_USBCLK (0x1u << 5) /**< \brief (PMC_SCSR) USB FS Clock Status */
/* -------- CKGR_UCKR : (PMC Offset: 0x001C) UTMI Clock Register -------- */
#define CKGR_UCKR_UPLLEN (0x1u << 16) /**< \brief (CKGR_UCKR) UTMI PLL Enable */
#define CKGR_UCKR_UPLLCOUNT_Pos 20
#define CKGR_UCKR_UPLLCOUNT_Msk (0xfu << CKGR_UCKR_UPLLCOUNT_Pos) /**< \brief (CKGR_UCKR) UTMI PLL Start-up Time */
#define CKGR_UCKR_UPLLCOUNT(value) ((CKGR_UCKR_UPLLCOUNT_Msk & ((value) << CKGR_UCKR_UPLLCOUNT_Pos)))
/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB Input Clock Selection */
#define PMC_USB_USBDIV_Pos 8
#define PMC_USB_USBDIV_Msk (0xfu << PMC_USB_USBDIV_Pos) /**< \brief (PMC_USB) Divider for USB Clock */
#define PMC_USB_USBDIV(value) ((PMC_USB_USBDIV_Msk & ((value) << PMC_USB_USBDIV_Pos)))


void pmc_enable_periph_clk(uint32_t ul_id);
void pmc_disable_periph_clk(uint32_t ul_id);


#endif /* _SAME70_PMC_INSTANCE_ */
