#include "xboot.h"
#include "version.h"
#include "ff.h"
#include "sdcard.h"
#include "fdt.h"
#include "at91_qspi.h"
#include "qspiflash.h"

struct image_info image;
static struct _qspiflash qspiflash;

static void start_kernel(unsigned int kaddr, unsigned int daddr)
{
    void (*kernel)(uint32_t reserved, uint32_t mach, uint32_t dt) = 
	(void (*)(uint32_t, uint32_t, uint32_t))(kaddr);

	kernel(0, ~0UL, daddr);
}

static int boot_image_setup(unsigned char *addr, unsigned int *entry)
{
    unsigned int magic;
    struct linux_uimage_header *uimage_header
			= (struct linux_uimage_header *)addr;

	magic = swap_uint32(uimage_header->magic);
	if (magic == LINUX_UIMAGE_MAGIC) {
		*entry = swap_uint32(uimage_header->entry_point);
		return 0;
	}

	kprintf("** Bad uImage magic: 0x%X\r\r\n", magic);
	return -1;
}

static int load_uimage()
{
	memset(&image, 0, sizeof(struct image_info));
	image.dest = (unsigned char *)CONFIG_KERNEL_LOAD_ADDRESS;
	strcpy(image.filename, CONFIG_KERNEL_FILENAME);
	image.of_dest = (unsigned char *)CONFIG_DTB_LOAD_ADDRESS;
	strcpy(image.of_filename, CONFIG_DTB_FILENAME);

	if ( load_sdcard(&image) != 0 )
	    return -1;

	return 0;
}

int main()
{    
    unsigned int kernel_entry, dtb_address;	
    unsigned int dtb_size, kernel_size;
    struct linux_uimage_header *uimage_header;


	armv7m_caches_invalidate();
	armv7m_caches_disable();

	board_init();

	kprintf("\r\nxboot v%s\r\n", XBOOT_VERSION);

	if ( board_bootsel_pin_state() == CONFIG_BOOTSEL_PIN_SDCARD) {

		kprintf("SD/MMC boot selected\r\n");

		if (load_uimage() != 0 )
		    goto _xboot_error;	
	    
	} else {
		kprintf("QSPI boot selected\r\n");

		qspi_initialize(QSPI0);
		qspi_set_baudrate(QSPI0, CONFIG_QSPIFLASH_BAUDRATE);

		if (qspiflash_configure(&qspiflash, QSPI0) < 0) {
	    	    kprintf("qspi: not configured\r\n");
		    goto _xboot_error;	    
		}

		/* load dtb header */
		qspiflash_read(&qspiflash, CONFIG_DTB_QSPI_ADDRESS, 
		    (void *)CONFIG_DTB_LOAD_ADDRESS, sizeof(struct boot_param_header));

		dtb_size = of_get_dt_total_size((void *)CONFIG_DTB_LOAD_ADDRESS);

		/* load dtb */
		kprintf("QSPI: dt blob: Read from 0x%02X to 0x%X size: %d bytes\r\n", 
		    CONFIG_DTB_QSPI_ADDRESS, CONFIG_DTB_LOAD_ADDRESS, dtb_size);
		
		qspiflash_read(&qspiflash, CONFIG_DTB_QSPI_ADDRESS, 
		    (void *)CONFIG_DTB_LOAD_ADDRESS, dtb_size);

		/* load uImage header */
		qspiflash_read(&qspiflash, CONFIG_KERNEL_QSPI_ADDRESS, 
		    (void *)CONFIG_KERNEL_LOAD_ADDRESS, sizeof(struct linux_uimage_header));

		uimage_header = (struct linux_uimage_header *)CONFIG_KERNEL_LOAD_ADDRESS;
		kernel_size = swap_uint32(uimage_header->size);

		/* load uImage */
		kprintf("QSPI: Image: Read from 0x%02X to 0x%X, size: %d bytes\r\n", 
		    CONFIG_KERNEL_QSPI_ADDRESS, CONFIG_KERNEL_LOAD_ADDRESS, kernel_size);

		qspiflash_read(&qspiflash, CONFIG_KERNEL_QSPI_ADDRESS, 
		    (void *)CONFIG_KERNEL_LOAD_ADDRESS, kernel_size);

		/* switch back to SPI-1-1-1 proto */
		int ret;
		if ((ret = qspiflash_deconfigure(&qspiflash, QSPI0)) < 0) {
	    	    kprintf("qspi: error release flash: %d\r\n", ret);
		    goto _xboot_error;	    
		}
	}

	if ( boot_image_setup((unsigned char *)CONFIG_KERNEL_LOAD_ADDRESS, &kernel_entry) != 0 )
	    goto _xboot_error;	

	dtb_address = CONFIG_DTB_LOAD_ADDRESS;

	kprintf("starting kernel 0x%04x\r\n\r\n", kernel_entry);

	start_kernel(kernel_entry, dtb_address);

	return 0;

_xboot_error:
	cpu_halt();
}

