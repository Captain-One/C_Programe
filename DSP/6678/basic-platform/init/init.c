/*
 * init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: pu
 */

#include "qmss_init.h"
#include "srio_init.h"
#include <xdc/std.h>
#include <xdc/runtime/System.h>

Int  sysInit(Void)
{
    Int re;

    re = ipcInit();
    if(re < 0){
        System_printf("IPC Init error\n");
        return -1;
    }

    re = cppiInit();
    if(re < 0){
        System_printf("cppi Init error\n");
        return -1;
    }
#if 0
    re = srioInit();
    if(re < 0){

    }
#endif
    return 0;
}
