#include "../lmx2594/lmx2594.h"

#include <stdio.h>
#include <common.h>
#include "parameters.h"

static uint32_t _desired_time_to_elapse_ms = 0;

//**********10MHZ 输入后1分频
//const uint16 lmx2594_reg[21]={0x01B1,0x0000,0X004B,0X00F0,0X00AC,0X0022,0X0012,0x0000,0x0000,0X4052,0x0000,0x0000,0X4010,\
//                               0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
//const uint16 lmx2594_reg[21]={0x01B1,0x01F0,0X23FF,0X00F0,0X30AB,0X0003,0X0005,0x0001,0x0000,0X2053,0x0000,0x0000,0X0001,\
//                               0x0000,0x0000,0x0001,0x0000,0x0000,0x001,0x0000,0x0000};
#if 1  //10MHz use
const uint32 lmx2594_reg[79]={0x4E0003,0x4D0000,0x4C000C,0x4B0800,0x4A0000,0x49003F,0x480001,0x470081,0x46C350,0x450000,0x4403E8,\
		0x430000,0x4201F4,0x410000,0x401388,0x3F0000,0x3E0322,0x3D00A8,0x3C0000,0x3B0001,0x3A9001,0x390020,0x380000,0x370000,0x360000,\
		0x350000,0x340820,0x330080,0x320000,0x314180,0x300300,0x2F0300,0x2E07FC,0x2DC0F2,0x2C3223,0x2B0000,0x2A0000,0x290000,0x280000,\
		0x2703E8,0x260000,0x250404,0x2402BC,0x230004,0x220000,0x211E21,0x200393,0x1F03EC,0x1E318C,0x1D318C,0x1C0488,0x1B0002,0x1A0DB0,\
		0x190C2B,0x18071A,0x17007C,0x160001,0x150401,0x14E048,0x1327B7,0x120064,0x11012C,0x100080,0x0F064F,0x0E1E70,0x0D4000,0x0C5001,\
		0x0B0018,0x0A10D8,0x091604,0x082000,0x0740B2,0x06C802,0x0500C8,0x040A43,0x030642,0x020500,0x010808,0x00241C,};
#else
//240MHz
const uint32 lmx2594_reg[79]={0x4E0003, 0x4D0000, 0x4C000C, 0x4B0800, 0x4A0000, 0x49003F, 0x480001, 0x470081,
		0x46C350, 0x450000, 0x4403E8, 0x430000, 0x4201F4, 0x410000, 0x401388, 0x3F0000,
		0x3E0322, 0x3D00A8, 0x3C0000, 0x3B0001, 0x3A9001, 0x390020, 0x380000, 0x370000,
		0x360000, 0x350000, 0x340820, 0x330080, 0x320000, 0x314180, 0x300300, 0x2F0300,
		0x2E07FC, 0x2DC0F2, 0x2C3223, 0x2B014D, 0x2A0000, 0x290000, 0x280000, 0x2703E8,
		0x260000, 0x250404, 0x24003A, 0x230004, 0x220000, 0x211E21, 0x200393, 0x1F03EC,
		0x1E318C, 0x1D318C, 0x1C0488, 0x1B0002, 0x1A0DB0, 0x190C2B, 0x18071A, 0x17007C,
		0x160001, 0x150401, 0x14F848, 0x1327B7, 0x120064, 0x11012C, 0x100080, 0x0F064F,
		0x0E1E70, 0x0D4000, 0x0C5001, 0x0B0018, 0x0A1358, 0x090604, 0x082000, 0x0740B2,
		0x06C802, 0x0500C8, 0x04C843, 0x030642, 0x020500, 0x010808, 0x00259C};

//122.88MHz

/*const uint32 lmx2594_reg[79]={0x4E0143, 0x4D0000, 0x4C000C, 0x4B0800, 0x4A0000, 0x49003F, 0x480001, 0x470081, 0x46C350, 0x450000, 0x4403E8,
		0x430000, 0x4201F4, 0x410000, 0x401388, 0x3F0000, 0x3E0322, 0x3D00A8, 0x3C0000, 0x3B0001, 0x3A9001, 0x390020,
		0x380000, 0x370000, 0x360000, 0x350000, 0x340820, 0x330080, 0x320000, 0x314180, 0x300300, 0x2F0300, 0x2E07FC,
		0x2DC0F2, 0x2C3223, 0x2B03CA, 0x2A0000, 0x290000, 0x280000, 0x2703E8, 0x260000, 0x250404, 0x240038, 0x230004,
		0x220000, 0x211E21, 0x200393, 0x1F03EC, 0x1E318C, 0x1D318C, 0x1C0488, 0x1B0002, 0x1A0DB0, 0x190C2B, 0x18071A,
		0x17007C, 0x160001, 0x150401, 0x14F848, 0x1327B7, 0x120064, 0x11013C, 0x100080, 0x0F064F, 0x0E1E70, 0x0D4000,
		0x0C5001, 0x0B0018, 0x0A10D8, 0x091604, 0x082000, 0x0740B2, 0x06C802, 0x0500C8, 0x04C843, 0x030642, 0x020500,
		0x010808, 0x00259C };*/
