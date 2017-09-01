CROSS_COMPILE ?= arm-none-eabi-

TOPDIR=$(shell pwd)

CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size
GDB = $(CROSS_COMPILE)gdb
OPENOCD = openocd

CFLAGS = -march=armv7-m -mtune=cortex-m7 -mthumb -ffunction-sections -fdata-sections
CFLAGS += -Os -std=gnu99 -Wall -g -I ./ -I lib/fatfs -I lib/sd -I drivers/ -I cpu/ -I lib -I lib/qspiflash

LDFLAGS = -march=armv7-m -mtune=cortex-m7 -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=reset_handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common
LDSCRIPT = cpu/same70q20.ld

COBJS-y:= xboot.o

include	board/same70-sampione/board.mk
include	cpu/cpu.mk
include	drivers/drivers.mk
include	lib/lib.mk
include	lib/sd/sd.mk
include	lib/qspiflash/qspiflash.mk
include	lib/fatfs/fatfs.mk

SRCS:= $(COBJS-y:.o=.c)
OBJS:= $(SOBJS-y) $(COBJS-y)

all: xboot.elf xboot.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

xboot.elf: $(OBJS) Makefile $(LDSCRIPT)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) -Wl,-Map,xboot.map $(LDFLAGS) -o xboot.elf $(OBJS)

xboot.bin: xboot.elf Makefile
	$(OBJCOPY) -Obinary xboot.elf xboot.bin
	$(OBJDUMP) -S xboot.elf > xboot.lst
	$(SIZE) xboot.elf

clean:
	@rm -f *.o *.elf *.bin *.lst *.map $(COBJS-y)

debug: xboot.elf xboot.bin
	$(GDB) xboot.elf -ex "target remote :3333" -ex "monitor reset halt"

program:
	$(OPENOCD) -f ./openocd.conf
