FS_FAT:=$(TOPDIR)/lib/fatfs

COBJS-y	+=  $(FS_FAT)/ff.o
COBJS-y	+=  $(FS_FAT)/diskio.o
COBJS-y	+=  $(FS_FAT)/option/ccsbcs.o


