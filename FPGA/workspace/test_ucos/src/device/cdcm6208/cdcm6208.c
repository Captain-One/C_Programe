#include <stdio.h>
#include <common.h>
#include "parameters.h"
#include "cdcm6208.h"

static uint32_t _desired_time_to_elapse_ms = 0;

//**********10MHZ  ‰»Î∫Û1∑÷∆µ
//const uint16 cdcm6208_reg[21]={0x01B1,0x0000,0X004B,0X00F0,0X00AC,0X0022,0X0012,0x0000,0x0000,0X4052,0x0000,0x0000,0X4010,\
//                               0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
//const uint16 cdcm6208_reg[21]={0x01B1,0x01F0,0X23FF,0X00F0,0X30AB,0X0003,0X0005,0x0001,0x0000,0X2053,0x0000,0x0000,0X0001,\
//                               0x0000,0x0000,0x0001,0x0000,0x0000,0x001,0x0000,0x0000};
#if 0
const uint16 cdcm6208_reg[21]={0x01B1,0x0060,0X05FF,0X00F5,0X30B4,0X0023,0X0004,0x0023,0x0004,0x40D3,0x0000,0x0000,0X0001,\
                               0x0000,0x0000,0x0001,0x0000,0x0000,0x0001,0x0000,0x0000};
#else  //test
const uint16 cdcm6208_reg[21]={0x02BB,0x0060,0X05FF,0X00F5,0X30AB,0X0183,0X0004,0x0001,0x0000,0X4053,0x0000,0x0000,0X0001,\
		                       0x0000,0x0000,0x0001,0x0000,0x0000,0x0001,0x0000,0x0000};

//const uint16 cdcm6208_reg[21]={0x01B1,0x0000,0X004B,0X00F0,0X00AC,0X0022,0X0012,0x0000,0x0000,0X4052,0x0000,0x0000,0X4010,\
//                               0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
#endif

cdcm6208Err_t cdcm6208_init(void)
{
	uint16 check;
    uint8 i;

//    cdcm6208Err_t ad9528Error;
    cdcm6208Device_t device = {
    .gpio_resetb = NULL,
    .gpio_ref_sel = NULL,
	.spi_desc = NULL,
    .spiSetting = &cdcm6208spisetting,
    };

    struct spi_init_param spi_param;
    int32_t status;

	status  = gpio_get(&device.gpio_resetb, CDCM6208_RST);
	status |= gpio_get(&device.gpio_ref_sel, CDCM6208_REF_SEL);

	spi_param.id = CDCM6208_SPI_ID;
	spi_param.mode = SPI_MODE_0;
	spi_param.chip_select = CDCM6208_SPI_CS;
	spi_param.flags = 0;
	status |= spi_init(&device.spi_desc, &spi_param);

	if (status != SUCCESS)
		return CDCM6208_ERR;

	//reset;
	gpio_direction_output(device.gpio_resetb, 0);
	mdelay(100);
	gpio_direction_output(device.gpio_resetb, 1);
	mdelay(100);

	gpio_direction_output(device.gpio_resetb, 0);
	mdelay(100);


	//ref select
	gpio_direction_output(device.gpio_ref_sel, 1);

	cdcm6208_read(&device, 40, &check);
	printf("device version %d\n",check);

	cdcm6208_read(&device, 21, &check);
	printf("21 reg %d\n",check);

//while(1){
	for(i=0;i<21;i++)
	{
		cdcm6208_write(&device, i,cdcm6208_reg[i]);
		cdcm6208_setTimeout_ms(1000);
#if 1
		do{
			cdcm6208_read(&device, i, &check);
		    if(cdcm6208_hasTimeoutExpired() > 0) {
				printf("check cdcm6208 register %d time out, check value : 0x%02x\n", i, check);
				//return CDCM6208_ERR;
				break;
			}
		}while(check!=cdcm6208_reg[i]);
#endif
	}
//}
	gpio_direction_output(device.gpio_resetb, 1);
    mdelay(100);
	return CDCM6208_OK;
}


cdcm6208Err_t cdcm6208_write(cdcm6208Device_t *device, uint16 addr, uint16 data)
{
	uint8_t buf[4];
	int32_t status;

	buf[0] = (addr >> 8) & 0x7F;
	buf[1] = addr & 0xFF;
	buf[2] = data >> 8;
	buf[3] = data & 0xFF;
	status = spi_write_and_read(device->spi_desc, buf, 4);

	if (status != SUCCESS)
	return CDCM6208_SPI_FAIL;
	else
	return CDCM6208_OK;
}
 
cdcm6208Err_t cdcm6208_read(cdcm6208Device_t *device, uint16 addr, uint16 *readdata)
{
	uint8_t buf[4];
	int32_t status;

	buf[0] = 0x80 | ((addr >> 8) & 0x7F);
	buf[1] = addr & 0xFF;
	buf[2] = 0x00;
	buf[3] = 0x00;
	status = spi_write_and_read(device->spi_desc, buf, 4);
	*readdata = ((uint16_t)buf[2] << 8) | buf[3];

	if (status != SUCCESS)
		return CDCM6208_SPI_FAIL;
	else
		return CDCM6208_OK;
}

cdcm6208Err_t cdcm6208_setTimeout_ms(uint32_t timeOut_ms)
{
	_desired_time_to_elapse_ms = timeOut_ms;

	return CDCM6208_OK;
}

/**
 * \brief Verify if the desired time has elapsed
 */
cdcm6208Err_t cdcm6208_hasTimeoutExpired(void)
{
	udelay(1000);

	_desired_time_to_elapse_ms--;
	if (_desired_time_to_elapse_ms > 0)
		return CDCM6208_OK;

	return CDCM6208_ERR;
}



