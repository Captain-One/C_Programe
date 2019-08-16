/*
 * common.c
 *
 *  Created on: 2019��6��24��
 *      Author: lin
 */

#include <common.h>

extern UInt16 const core_id;

uint32_t l2_global_address (uint32_t addr)
{
    if(addr > 0x87FFFF){
        return addr;
    }

    return (addr + (0x10000000 + (core_id * 0x1000000)));
}


