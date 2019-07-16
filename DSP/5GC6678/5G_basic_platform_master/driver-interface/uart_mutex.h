/*
 * uart_mutex.h
 *
 *  Created on: 2019Äê7ÔÂ12ÈÕ
 *      Author: Pu
 */

#ifndef UART_MUTEX_H_
#define UART_MUTEX_H_

inline int32_t getSemaphore(uint8_t semNum);
inline int32_t releaseSemaphore(uint8_t semNum);
int __attribute__((format(printf,1,2))) UART_mutex_printf(char *fmt,...);

#endif /* UART_MUTEX_H_ */