//245.76MHz use
/*
const uint32 lmx2594_reg[79]={0x4E0003,0x4D0000,0x4C000C,0x4B0800,0x4A0000,0x49003F,0x480001,0x470081,0x46C350,0x450000,0x4403E8,
		0x430000,0x4201F4,0x410000,0x401388,0x3F0000,0x3E0322,0x3D00A8,0x3C0000,0x3B0001,0x3A9001,0x390020,0x380000,0x370000,0x360000,
		0x350000,0x340820,0x330080,0x320000,0x314180,0x300300,0x2F0300,0x2E07FC,0x2DC0F2,0x2C3223,0x2B03C6,0x2A0000,0x290000,0x280000,
		0x2703E8,0x260000,0x250404,0x240038,0x230004,0x220000,0x211E21,0x200393,0x1F03EC,0x1E318C,0x1D318C,0x1C0488,0x1B0002,0x1A0DB0,
		0x190C2B,0x18071A,0x17007C,0x160001,0x150401,0x14E048,0x1327B7,0x120064,0x11012C,0x100080,0x0F064F,0x0E1E70,0x0D4000,0x0C5001,
		0x0B0018,0x0A10D8,0x090604,0x082000,0x0740B2,0x06C802,0x0500C8,0x04C843,0x030642,0x020500,0x010809,0x00259C};
*/
#endif

lmx2594Err_t lmx2594_init(void)
{
	uint16 check;
    uint8 i;

//    lmx2594Err_t ad9528Error;
    lmx2594Device_t device = {
    .gpio_sync = NULL,
    .gpio_sysrefred = NULL,
	.gpio_muxout = NULL,
	.spi_desc = NULL,
    .spiSetting = &lmx2594spisetting,
    };

    struct spi_init_param spi_param;
    int32_t status;

	status  = gpio_get(&device.gpio_muxout, LMX2594_MUX_OUT);
	status |= gpio_get(&device.gpio_sync, LMX2594_SYN);
	status |= gpio_get(&device.gpio_sysrefred, LMX2594_SYSREFREQ);

	spi_param.id = LMX2594_SPI_ID;
	spi_param.mode = SPI_MODE_0;
	spi_param.chip_select = LMX2594_SPI_CS;
	spi_param.flags = 0;
	status |= spi_init(&device.spi_desc, &spi_param);

	if (status != SUCCESS)
		return LMX2594_ERR;

/*************reset***************/
	lmx2594_write(&device, 0, 0x251D);//先关电
	mdelay(16);
	lmx2594_write(&device, 0, 0x251C);//上电
	lmx2594_write(&device, 0, 0x251E);//复位寄存器
	lmx2594_write(&device, 0, 0x251C);//复位结束
	mdelay(16);

/*************set Frequncy***************/
	for (i = 0; i < 79; i++)
	{
		lmx2594_write(&device, (uint8)((lmx2594_reg[i] >> 16) & 0x00FF), (uint16)(lmx2594_reg[i] & 0x0000FFFF)); //REG
	}
	mdelay(16);

/*************Write back R0***************/
	lmx2594_write(&device, (uint8)((lmx2594_reg[78] >> 16) & 0x00FF), (uint16)(lmx2594_reg[78] & 0x0000FFFF));

	return LMX2594_OK;
}


lmx2594Err_t lmx2594_write(lmx2594Device_t *device, uint8 addr, uint16 data)
{
	uint8_t buf[4];
	int32_t status;

	buf[0] = addr;
	buf[1] = data >> 8;
	buf[2] = data & 0xFF;
	status = spi_write_and_read(device->spi_desc, buf, 3);

	if (status != SUCCESS)
	return LMX2594_SPI_FAIL;
	else
	return LMX2594_OK;
}



