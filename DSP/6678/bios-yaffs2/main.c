/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include "yaffs2/yaffsfs.h"
#include <ti/platform/platform.h>

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{

    int handle;
    char test[] = {"aaaaa"};

    System_printf("enter taskFxn()\n");

    handle = yaffs_open("/test.txt", O_CREAT|O_WRONLY|O_APPEND, S_IREAD|S_IWRITE);
    if (handle == -1) {
        System_printf("Create test.txt failed\n");
        goto ttt;
    }
    yaffs_write(handle, test, strlen(test));
    yaffs_close(handle);
    System_printf("Create test.txt OKKKKK\n");
ttt:
    Task_sleep(10);

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
}

/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;
    int re;

    Platform_STATUS status;

    platform_init_flags init_flag;
    platform_init_config init_config;

    init_flag.pll = 0;
    init_flag.ddr = 0;
    init_flag.phy = 0;
    init_flag.ecc = 1;
    init_flag.tcsl = 0;

    init_config.plld = 0;
    init_config.pllm = 0;
    init_config.postdiv = 0;
    init_config.prediv = 0;

    status = platform_init(&init_flag, &init_config);
    if(status != Platform_EOK){
        System_printf("platform_init Error: %d\n", status);
    }
    System_printf("platform_init OK!\n");

    System_printf("enter main()\n");

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
    System_flush();

    yaffs_start_up();
    re = yaffs_mount("nand/user");
    if(re != 0){
        System_printf("yaffs_mount error\n");
    }

    re=yaffs_mkdir("/test",S_IFDIR);
    if(re != 0)
    {
        System_printf("yaffs mkdir error\r\n");
    }

    BIOS_start();    /* does not return */
    return(0);
}
