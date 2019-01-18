/* 
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdarg.h>

/* XDC includes */
#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>

/* IPC includes */
#include <ti/ipc/SharedRegion.h>
#include <ti/ipc/GateMP.h>

/* SYSBIOS includes */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/c66/Cache.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/knl/Semaphore.h>

 /* CSL modules */
#include <ti/csl/csl_semAux.h>
/* CSL Cache module includes */
#include <ti/csl/csl_cacheAux.h>
/* CSL XMC module includes */
#include <ti/csl/csl_xmcAux.h>

#if (defined(DEVICE_C6657) || defined(DEVICE_C6678) || defined(DEVICE_K2H) || defined(DEVICE_K2K))
/* SRIO LLD */
#include <ti/drv/srio/srio_drv.h>
#endif
 
#include <ti/transport/ipc/c66/example/common_src/bench_common.h>

 /**********************************************************************
 ****************************** Defines *******************************
 **********************************************************************/
#define CPPI_HW_SEM         1
#define QMSS_HW_SEM         2
#define QMSS_ACC_HW_SEM     3
#if (defined(DEVICE_C6657) || defined(DEVICE_C6678) || defined(DEVICE_K2H) || defined(DEVICE_K2K))
#define SRIO_HW_SEM         4
#endif

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
uint32_t qmssMallocCounter = 0;
uint32_t qmssFreeCounter   = 0;
uint32_t cppiMallocCounter = 0;
uint32_t cppiFreeCounter   = 0;
uint32_t rmMallocCounter   = 0;
uint32_t rmFreeCounter     = 0;
#if (defined(DEVICE_C6657) || defined(DEVICE_C6678) || defined(DEVICE_K2H) || defined(DEVICE_K2K))
uint32_t srioMallocCounter = 0;
uint32_t srioFreeCounter   = 0;
#endif

/**********************************************************************
 ************************** Extern Variables **************************
 **********************************************************************/


/**********************************************************************
 *************************** OSAL Functions **************************
 **********************************************************************/

