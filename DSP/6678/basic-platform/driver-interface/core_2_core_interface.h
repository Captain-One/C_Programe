/*
 * core_2_core_interface.h
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#ifndef DRIVER_INTERFACE_CORE_2_CORE_INTERFACE_H_
#define DRIVER_INTERFACE_CORE_2_CORE_INTERFACE_H_

Int getDataFromCoreN(Int core_id, Void *buf, uint32_t len);
Int sendDataToCoreN(Int core_id, Void *buf, uint32_t len);

#endif /* DRIVER_INTERFACE_CORE_2_CORE_INTERFACE_H_ */
