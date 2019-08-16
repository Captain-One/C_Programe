#include <common.h>
#include "parameters.h"
#include "dac8550.h"

//#define DAC8550_SYNC	GPIO_OFFSET + 99	//P0

uint16 dac8550_cpl_d_value(uint16 mv)
{
	int32 temp;
	int16 temp2;
	uint16 d_vlaue;

	temp=mv;
	temp2=(temp-2048L)*65536L/4096;

	memcpy(&d_vlaue,&temp2,sizeof(d_vlaue));
	
	return d_vlaue;
}

dac8550Err_t dac8550_init(void)
{
	uint16 temp;
	
	dac8550Err_t dac8550Error;
	dac8550Device_t device ={
	.spi_desc = NULL,
	.spiSetting = &dac8550spisetting,
	};

	struct spi_init_param spi_param;
	int32_t status;

	spi_param.id = DAC8550_SPI_ID;
	spi_param.mode = SPI_MODE_1;
	spi_param.chip_select = DAC8550_SPI_CS;
	spi_param.flags = 0;
	status = spi_init(&device.spi_desc, &spi_param);

	if (status != SUCCESS)
		return DAC8550_ERR;

	mdelay(100);
	
	temp = dac8550_cpl_d_value(2500);
	//temp = 0xFFFF;
	//while(1)
	//{
	dac8550Error = dac8550_write(&device, 0, temp);
	//}

	return dac8550Error;
}

dac8550Err_t dac8550_write(dac8550Device_t *device, uint8 pd, uint16 data)
{
	uint8_t buf[3];
	int32_t status;

	buf[0] = pd;
	buf[1] = data >> 8;
	buf[2] = data & 0xFF;
	status = spi_write_and_read(device->spi_desc, buf, 3);

	if (status != SUCCESS)
	return DAC8550_SPI_FAIL;
	else
	return DAC8550_OK;
}


