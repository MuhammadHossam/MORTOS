/**
 * @file rtos_thread.h
 * @brief Thread management Implementation for the RTOS.
 *
 * This file contains definitions for thread-related operations
 * such as creation, deletion, and management of threads in the RTOS.
 *
 * @note This file is part of the RTOS module.
 *
 * @date 19 March 2025
 */

/**
 * @defgroup RTOS_Thread RTOS Thread Management
 * @brief Functions and definitions for managing threads in the RTOS.
 * @{
 */



 // Includes
#include "stm32f4xx.h"
#include "rtos_thread.h"
#include "rtos_cfg.h"
#include "rtos_list.h"
#include "rtos.h"
// -----------------------------------------------------------------------------
// Private Typedefs
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Typedefs Private Typedefs
 * @brief Typedefs used internally in RTOS Thread implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Defines
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Defines Private Defines
 * @brief Macro definitions used internally in RTOS Thread implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Macros
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Macros Private Macros
 * @brief Macros used internally in RTOS Thread implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Constants
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Constants Private Constants
 * @brief Constants used internally in RTOS Thread implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Variables
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Variables Private Variables
 * @brief Variables used internally in RTOS Thread implementation.
 * @{
 */

static rtos_list_t readylist[THREAD_PRIORITY_LEVELS]; /**< Array of ready lists. */
static uint32_t currentTopPriority = (uint32_t)(THREAD_PRIORITY_LEVELS - 1u); /**< Current top priority. */
rtos_thread_t *pRunningThread; /**< Pointer to the currently running thread. */
static uint32_t RunningThreadId = 0u; /**< Running thread Id */
static uint32_t numOfThreads = 0u; /**< Total number of created threads */
/** @} */


// -----------------------------------------------------------------------------
// Exported Variables
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Exported_Variables Exported Variables
 * @brief Variables can be externed for external usage.
 * @{
 */


// -----------------------------------------------------------------------------
// Private Functions
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Private_Functions Private Functions
 * @brief Static Functions used internally in RTOS Thread implementation.
 * @{
 */
/** @} */


// -----------------------------------------------------------------------------
// Function Implementations
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Thread_Implementations RTOS Thread Function Implementations
 * @brief Implementations of RTOS Thread functions.
 * @{
 */

 
/**
 * @brief Initializes the ready lists for all thread priority levels.
 *
 * This function iterates through each priority level and initializes
 * the corresponding ready list using the rtos_listInit function.
 * It sets up the infrastructure for managing threads based on their
 * priority levels within the RTOS.
 */

void rtos_threadListsInit(void) {
  uint32_t i;

  for (i = 0; i < THREAD_PRIORITY_LEVELS; i++) {
    rtos_listInit(&readylist[i]);
  }
}

/**
 * @brief Creates a new thread and prepares it for execution.
 *
 * This function initializes a thread with the given stack, priority, and entry function.
 * It sets up the stack frame for the thread, including program status register (xPSR),
 * program counter, and control register. The thread is then inserted into the ready list
 * based on its priority. If the new thread has a higher priority than the currently running 
 * thread, a context switch is triggered.
 *
 * @param pthread Pointer to the thread structure to be initialized.
 * @param pstack Pointer to the stack structure for the thread.
 * @param priority Priority level assigned to the thread.
 * @param pfunc Function pointer to the thread's entry function.
 */

void rtos_threadCreate(rtos_thread_t * pthread, rtos_stack_t * pstack, uint32_t priority, void (*pfunc)(void)) {
    ASSERT(pthread != NULL); // Check if the thread pointer is not NULL
    ASSERT(pstack != NULL); // Check if the stack pointer is not NULL
    ASSERT(pfunc != NULL); // Check if the function pointer is not NULL
    ASSERT(priority < THREAD_PRIORITY_LEVELS); // Check if the priority is within the valid range

    pthread->pStack = (uint32_t)pstack + ( (THREAD_STACK_SIZE) * 8u) - (THREAD_STACK_FRAME * 4); // Set the thread's stack pointer  
    /*Write initial xPSR, program status register, Set T-bit (Bit #24) for Thumb instruction*/
    MEM32_ADDRESS(pthread->pStack + (17 << 2)) = 0x01000000; 
    MEM32_ADDRESS(pthread->pStack + (16 << 2)) = (uint32_t)pfunc; /*Initialize the program counter with the function start address*/
    /*Initialize the thread Exception return EXC_RETURN
        0xFFFFFFFD --> Return to thread mode, use PSP.*/
    MEM32_ADDRESS(pthread->pStack) = 0xFFFFFFFDUL;

    /*Initialize the control register value to unprivilege mode, using PSP, No FPU*/
    MEM32_ADDRESS(pthread->pStack + (1 << 2)) = 0x03;
    pthread->priority = priority; // Set the thread's priority
    /*Thread isn't linked to any list yet*/
    pthread->item.pList = NULL;

    /*Link the item thread with the created thread.*/
    pthread->item.pThread =(void*) pthread;

    /*Increment the total number of threads and assign it to the thread id indicating the creation order*/
    pthread->threadId = ++numOfThreads; 

    /*Initialize the item priority with the thread priority*/
    pthread->item.itemPriority = priority;

    rtos_addThreadToReadyList(pthread); // Add the thread to the ready list 
}


/**
 * @brief Retrieves the next thread to be executed based on the highest priority.
 *
 * This function returns a pointer to the thread control block of the next
 * thread that should be executed. It selects the thread from the ready list
 * that corresponds to the current highest priority level.
 *
 * @return Pointer to the thread control block of the next scheduled thread.
 */

rtos_thread_t * rtos_threadGetNext(void) {
    return (rtos_thread_t *)readylist[currentTopPriority].pHead->pThread;
}


/**
 * @brief Adds a thread to the ready list.
 *
 * This function adds a created thread to the ready list based on its priority.
 * If the added thread has a higher priority than the current running thread, a
 * context switch is triggered by setting the PendSV exception.
 *
 * @param pthread Pointer to the thread structure to be added.
 */
void rtos_addThreadToReadyList(rtos_thread_t * pthread)
{
    ASSERT(pthread != NULL);
    rtos_listInsert(&readylist[pthread->priority], &pthread->item); // Insert the thread into the ready list
    if(pthread->priority < currentTopPriority) {
        currentTopPriority = pthread->priority; // Update the current top priority
    }

    if((pRunningThread != NULL) && ( pthread->priority < pRunningThread->priority)) {
        /*If the created thread has higher priority than the running thread, perform a context switch*/
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; // Set the PendSV exception
    }
    else
    {
        /*Context switching isn't needed*/
    }
}


/**
 * @brief Switches to the next thread in the ready list.
 *
 * This function retrieves the head of the highest priority ready list and
 * assigns it to the running thread. It then assigns the highest priority
 * thread id to the current running thread id.
 */
void rtos_threadSwitchingRunning(void){

    /*Get the highest priority list*/
    rtos_list_t * pReadylist = &readylist[currentTopPriority];

    /*Move the head to the next list item since always
        head is pointing to the last added list item 
        and we need to point to the first added one in the list*/
    pReadylist->pHead = pReadylist->pHead->pNext;
    if(pReadylist->pHead == (rtos_listItem_t*)&pReadylist->end)
    {
        /*Points to the first added thread in the list.*/
        pReadylist->pHead = pReadylist->pHead->pNext;
    }

    /*Get the running thread with the highest current priority*/
    pRunningThread = (rtos_thread_t *)pReadylist->pHead->pThread;

    /*Assign the highest priority thread id to the current running thread id*/
    RunningThreadId = pRunningThread->threadId;
}


/**
 * @brief Retrieves the currently running thread.
 *
 * This function returns a pointer to the currently running thread control block.
 *
 * @return Pointer to the currently running thread control block.
 */
rtos_thread_t * rtos_RunningThreadGet(void){
    return (rtos_thread_t*)pRunningThread;
}
 /** @} */
