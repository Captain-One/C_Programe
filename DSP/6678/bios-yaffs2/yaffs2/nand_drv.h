/*
 * nand_drv.h
 *
 *  Created on: 2019Äê4ÔÂ10ÈÕ
 *      Author: lin
 */

#ifndef YAFFS2_NAND_DRV_H_
#define YAFFS2_NAND_DRV_H_

#include <stdint.h>
#include <ti/platform/platform.h>

/*********************************
 * Defines and Macros and globals
 *********************************/

#if (PLATFORM_DEBUG)
#define IFPRINT(x)   (x)
#else
#define IFPRINT(x)
#endif

#define SUCCESS                 (0)
#define FAIL                    (1)

// Macros for error
#define NULL_POINTER_ERROR      (2)
#define INVALID_ARGUMENTS       (3)

/* NAND FLASH ADDRESS */
#define NAND_DATA_ADDR  ((volatile uint8_t*)0x30000000)  /*emif16_cs2_base */
#define NAND_ALE_ADDR   ((volatile uint8_t*)0x30002000)
#define NAND_CMD_ADDR   ((volatile uint8_t*)0x30004000)

#define NAND_TYPE_MASK_0X00000020       (0x00000020)

/* NAND FLASH COMMANDS */

#define NAND_ADD_00H                    (0x00)
#define NAND_ADD_08H                    (0x08)
#define NAND_CMD_05H                    (0x05)  /* Random Data Read Command */
#define NAND_CMD_10H                    (0x10)  /* Program Confirm Command */
#define NAND_CMD_30H                    (0x30)
#define NAND_CMD_E0H                    (0xE0)
#define NAND_BLOCK_ERASE                (0x60)  /* Block Erase Command */
#define NAND_ERASE_CONFIRM              (0xD0)  /* Erase Confirm Command */
#define NAND_GET_FEATURES               (0xEE)
#define NAND_OTP_DATA_PROG              (0xA0)
#define NAND_OTP_DATA_PROT              (0xA5)
#define NAND_OTP_DATA_READ              (0xAF)
#define NAND_PAGE_READ                  (0x00)  /* Page Read Command */
#define NAND_PAGE_READ_LAST             (0x3F)  /* Page Read Cache Mode Start Last*/
#define NAND_PAGE_READ_RANDOM           (0x00)
#define NAND_PAGE_READ_SEQUENTIAL       (0x31)  /* page Read Cache mode start */
#define NAND_INT_DATA_MOVE_PROG         (0x85)  /* Program for Internal Data Move */
#define NAND_PROG_PAGE                  (0x80)  /* Program Page Command */
#define NAND_PROG_PAGE_CACHE            (0x80)  /* Program Page command */
#define NAND_RANDOM_DATA_IN             (0x85)  /* Program for internal Data Move */
#define NAND_RANDOM_DATA_READ           (0x05)
#define NAND_INT_DATA_MOVE_READ         (0xA5)
#define NAND_RDID                       (0x90)  /* Read NAND ID Command */
#define NAND_READ_PARAM_PAGE            (0xEC)
#define NAND_STATUS                     (0x70)  /* Read Status command */
#define NAND_READ_UNIQUE_ID             (0xED)
#define NAND_RST                        (0xFF)  /* Reset Command */
#define NAND_RDY                        (0x40)
#define NAND_RDIDADD                    (0x20)

/* Maximum number of ECC bytes per page */
#define NAND_MAX_NUM_ECC_BYTES      10

 /**
  *  Handle to access BOOTCFG registers.
  */
#define hEmif16Cfg     ((CSL_Emif16Regs*)CSL_AEMIF_SLV_CFG_REGS)

 /**
 @}
 */
/****************
 * Defines
 ****************/
#define PACK_ADDR(col, page, block) \
        ((col & 0x00000fff) | ((page & 0x0000003f)<<16) | ((block & 0x000003ff) << 22 ))

// Macros for delay in micro Sec
#define STD_DELAY                   (25)
#define EMIF16_NAND_PROG_TIMEOUT           (100000)
#define EMIF16_NAND_RESET_TIMEOUT          (100000)
#define EMIF16_NAND_BLOCK_ERASE_TIMEOUT    (2000000)
#define EMIF16_WAIT_PIN_POLL_ST_DLY        (10)


