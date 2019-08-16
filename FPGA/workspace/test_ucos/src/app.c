/*
*********************************************************************************************************
*                                             uCOS XSDK BSP                               
*                                                                                         
*                      (c) Copyright 2014-2019; Silicon Laboratories Inc.,                
*                             400 W. Cesar Chavez, Austin, TX 78701                       
*                                                                                         
*                All rights reserved. Protected by international copyright laws.          
*                                                                                         
*               Your use of this software is subject to your acceptance of the terms      
*               of a Silicon Labs Micrium software license, which can be obtained by      
*               contacting info@micrium.com. If you do not agree to the terms of this     
*               license, you may not use this software.                                   
*                                                                                         
*               Please help us continue to provide the Embedded community with the finest 
*               software available. Your honesty is greatly appreciated.                  
*                                                                                         
*                 You can find our product's documentation at: doc.micrium.com            
*                                                                                         
*                       For more information visit us at: www.micrium.com                 
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          SETUP INSTRUCTIONS
*
*   This demonstration project illustrate a basic uC/OS-III project with simple "hello world" output.
*
*   By default some configuration steps are required to compile this example :
*
*   1. Include the require Micrium software components
*       In the BSP setting dialog in the "overview" section of the left pane the following libraries
*       should be added to the BSP :
*
*           ucos_common
*           ucos_osiii
*           ucos_standalone
*
*   2. Kernel tick source - (Not required on the Zynq-7000 PS)
*       If a suitable timer is available in your FPGA design it can be used as the kernel tick source.
*       To do so, in the "ucos" section select a timer for the "kernel_tick_src" configuration option.
*
*   3. STDOUT configuration
*       Output from the print() and UCOS_Print() functions can be redirected to a supported UART. In
*       the "ucos_standalone" section the stdout configuration will list the available UARTs.
*
*   Troubleshooting :
*       By default the Xilinx SDK may not have selected the Micrium drivers for the timer and UART.
*       If that is the case they must be manually selected in the drivers configuration section.
*
*       Finally make sure the FPGA is programmed before debugging.
*
*
*   Remember that this example is provided for evaluation purposes only. Commercial development requires
*   a valid license from Micrium.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdio.h>
#include  <Source/os.h>
#include  <ucos_bsp.h>
#include <cpu.h>
#include <ucos_bsp.h>
#include <ucos_int.h>
#include <xparameters.h>
#include <KAL/kal.h>

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  MainTask (void *p_arg);


/*
*********************************************************************************************************
*                                               main()
*
* Description : Entry point for C code.
*
*********************************************************************************************************
*/

int main()
{

    UCOSStartup(MainTask);

    return 0;
}


/*
*********************************************************************************************************
*                                             MainTask()
*
* Description : Startup task example code.
*
* Returns     : none.
*
* Created by  : main().
*********************************************************************************************************
*/
OS_TCB Task1TCB;
OS_TCB Task2TCB;

CPU_STK Task1Stk[128];
CPU_STK Task2Stk[128];

OS_SEM  TestSem;
void Task1(void *p_arg)
{
	OS_ERR       os_err;

	OSSemCreate(&TestSem, "test sem", 0, &os_err);
	if(os_err != OS_ERR_NONE)
	{
		UCOS_Print("task 1 create sem error \r\n");
	}

	 while (DEF_TRUE) {
	        OSTimeDlyHMSM(0, 0, 10, 0, OS_OPT_TIME_HMSM_STRICT, &os_err);
	        OSSemPost(&TestSem, OS_OPT_POST_1, &os_err);
	        if(os_err != OS_ERR_NONE)
			{
				UCOS_Print("task 1 post sem error \r\n");
			}else{
				UCOS_Print("task 1 post sem ok! waiting task 2 response\r\n\n");
			}
			OSSemPend(&TestSem, 0, OS_OPT_PEND_BLOCKING, NULL, &os_err);
			if(os_err  != OS_ERR_NONE){
				UCOS_Print("task 1 pend sem error!\r\n");
			}else{
				UCOS_Print("task 1 get Task 2 response !\r\n");
			}
	    }
}

void Task2(void *p_arg)
{
	OS_ERR       os_err;
	 while (DEF_TRUE) {
		 UCOS_Print("waiting task 1 post sem ....\r\n\n");
		 OSSemPend(&TestSem, 0, OS_OPT_PEND_BLOCKING, NULL, &os_err);
		 if(os_err != OS_ERR_NONE)
		 {
			UCOS_Print("task 2 pend sem error \r\n");
		 }
		 UCOS_Print("get task 1 sem, waiting 4s response task 1\r\n");
		 OSTimeDlyHMSM(0, 0, 4, 0, OS_OPT_TIME_HMSM_STRICT, &os_err);
		 OSSemPost(&TestSem, OS_OPT_POST_1, &os_err);
		 if(os_err != OS_ERR_NONE)
		 {
			 UCOS_Print("task 2 post sem error \r\n");
		 }else{
			 UCOS_Print("task 2 response OK!\r\n");
		 }
	    }
}

OS_TCB  TaskCreateTCB;
CPU_STK TaskCreateStk[128];
void TaskCreate(void *p_arg)
{
	OS_ERR       os_err;

	UCOS_Print ("Enter Task Create\r\n");

	OSTaskCreate(&Task1TCB,
				  "Task 1",
				  Task1,
				  0,
				  5,
				 &Task1Stk[0],
				  0,
				  128,
				  0,
				  0,
				  DEF_NULL,
				 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 &os_err);

	OSTaskCreate(&Task2TCB,
				  "Task 2",
				  Task2,
				  0,
				  5,
				 &Task2Stk[0],
				  0,
				  128,
				  0,
				  0,
				  DEF_NULL,
				 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 &os_err);
}



void  MainTask (void *p_arg)
{
    OS_ERR       os_err;

    UCOS_Print ("Hello world from the main task\r\n");

    OSTaskCreate(&TaskCreateTCB,
				  "Task Create",
				  TaskCreate,
				  0,
				  5,
				 &TaskCreateStk[0],
				  0,
				  128,
				  0,
				  0,
				  DEF_NULL,
				 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 &os_err);
    while (DEF_TRUE) {
        OSTimeDlyHMSM(0, 0, 10, 0, OS_OPT_TIME_HMSM_STRICT, &os_err);
        UCOS_Print("Periodic output every 6 seconds from the main task\r\n");
    }

}

