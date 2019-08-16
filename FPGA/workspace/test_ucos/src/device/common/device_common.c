/*
 * device_common.c
 *
 *  Created on: 2019Äê8ÔÂ16ÈÕ
 *      Author: Pu
 */

#include  <Source/os.h>
#include <device_struct.h>

adiHalErr_t Device_setTimeout_10ms(Device_t *device, uint32_t timeOut_ms)
{
	device->_desired_time_to_elapse_10ms = timeOut_ms;

	return ADIHAL_OK;
}

/**
 * \brief Verify if the desired time has elapsed
 */
adiHalErr_t Device_hasTimeoutExpired(Device_t *device)
{
	OSTimeDly(10);

	device->_desired_time_to_elapse_10ms--;
	if (device->_desired_time_to_elapse_10ms > 0)
		return ADIHAL_OK;

	return ADIHAL_ERR;
}