// Macros for errors
#define INVALID_NAND_ADDR           (8)
#define NAND_PAGE_WRITE_FAIL        (9)
#define NAND_SPARE_AREA_WRITE_FAIL  (10)
#define NAND_PAGE_READ_FAIL         (11)
#define NAND_SPARE_AREA_READ_FAIL   (12)
#define NAND_BLOCK_ERASE_FAIL       (13)
#define NAND_ID_READ_ERROR          (14)
#define NAND_TWO_BIT_ERROR          (15)
#define INVALID_NAND_DEVICE         (16)

#define NAND_MAN_ID_MICRON          (0x2C)
#define NAND_DEVICE_ID              (0xAC)

#define BYTES_PER_PAGE              (2048)
#define SPARE_BYTES_PER_PAGE        (64)
#define PAGES_PER_BLOCK             (64)
#define TOTAL_BYTES_PER_PAGE        (BYTES_PER_PAGE + SPARE_BYTES_PER_PAGE)
#define BLOCKS_PER_DEVICE           (4096)

// ECC related macros
#define ECC_BLOCK_SIZE              (512)   // in Bytes
#define ECC_SPARE_OFFSET            (SPARE_BYTES_PER_PAGE/(BYTES_PER_PAGE/ECC_BLOCK_SIZE))

// NAND flags
#define NAND_FLAG_LINUX             (0x0)
#define NAND_FLAG_RBL               (0x1)

typedef struct _NAND_ADDR
{
    uint32_t uiColumnAddr;
    uint32_t uiPageAddr;
    uint32_t uiBlockAddr;
} NAND_ADDR;

typedef struct  {
    uint32_t uiDeviceID;        // DeviceID
    uint32_t uiPageCount;       // Page count per block
    uint32_t uiPageSize;        // Byte count per page(include redundant parts)
    uint32_t blk_shift;     // Number of bits by which block address is to be shifted
    uint32_t addr_cycles;       // Number of address cycles
} StdNANDDeviceInfoObj;

//  NAND_info structure
typedef struct  {
    uint32_t uiNandWidth;       // NAND width 1-&gt;16 bits 0-&gt;8 bits
    uint32_t dev_code;      // NAND_DevTable index
    uint32_t uiPageCount;       // page count per block
    uint32_t addr_cycles;       // Number of address cycles
    uint32_t big_block;     // 1 - Big block device, 0 - small block device
    uint32_t uiPageSize;        // Number of bytes in a page including extra data 264/528
    uint32_t blk_shift;     // Number of bits by which block address is to be shifted
    uint32_t page_shift;        // Number of bits by which  page address is to be shifted
    uint32_t numPage;           // Number of pages where boot loader is stored
    uint32_t block;         // starting block number where User boot loader is stored
    uint32_t page;          // starting page number where boot-loader is stored
} StdNANDBootInfoObj;


/************************
 * Function declarations
 ************************/
uint32_t nandInit(void);
uint32_t readNandPage(PLATFORM_DEVICE_info* pNandInfo, NAND_ADDR address, uint8_t* puchBuffer);
uint32_t writeNandPage(PLATFORM_DEVICE_info* pNandInfo, NAND_ADDR address,  uint8_t* puchBuffer);
uint32_t enableNandECC(uint32_t uiUseSoftEcc);
uint32_t nandFlashBlockErase(uint32_t uiBlockNumber);
uint32_t NandGetDetails(PLATFORM_DEVICE_info* pNandInfo);
uint32_t NandReadSpareArea(PLATFORM_DEVICE_info* pNandInfo, uint32_t uiBlkAddr, uint32_t uiPage, uint8_t *pBuffer);
uint32_t NandWriteSpareArea (PLATFORM_DEVICE_info* pNandInfo, uint32_t uiBlkAddr, uint32_t uiPage, uint8_t *pBuffer);

/************************
 * Function declarations
 ************************/

#endif /* YAFFS2_NAND_DRV_H_ */
