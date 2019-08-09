/******************************************************************************
 * Copyright (c) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *****************************************************************************/

/******************************************************************************
 *
 * File Name:  	evmc66x_fpga.c
 *
 * Description:	This file contains the function definitions for accessing
 * 				fpga device registers 
 * 
 ******************************************************************************/
 
/************************
 * Include Files
 ************************/
#include "platform_internal.h"

/******************************************************************************
 *
 * Function:	dspControlUserLEDs
 *
 * Description:	This function enable/disables user LEDs
 *
 * Parameters:	uchUserLEDNum - User LED number (0)
 * 				uchStatus - User LED status
 *
 * Return Value: void
 *
 ******************************************************************************/
void dspControlUserLEDs(DSP_UserLed uchUserLEDNum, DSP_LedStatus uchStatus)
{
	if (DSP_USER_LED0 != uchUserLEDNum) {
		 /* No action for the invalid LED numbers */
		 return;
	}

	/* Turn on/off the corresponding LED bit number */
	switch (uchStatus) {
		case DSP_LED_OFF:
		    gpioSetOutput(DSP_USER_LED0);
			break;
		case DSP_LED_ON:
		    gpioClearOutput(DSP_USER_LED0);
			break;
		default: /* No action */
			break;
	}

	return;
}
