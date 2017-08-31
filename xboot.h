#ifndef __XBOOT_H__
#define __XBOOT_H__

#include <inttypes.h> 
#include <string.h> 
#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "debug.h"
#include "board/same70-sampione/board.h"

/* uImage Header */
#define LINUX_UIMAGE_MAGIC	0x27051956
struct linux_uimage_header {
	unsigned int	magic;
	unsigned int	header_crc;
	unsigned int	time;
	unsigned int	size;
	unsigned int	load;
	unsigned int	entry_point;
	unsigned int	data_crc;
	unsigned char	os_type;
	unsigned char	arch;
	unsigned char	image_type;
	unsigned char	comp_type;
	unsigned char	name[32];
};

#define FILENAME_MAX_LEN	256
struct image_info
{
	unsigned int offset;
	unsigned int length;
	unsigned char *dest;

	unsigned int of_offset;
	unsigned char *of_dest;

	char filename[FILENAME_MAX_LEN];
	char of_filename[FILENAME_MAX_LEN];
};

#endif
