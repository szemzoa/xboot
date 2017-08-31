SD_CARD:=$(TOPDIR)/lib/qspiflash

COBJS-y	+=  $(SD_CARD)/qspiflash.o
COBJS-y	+=  $(SD_CARD)/spi-nor.o


