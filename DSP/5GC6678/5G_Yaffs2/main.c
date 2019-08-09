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

    int handle = 0;
    char buf[20] = {0};
    int i;

    System_printf("enter taskFxn()\n");
    handle = yaffs_open("/boot/j",O_CREAT | O_RDWR , S_IREAD | S_IWRITE);
    if (handle == -1) {
        System_printf("Create test.txt failed\n");
    }

    yaffs_read(handle, buf, 5);

    for(i = 0; i < 20; i++){
        System_printf("%c ", buf[i]);
        if((i % 5 == 0) && (i != 0))
            System_printf("\n");
    }
    System_printf("\n");
    yaffs_close(handle);
    System_printf("read test.txt OKKKKK\n");
//ttt:
    Task_sleep(10);

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */

    System_exit(0);
}

/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;
    int re;
    int handle;
    char test[] = {"aaaaa"};

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
#if 0
    yaffs_start_up();

    re = yaffs_mount("/boot");
    if(re != 0){
        System_printf("yaffs_mount error\n");
    }

    handle = yaffs_open("/boot/j",O_CREAT | O_RDWR , S_IREAD | S_IWRITE);
    if (handle == -1) {
        System_printf("Create test.txt failed\n");
    }
    yaffs_write(handle, test, strlen(test));
    yaffs_close(handle);
#endif
    BIOS_start();    /* does not return */
    return(0);
}
