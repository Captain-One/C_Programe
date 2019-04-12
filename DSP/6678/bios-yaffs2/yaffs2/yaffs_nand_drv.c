/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2018 Aleph One Ltd.
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/*
 * This is an interface module for handling NAND in yaffs2 mode.
 */

/* This code calls a driver that accesses "generic" NAND. In the simulator
 * this is direceted at a file-backed NAND simulator. The NAND access functions
 * should also work with real NAND.
 *
 * This driver is designed for use in yaffs2 mode with a 2k page size and
 * 64 bytes of spare.
 *
 * The spare ares is used as follows:
 * offset 0: 2 bytes bad block marker.
 * offset 2: 8x3 bytes of ECC over the data.
 * offset 26: rest available to store Yaffs tags etc.
 */

//#include "yaffs_nand_drv.h"
#include "yportenv.h"
#include "yaffs_trace.h"

//#include "nand_store.h"
//#include "yaffs_flashif.h"
#include "yaffs_guts.h"
//#include "nanddrv.h"
#include "yaffs_ecc.h"

#include <ti/platform/platform.h>
//#include "nand_drv.h"

//extern PLATFORM_DEVICE_info gDeviceNand;

PLATFORM_DEVICE_info *device_info;

struct nand_context {
	struct nand_chip *chip;
	u8 *buffer;
};

/******************************************************************************
 * Function:    checkBadBlockMark
 *
 *              Checks for the bad block mark. Returns TRUE if a block is marked bad.
 ******************************************************************************/
uint32_t checkBadBlockMark(PLATFORM_DEVICE_info  *p_device, uint32_t block)
{
    //printf("p_device->bblist[block] 0x%02x\n",p_device->bblist[block]);
    if (p_device->bblist[block] != 0xFF)
    {
        return 1;  //bad
    }
    else
    {
        return 0;
    }
}


Platform_STATUS markBlockBad
(
    PLATFORM_DEVICE_info        *p_device,
    uint32_t                    block
)
{
    uint8_t       *spare_data;

    if(p_device == NULL){
        return Platform_EFAIL;
    }

    spare_data = malloc(p_device->spare_size);
    if (spare_data == NULL)
    {
        printf ("Can not allocate spare_data memory!\n");
        return Platform_EFAIL;
    }

    platform_device_read_spare_data(p_device->handle, block, 0, spare_data);

    /* Set all data bytes to 0xff, only set the user defined bad block mark value */
    spare_data[p_device->bboffset] = 0xA5;

    /* Write the data to page */
    platform_device_write_spare_data(p_device->handle, block, 0, spare_data);

    /* Save the user defined bad block mark in bblist */
    p_device->bblist[block] = 0xA5;

    free (spare_data);
    return Platform_EOK;
}

#if 0
static inline struct nand_chip *dev_to_chip(struct yaffs_dev *dev)
{
	struct nand_context *ctxt =
		(struct nand_context *)(dev->driver_context);
	return ctxt->chip;
}

static inline u8 *dev_to_buffer(struct yaffs_dev *dev)
{
	struct nand_context *ctxt =
		(struct nand_context *)(dev->driver_context);
	return ctxt->buffer;
}
#endif

static int yaffs_nand_drv_WriteChunk(struct yaffs_dev *dev, int nand_chunk,
				   const u8 *data, int data_len,
				   const u8 *oob, int oob_len)
{

    uint32_t   offset;
    Platform_STATUS ret;

    offset = nand_chunk * 2048;

    ret = platform_device_write(device_info->handle, offset, (uint8_t *)data, data_len);
    if(ret != Platform_EOK){
        return YAFFS_FAIL;
    }else{
        return YAFFS_OK;
    }
}

static int yaffs_nand_drv_ReadChunk(struct yaffs_dev *dev, int nand_chunk,
				   u8 *data, int data_len,
				   u8 *oob, int oob_len,
				   enum yaffs_ecc_result *ecc_result_out)
{
    uint32_t   offset;
    Platform_STATUS ret;

    offset = nand_chunk * 2048;

    ret = platform_device_read(device_info->handle, offset, data, data_len);

    if(ret != Platform_EOK) {
        if (ecc_result_out)
            *ecc_result_out = YAFFS_ECC_RESULT_UNKNOWN;
        return YAFFS_FAIL;
    }else{
        if (ecc_result_out)
                *ecc_result_out = YAFFS_ECC_RESULT_NO_ERROR;
        return YAFFS_OK;
    }
}

static int yaffs_nand_drv_EraseBlock(struct yaffs_dev *dev, int block_no)
{
    Platform_STATUS ret;

    ret = platform_device_erase_block(device_info->handle, block_no);
    if(ret != Platform_EOK){
        return YAFFS_OK;
    }else{
        return YAFFS_FAIL;
    }
}

