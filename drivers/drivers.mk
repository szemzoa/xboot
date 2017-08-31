DRIVERS:=$(TOPDIR)/drivers/

COBJS-y	+=  $(DRIVERS)/at91_mci.o
COBJS-y	+=  $(DRIVERS)/at91_pio.o
COBJS-y	+=  $(DRIVERS)/at91_pmc.o
COBJS-y	+=  $(DRIVERS)/at91_usart.o
COBJS-y	+=  $(DRIVERS)/at91_wdt.o
COBJS-y	+=  $(DRIVERS)/at91_qspi.o
COBJS-y	+=  $(DRIVERS)/at91_eefc.o

