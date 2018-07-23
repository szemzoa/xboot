SD_CARD:=$(TOPDIR)/lib/qspiflash

COBJS-y	+=  $(SD_CARD)/spi-flash.o
COBJS-y	+=  $(SD_CARD)/spi-nor.o
COBJS-y	+=  $(SD_CARD)/sfdp.o
COBJS-y	+=  $(SD_CARD)/spi-nor-ids.o