static int yaffs_nand_drv_MarkBad(struct yaffs_dev *dev, int block_no)
{
    Platform_STATUS ret;

    ret = platform_device_mark_block_bad(device_info->handle,block_no);
    //ret = markBlockBad(device_info, block_no);

    if(ret != Platform_EOK){
        return YAFFS_OK;
    }else{
        return YAFFS_FAIL;
    }
}

static int yaffs_nand_drv_CheckBad(struct yaffs_dev *dev, int block_no)
{
    Platform_STATUS ret;
    uint8_t *buf;

    buf = malloc(device_info->spare_size);
    if(buf == NULL){
        printf("malloc buf error\n");
        return YAFFS_FAIL;
    }

    ret = platform_device_read_spare_data(device_info->handle, block_no, 0, buf);
    if(ret != Platform_EOK){
            return YAFFS_FAIL;
    }
    //printf("buf[device_info->bboffset]  0x%02x\n", buf[device_info->bboffset]);
    if(buf[device_info->bboffset] != 0xff){
        return  YAFFS_FAIL;  //bad
    }else{
        return YAFFS_OK;
    }
    //ret = checkBadBlockMark(device_info, block_no);
   // if(ret){
   //     return  YAFFS_FAIL;  //bad
   // }else{
   //     return YAFFS_OK;
  //  }

#if 0
	struct nand_chip *chip = dev_to_chip(dev);
	u8 *buffer = dev_to_buffer(dev);
	int nand_chunk = block_no * chip->pages_per_block;
	struct nanddrv_transfer tr[1];

	memset(buffer, 0, chip->spare_bytes_per_page);

	tr[0].buffer = buffer;
	tr[0].offset = chip->data_bytes_per_page;
	tr[0].nbytes = chip->spare_bytes_per_page;

	nanddrv_read_tr(chip, nand_chunk, tr, 1);

	/* Check that bad block marker is not set */
	if(yaffs_hweight8(buffer[0]) + yaffs_hweight8(buffer[1]) < 14)
		return YAFFS_FAIL;
	else
		return YAFFS_OK;
#endif
    //return YAFFS_OK;
}

static int yaffs_nand_drv_Initialise(struct yaffs_dev *dev)
{

    device_info = platform_device_open(PLATFORM_DEVID_MT29F1G08ABCHC, 0);
    if(device_info == NULL){
        return YAFFS_FAIL;
    }else{
        return YAFFS_OK;
    }

#if 0
	struct nand_chip *chip = dev_to_chip(dev);

	(void)chip;
	return YAFFS_OK;
#endif
}

static int yaffs_nand_drv_Deinitialise(struct yaffs_dev *dev)
{
    Platform_STATUS status;
    status = platform_device_close(device_info->handle);
    if(status != Platform_EOK){
        return YAFFS_FAIL;
    }else{
        return YAFFS_OK;
    }

#if 0
	struct nand_chip *chip = dev_to_chip(dev);

	(void) chip;
	return YAFFS_OK;
#endif

}


int yaffs_nand_install_drv(struct yaffs_dev *dev, struct nand_chip *chip)
{
	struct yaffs_driver *drv = &dev->drv;
	//u8 *buffer = NULL;
	//struct nand_context *ctxt = NULL;

	//ctxt = malloc(sizeof(struct nand_context));
	//buffer = malloc(chip->spare_bytes_per_page);

	//if(!buffer || !ctxt)
		//goto fail;

	drv->drv_write_chunk_fn = yaffs_nand_drv_WriteChunk;
	drv->drv_read_chunk_fn = yaffs_nand_drv_ReadChunk;
	drv->drv_erase_fn = yaffs_nand_drv_EraseBlock;
	drv->drv_mark_bad_fn = yaffs_nand_drv_MarkBad;
	drv->drv_check_bad_fn = yaffs_nand_drv_CheckBad;
	drv->drv_initialise_fn = yaffs_nand_drv_Initialise;
	drv->drv_deinitialise_fn = yaffs_nand_drv_Deinitialise;

	//ctxt->chip = chip;
	//ctxt->buffer = buffer;
	dev->driver_context = (void *) 1;

	device_info = platform_device_open(PLATFORM_DEVID_MT29F1G08ABCHC, 0);
    if(device_info == NULL){
        return YAFFS_FAIL;
    }else{
        return YAFFS_OK;
    }

	//return YAFFS_OK;

//fail:
	//free(ctxt);
	//free(buffer);
	//return YAFFS_FAIL;
}
