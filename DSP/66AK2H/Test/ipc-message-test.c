/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/sysbios/heaps/HeapBuf.h>

#include <ti/ipc/Ipc.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>


#define EVENTID         10
#define LINEID          0

#define Core0_MsgQ0     "creo_msgq0"
#define MSG_SIZE        64
#define HEAPID          0

typedef struct my_msg{
    MessageQ_MsgHeader msgQHeader;
    UInt32             i;
}my_Msg;


Void cbfxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg, UInt32 payload)
{
    System_printf("cbfxn, payload is: %d!\n", payload);
    System_flush(); /* force SysMin output to console */
}

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    UInt16 corenum;
    Int ret;

    MessageQ_Handle msgQ_handle;
    MessageQ_Params msgQ_params;
    MessageQ_QueueId msgQ_id;
    Error_Block         eb;
    my_Msg msgQ_msg;
    my_Msg *pmsgQ_msg;
    IHeap_Handle heap;
    IHeap_Handle srheap;
    Ptr          msg_pool_ptr;
    HeapBuf_Params      heapParams;

    Int msgQ_ret;

    System_printf("enter taskFxn()\n");
    System_flush(); /* force SysMin output to console */

    corenum = MultiProc_self();

    System_printf("enter taskFxn2()\n");
    System_flush(); /* force SysMin output to console */

    if(corenum == 0)
    {
        while(Ipc_attach(1)){
            Task_sleep(1);
        }
        while(Ipc_attach(2)){
            Task_sleep(1);
        }
        while(Ipc_attach(3)){
            Task_sleep(1);
        }
        System_printf("Ipc_attach Ok!\n");
        System_flush();

        MessageQ_Params_init(&msgQ_params);
        msgQ_handle = MessageQ_create(Core0_MsgQ0, &msgQ_params);
        if(msgQ_handle == NULL){
            System_printf("MessageQ_create failed!\n");
        }else{
            System_printf("MessageQ_create Ok!\n");
        }
        System_flush(); /* force SysMin output to console */
        System_printf("core 0-1, pmsgQ_msg ptr :0x%8x\n",&pmsgQ_msg);
        ret = MessageQ_get(msgQ_handle, (MessageQ_Msg *)&pmsgQ_msg, MessageQ_FOREVER);
        if (ret < 0) {
            System_printf("Should not happen; timeout is forever\n");
        }else{
            System_printf("MessageQ_get OK!,i is %d\n",pmsgQ_msg->i);
        }
        System_printf("core 0-2, pmsgQ_msg ptr :0x%8x\n",pmsgQ_msg);
        System_flush();
        while(1);
    }else{
        while(Ipc_attach(0)){
            Task_sleep(1);
        }
        System_printf("Ipc_attach Ok!\n");
        System_flush(); /* force SysMin output to console */

        if(corenum == 1){
            srheap = (IHeap_Handle)SharedRegion_getHeap(1);
            if(srheap == NULL){
                System_printf("SharedRegion_getHeap failed!\n");
            }else{
                System_printf("SharedRegion_getHeap Ok!\n");
            }

            msg_pool_ptr =  Memory_alloc(srheap, 4096, 32, NULL);
            if(msg_pool_ptr == NULL){
                System_printf("Memory_alloc failed!\n");
            }else{
                System_printf("Memory_alloc Ok!msg_pool_ptr:0x%8x\n",msg_pool_ptr);
            }

            HeapBuf_Params_init(&heapParams);
            heapParams.blockSize = 64;
            heapParams.numBlocks = 4;
            heapParams.bufSize = 4096;
            heapParams.align = 32;
            heapParams.buf = msg_pool_ptr;
            Error_init(&eb);

            heap = (IHeap_Handle)HeapBuf_create(&heapParams, &eb);
            if(heap == NULL){
                System_printf("HeapBuf_create failed!\n");
            }else{
                System_printf("HeapBuf_create Ok!\n");
            }
            ret = MessageQ_registerHeap((Ptr)(heap), 0);
            if(ret < 0){
                System_printf("MessageQ_registerHeap failed!\n");
            }else{
                System_printf("MessageQ_registerHeap Ok!\n");
            }
            System_printf("core 1-1, pmsgQ_msg ptr :0x%8x\n",&pmsgQ_msg);
            pmsgQ_msg = (my_Msg *)MessageQ_alloc(0, sizeof(my_Msg));
            if(pmsgQ_msg == NULL){
                System_printf("core %d ,MessageQ alloc failed\n", corenum);
            }else{
                System_printf("core %d ,MessageQ alloc ok\n", corenum);
            }
            System_printf("core 1-2, pmsgQ_msg ptr :0x%8x\n",pmsgQ_msg);
            pmsgQ_msg->i = 128;

            do{
                msgQ_ret = MessageQ_open(Core0_MsgQ0, &msgQ_id);
            }while(msgQ_ret < 0);
            System_printf("core %d ,MessageQ_open Ok!\n", corenum);
            System_printf("MessageQ ID is: %d\n", msgQ_id);

            ret = MessageQ_put(msgQ_id, (MessageQ_Msg)pmsgQ_msg);
            if(ret < 0){
                System_printf("MessageQ_put failed!\n");
            }else{
                System_printf("MessageQ_put Ok!\n");
            }
            System_flush();
            while(1);
        }
    }

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
    Int ipc_ret;
    //UInt16 corenum;

    System_printf("enter main()\n");

    ipc_ret = Ipc_start();
    if(ipc_ret < 0){
        System_printf("Ipc_start failed, failed code is: %d!\n",ipc_ret);
    }else{
        System_printf("Ipc_start Ok!\n");
    }
    //corenum = MultiProc_self();

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
