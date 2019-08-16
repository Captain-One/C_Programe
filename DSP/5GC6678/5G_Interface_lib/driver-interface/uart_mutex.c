/*
 * uart_mutex.c
 *
 *  Created on: 2019Äê7ÔÂ12ÈÕ
 *      Author: Pu
 */
#include <stdio.h>

#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/src/UART_osal.h>
#include <ti/drv/uart/soc/UART_soc.h>

#include <ti/csl/soc.h>
#include <ti/csl/csl_semAux.h>

#define UART_SEMAPHORE        0

extern uint8_t core_ID;

inline int32_t getSemaphore(uint8_t semNum)
{
    volatile int re ;

    re = CSL_semIsFree(semNum);

  //  re = CSL_semGetFlags(core_ID);
    while(re == FALSE)
    {
        UART_osalDelay(1U);
        re = CSL_semIsFree(semNum);
    }

    re = CSL_semAcquireCombined(semNum);
    if(re != 0)
        goto check_free;

    do{
        re = CSL_semGetFlags(core_ID);
    }while(!(re & (1 << semNum)));

    CSL_semClearFlags(core_ID, re);

    re = CSL_semGetFlags(core_ID);
    if( re != 0)
        return -1;

check_free:
    if(CSL_semIsFree(semNum) == TRUE)
        return -1;

    return 0;
}

inline int32_t releaseSemaphore(uint8_t semNum)
{
    int re;

    CSL_semReleaseSemaphore (semNum);

   // if(CSL_semIsFree(semNum) == FALSE)
   //     return -1;

    re = CSL_semGetErrorCode();
    if(re != 0)
        return -1;

    return 0;
}

int __attribute__((format(printf,1,2))) UART_mutex_printf(char *fmt,...)
{
    int32_t re;

    re = getSemaphore(UART_SEMAPHORE);
    if(re < 0)
        return re;

    va_list args;
    va_start(args,fmt);
    UART_printf(fmt,args);
    va_end(args);

    re = releaseSemaphore(UART_SEMAPHORE);
    if(re < 0)
        return re;

    return 0;
}