#if (defined(DEVICE_C6657) || defined(DEVICE_C6678) || defined(DEVICE_K2H) || defined(DEVICE_K2K))
/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *  @param[in]  numBytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
void *Osal_srioMalloc(uint32_t numBytes)
{
    Error_Block  errorBlock;
    void        *ptr;

    /* Increment the allocation counter. */
    srioMallocCounter++;
    /* Allocate the memory. */
    ptr = Memory_alloc(NULL, numBytes, 0, &errorBlock);

    /* Return the allocated memory block. */
    return(ptr);
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean up a specific memory block and is called
 *      from the SRIO Driver. 
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *  @param[in]  size
 *      Size of the memory block being cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioFree (void *ptr, uint32_t size)
{
    /* Increment the free counter. */
    srioFreeCounter++;
    Memory_free(NULL, ptr, size);
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a block of memory for all the data
 *      buffer operations. This function is called by the application.
 *
 *  @param[in]  numBuffers
 *      Number of data buffers
 *  @param[in]  dataBufferSize
 *      Size of each data buffer
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t Osal_dataBufferInitMemory(uint32_t dataBufferSize)
{

    /* Using RAW sockets so SRIO doesn't have to handle data buffer
     * management */
    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to allocate a data buffer of the specified
 *      size. Data buffers should always be allocated from the global
 *      address space.
 *
 *  @param[in]  numBytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
void *Osal_srioDataBufferMalloc(uint32_t numBytes)
{
    /* Using RAW sockets so SRIO doesn't have to handle data buffer
     * management */
    return NULL;
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean up a previously allocated data buffer
 *      block. All data buffers are in the global address space
 *
 *  @param[in]  ptr
 *      Pointer to the data buffer block to be cleaned up
 *  @param[in]  size
 *      Size of the data buffer
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioDataBufferFree(void *ptr, uint32_t numBytes)
{
    /* Using RAW sockets so SRIO doesn't have to handle data buffer
     * management */
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is the SRIO OSAL Logging API which logs 
 *      the messages on the console.
 *
 *  @param[in]  fmt
 *      Formatted String.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioLog(char *fmt, ...)
{
    /* System_printf(fmt); */
}

/**
 *  @b Description
 *  @n
 *      The function is used to create a critical section.
 *
 *  @retval
 *      Semaphore Handle created
 */
void *Osal_srioCreateSem(void)
{
    return((void *)Semaphore_create(0, NULL, NULL));
}

/**
 *  @b Description
 *  @n
 *      The function is used to delete a critical section.
 *
 *  @param[in]  semHandle
 *      Semaphore handle to be deleted
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioDeleteSem(void *semHandle)
{
    Semaphore_delete(semHandle);
}

/**
 *  @b Description
 *  @n
 *      The function is used to pend on a semaphore
 *
 *  @param[in]  semHandle
 *      Semaphore handle on which the API will pend
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioPendSem(void *semHandle)
{
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);
}

/**
 *  @b Description
 *  @n
 *      The function is used to post a semaphore
 *
 *  @param[in]  semHandle
 *      Semaphore handle which will be posted
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioPostSem(void *semHandle)
{
    Semaphore_post(semHandle);
}

/**
 *  @b Description
 *  @n
 *      This is the Multicore OSAL Implementation to protect the driver shared
 *      resources across multiple cores.
 *
 *  @retval
 *      Semaphore Opaque Handle
 */
void *Osal_srioEnterMultipleCoreCriticalSection(void)
{
    while ((CSL_semAcquireDirect(SRIO_HW_SEM)) == 0);
    return(NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section which was protecting
 *      shared resources from access across multiple cores.
 *
 *  @param[in]  critSectHandle
 *      Semaphore opaque handle.
 *
 *  @retval
 *      None
 */
void Osal_srioExitMultipleCoreCriticalSection(void *critSectHandle)
{
    CSL_semReleaseSemaphore(SRIO_HW_SEM);
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to provide critical section to prevent access of
 *      shared resources from single core and multiple threads.  
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needs critical section to protect its resources.
 *
 *  @retval
 *      Opaque handle
 */
void *Osal_srioEnterSingleCoreCriticalSection(Srio_DrvHandle drvHandle)
{
    return((void*)Hwi_disable());
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section access of shared
 *      resources from single cores.
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needed critical section to protect its resources.
 *  @param[in]  critSectHandle
 *      Opaque handle retreived when the Single Core Protection Enter API
 *      was called
 *
 *  @retval
 *      Not Applicable.
 */
void Osal_srioExitSingleCoreCriticalSection(void *critSectHandle)
{
    Hwi_enable();
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to indicate that
 *      its about to access a block of memory and we need to ensure
 *      that the cache contents for this block are invalidated before
 *      we try and use it.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer which is being accessed
 *  @param[in]  size
 *      Size of the buffer which is to be accessed.
 *
 *  @retval
 *      None
 */
void Osal_srioBeginMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

#ifdef L2_CACHE
    /* Invalidate L2 cache. This should invalidate L1D as well.
     * Wait until operation is complete. */
    CACHE_invL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Invalidate L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_invL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to indicate that its
 *      ending access to a block of memory. We need to ensure that the
 *      contents of the cache are written back to the actual memory.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer
 *  @param[in]  size
 *      Size of the buffer
 *
 *  @retval
 *      None
 */
void Osal_srioEndMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

#ifdef L2_CACHE
    /* Writeback L2 cache. This should Writeback L1D as well.
     * Wait until operation is complete. */
    CACHE_wbL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Writeback L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_wbL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is invoked by the SRIO Driver to indicate that a
 *      descriptor is being accessed.
 *
 *  @param[in]  drvHandle
 *      Driver Instance for which descriptor is being accessed.
 *  @param[in]  ptr
 *      Pointer to the descriptor being accessed
 *  @param[in]  descSize
 *      Size of the descriptor (Only valid for Driver Managed)
 *
 *  @retval
 *      None
 */
void Osal_srioBeginDescriptorAccess(Srio_DrvHandle drvHandle, void *ptr,
                                    uint32_t descSize)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

#ifdef L2_CACHE
    /* Invalidate L2 cache. This should invalidate L1D as well.
     * Wait until operation is complete. */
    CACHE_invL2(ptr, descSize, CACHE_FENCE_WAIT);
#else
    /* Invalidate L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_invL1d(ptr, descSize, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is invoked by the SRIO Driver to indicate that a
 *      descriptor is finished being accessed.
 *
 *  @param[in]  drvHandle
 *      Driver Instance for which descriptor is being accessed.
 *  @param[in]  ptr
 *      Pointer to the descriptor being accessed
 *  @param[in]  descSize
 *      Size of the descriptor (Only valid for Driver Managed)
 *
 *  @retval
 *      None
 */
void Osal_srioEndDescriptorAccess(Srio_DrvHandle drvHandle, void *ptr,
                                  uint32_t descSize)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

#ifdef L2_CACHE
    /* Writeback L2 cache. This should Writeback L1D as well.
     * Wait until operation is complete. */
    CACHE_wbL2(ptr, descSize, CACHE_FENCE_WAIT);

#else
    /* Writeback L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_wbL1d(ptr, descSize, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);
    return;
}
#endif

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *      Note: If the LLD is used by applications on multiple core, the
 *      "cppiHeap" should be in shared memory
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
void *Osal_cppiMalloc(uint32_t num_bytes)
{
    Error_Block errorBlock;

    /* Increment the allocation counter. */
    cppiMallocCounter++;

    /* Allocate memory. */
    return(Memory_alloc(SharedRegion_getHeap(0), num_bytes, 0, &errorBlock));
}

/**
 *  @b Description
 *  @n
 *      The function is used to free a memory block of the specified size
 *      allocated using Osal_cppiMalloc() API.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *
 *  @param[in]  size
 *      Size of the memory block to be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_cppiFree(void *ptr, uint32_t size)
{
    /* Increment the free counter. */
    cppiFreeCounter++;
    Memory_free(SharedRegion_getHeap(0), ptr, size);
}

/**
 *  @b Description
 *  @n
 *      The function is used to enter a critical section.
 *      Function protects against 
 *
 *      access from multiple cores 
 *      and
 *      access from multiple threads on single core
 *
 *  @retval
 *      Handle used to lock critical section
 */
void *Osal_cppiCsEnter(void)
{
    while ((CSL_semAcquireDirect(CPPI_HW_SEM)) == 0);
    return(NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is used to exit a critical section
 *      protected using Osal_cppiCsEnter() API.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_cppiCsExit(void *CsHandle)
{
    CSL_semReleaseSemaphore(CPPI_HW_SEM);
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is the CPPI OSAL Logging API which logs
 *      the messages on the console.
 *
 *  @param[in]  fmt
 *      Formatted String.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_cppiLog(char *fmt, ... )
{
}

/**
 *  @b Description
 *  @n
 *      The function is used to indicate that a block of memory is
 *      about to be accessed. If the memory block is cached then this
 *      indicates that the application would need to ensure that the
 *      cache is updated with the data from the actual memory.
 *
 *  @param[in]  ptr
 *       Address of memory block
 *
 *  @param[in]  size
 *       Size of memory block
 *
 *  @retval
 *      Not Applicable
 */
void Osal_cppiBeginMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

#ifdef L2_CACHE
    /* Invalidate L2 cache. This should invalidate L1D as well.
     * Wait until operation is complete. */
    CACHE_invL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Invalidate L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_invL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to indicate that the block of memory has
 *      finished being accessed. If the memory block is cached then the
 *      application would need to ensure that the contents of the cache
 *      are updated immediately to the actual memory.
 *
 *  @param[in]  ptr
 *       Address of memory block
 *
 *  @param[in]  size
 *       Size of memory block
 *
 *  @retval
 *      Not Applicable
 */
void Osal_cppiEndMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

#ifdef L2_CACHE
    /* Writeback L2 cache. This should Writeback L1D as well.
     * Wait until operation is complete. */
    CACHE_wbL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Writeback L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_wbL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
void *Osal_qmssMalloc(uint32_t num_bytes)
{
    Error_Block errorBlock;

    /* Increment the allocation counter. */
    qmssMallocCounter++;

    /* Allocate memory. */
    return(Memory_alloc(NULL, num_bytes, 0, &errorBlock));
}

/**
 *  @b Description
 *  @n
 *      The function is used to free a memory block of the specified size.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *
 *  @param[in]  size
 *      Size of the memory block to be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssFree(void *ptr, uint32_t size)
{
    /* Increment the free counter. */
    qmssFreeCounter++;
    Memory_free(NULL, ptr, size);
}

/**
 *  @b Description
 *  @n
 *      The function is used to enter a critical section.
 *      Function protects against
 *
 *      access from multiple cores
 *      and
 *      access from multiple threads on single core
 *
 *  @retval
 *      Handle used to lock critical section
 */
void *Osal_qmssCsEnter(void)
{
    while ((CSL_semAcquireDirect (QMSS_HW_SEM)) == 0);
    return(NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is used to exit a critical section
 *      protected using Osal_qmssCsEnter() API.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssCsExit(void *CsHandle)
{
    CSL_semReleaseSemaphore(QMSS_HW_SEM);
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to enter a critical section.
 *      Function protects against
 *
 *      access from multiple cores
 *      and
 *      access from multiple threads on single core
 *
 *  @retval
 *      Handle used to lock critical section
 */
void *Osal_qmssAccCsEnter(void)
{
    /* Get the hardware semaphore */
    while ((CSL_semAcquireDirect(QMSS_ACC_HW_SEM)) == 0);

    /* Create Semaphore for protection against access from multiple threads
     * Not created here becasue application is not multithreaded */
    return(NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is used to exit a critical section
 *      protected using Osal_qmssAccCsEnter() API.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssAccCsExit(void *CsHandle)
{
    /* Release Semaphore using handle */

    /* Release the hardware semaphore */
    CSL_semReleaseSemaphore(QMSS_ACC_HW_SEM);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to enter a critical section.
 *      Function protects against
 *      access from multiple threads on single core
 *
 *  @retval
 *      Handle used to lock critical section
 */
void *Osal_qmssMtCsEnter(void)
{
    /* Create Semaphore for protection against access from multiple threads
     * Not created here becasue application is not multithreaded */
    return(NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is used to exit a critical section
 *      protected using Osal_qmssMtCsEnter() API.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssMtCsExit(void *CsHandle)
{
    /* Release Semaphore using handle */
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is the QMSS OSAL Logging API which logs
 *      the messages on the console.
 *
 *  @param[in]  fmt
 *      Formatted String.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssLog(char *fmt, ... )
{
}

/**
 *  @b Description
 *  @n
 *      The function is used to indicate that a block of memory is
 *      about to be accessed. If the memory block is cached then this
 *      indicates that the application would need to ensure that the
 *      cache is updated with the data from the actual memory.
 *
 *  @param[in]  ptr
 *       Address of memory block
 *
 *  @param[in]  size
 *       Size of memory block
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssBeginMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

#ifdef L2_CACHE
    /* Invalidate L2 cache. This should invalidate L1D as well.
     * Wait until operation is complete. */
    CACHE_invL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Invalidate L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_invL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to indicate that the block of memory has
 *      finished being accessed. If the memory block is cached then the
 *      application would need to ensure that the contents of the cache
 *      are updated immediately to the actual memory.
 *
 *  @param[in]  ptr
 *       Address of memory block
 *
 *  @param[in]  size
 *       Size of memory block
 *
 *  @retval
 *      Not Applicable
 */
void Osal_qmssEndMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

#ifdef L2_CACHE
    /* Writeback L2 cache. This should Writeback L1D as well.
     * Wait until operation is complete. */
    CACHE_wbL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Writeback L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_wbL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
void *Osal_rmMalloc(uint32_t num_bytes)
{
    Error_Block errorBlock;

    /* Increment the allocation counter. */
    rmMallocCounter++;

    /* Allocate memory. */
    return(Memory_alloc(NULL, num_bytes, 0, &errorBlock));
}

/**
 *  @b Description
 *  @n
 *      The function is used to free a memory block of the specified size.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *
 *  @param[in]  size
 *      Size of the memory block to be cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_rmFree(void *ptr, uint32_t size)
{
    /* Increment the free counter. */
    rmFreeCounter++;
    Memory_free(NULL, ptr, size);
}

/* FUNCTION PURPOSE: Critical section enter
 ***********************************************************************
 * DESCRIPTION: The function is used to enter a critical section.
 *              Function protects against
 *
 *              access from multiple cores
 *              and
 *              access from multiple threads on single core
 */  
void *Osal_rmCsEnter(void)
{
    return NULL;
}

/* FUNCTION PURPOSE: Critical section exit
 ***********************************************************************
 * DESCRIPTION: The function is used to exit a critical section
 *              protected using Osal_cppiCsEnter() API.
 */
void Osal_rmCsExit(void *CsHandle)
{

}

/* FUNCTION PURPOSE: Multi-threaded critical section enter
 ***********************************************************************
 * DESCRIPTION: The function is used to enter a multi-threaded critical
 *              section. Function protects against 
 *
 *              access from multiple threads on single core
 */
void *Osal_rmMtCsEnter(void *mtSemObj)
{

    return(NULL);
}

/* FUNCTION PURPOSE: Multi-threaded critical section exit
 ***********************************************************************
 * DESCRIPTION: The function is used to exit a multi-threaded critical
 *              section protected using Osal_rmMtCsEnter() API.
 */
void Osal_rmMtCsExit(void *mtSemObj, void *CsHandle)
{

}

/* FUNCTION PURPOSE: Critical section exit
 ***********************************************************************
 * DESCRIPTION: The function is used to indicate that a block of memory is
 *              about to be accessed. If the memory block is cached then this
 *              indicates that the application would need to ensure that the
 *              cache is updated with the data from the actual memory.
 */  
void Osal_rmBeginMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

#ifdef L2_CACHE
    /* Invalidate L2 cache. This should invalidate L1D as well.
     * Wait until operation is complete. */
    CACHE_invL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Invalidate L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_invL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/* FUNCTION PURPOSE: Critical section exit
 ***********************************************************************
 * DESCRIPTION: The function is used to indicate that the block of memory has
 *              finished being accessed. If the memory block is cached then the
 *              application would need to ensure that the contents of the cache
 *              are updated immediately to the actual memory.
 */
void Osal_rmEndMemAccess(void *ptr, uint32_t size)
{
    uint32_t key;

    /* Disable Interrupts */
    key = Hwi_disable();

#ifdef L2_CACHE
    /* Writeback L2 cache. This should Writeback L1D as well.
     * Wait until operation is complete. */ 
    CACHE_wbL2(ptr, size, CACHE_FENCE_WAIT);
#else
    /* Writeback L1D cache and wait until operation is complete.
     * Use this approach if L2 cache is not enabled */
    CACHE_wbL1d(ptr, size, CACHE_FENCE_WAIT);
#endif

    /* Reenable Interrupts. */
    Hwi_restore(key);

    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to create a task blocking object
 *      capable of blocking the task a RM instance is running
 *      within
 *
 *  @retval
 *      Allocated task blocking object
 */ 
void *Osal_rmTaskBlockCreate(void)
{
    Semaphore_Params semParams;

    Semaphore_Params_init(&semParams);
    return((void *)Semaphore_create(0, &semParams, NULL));
}

/**
 *  @b Description
 *  @n
 *      The function is used to block a task whose context a
 *      RM instance is running within.
 *
 *  @param[in]  handle
 *      Task blocking object handle.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_rmTaskBlock(void *handle)
{
    Semaphore_pend((Semaphore_Handle)handle, BIOS_WAIT_FOREVER);
}

/**
 *  @b Description
 *  @n
 *      The function is used to unblock a task whose context a
 *      RM instance is running within.
 *
 *  @param[in]  handle
 *      Task blocking object handle.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_rmTaskUnblock(void *handle)
{
    Semaphore_post((Semaphore_Handle)handle);
}

/**
 *  @b Description
 *  @n
 *      The function is used to delete a task blocking object
 *      provided to a RM instance
 *
 *  @param[in]  handle
 *      Task blocking object handle.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_rmTaskBlockDelete(void *handle)
{
    Semaphore_delete((Semaphore_Handle *)&handle);
}

/**
 *  @b Description
 *  @n
 *      The function is the RM OSAL Logging API which logs
 *      the messages on the console.
 *
 *  @param[in]  fmt
 *      Formatted String.
 *
 *  @retval
 *      Not Applicable
 */
void Osal_rmLog(char *fmt, ...)
{
    VaList ap;

    va_start(ap, fmt);
    System_vprintf(fmt, ap);
    va_end(ap);
}
