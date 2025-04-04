/**
 * @file rtos_mutex.c
 * @brief Implementation of RTOS mutex utilities.
 * 
 * @author Mohamed HossamElDin
 * @date 20 March 2025
 */

// -----------------------------------------------------------------------------
// Includes
#include "rtos_cfg.h"
#include "rtos_mutex.h"
#include "rtos_thread.h"
#include "stm32f4xx.h"

// -----------------------------------------------------------------------------
// Private Typedefs
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Typedefs Private Typedefs
 * @brief Typedefs used internally in RTOS mutex implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Defines
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Defines Private Defines
 * @brief Macro definitions used internally in RTOS mutex implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Macros
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Macros Private Macros
 * @brief Macros used internally in RTOS mutex implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Constants
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Constants Private Constants
 * @brief Constants used internally in RTOS mutex implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Variables
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Variables Private Variables
 * @brief Variables used internally in RTOS mutex implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Functions
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Private_Functions Private Functions
 * @brief Static Functions used internally in RTOS mutex implementation.
 * @{
 */
/** @} */


// -----------------------------------------------------------------------------
// Function Implementations
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_Mutex_Implementations RTOS Mutex Function Implementations
 * @brief Implementations of RTOS mutex functions.
 * @{
 */

/**
 * @brief Creates and initializes a mutex.
 *
 * This function initializes a mutex object with the specified initial 
 * value and prepares its waiting list. The mutex can be created with 
 * an initial value of 0 (unlocked) or 1 (locked). The waiting list is 
 * also initialized for managing threads waiting on the mutex.
 *
 * @param pMutex Pointer to the mutex object to be initialized.
 * @param mutexinitval Initial value of the mutex, must be 0 or 1.
 *
 * @pre The pMutex pointer must not be NULL.
 * @post The mutex is initialized with the specified value and its waiting 
 * list is ready for use.
 */

void rtos_mutexCreate(rtos_mutex_t *pMutex, uint32_t mutexinitval){
    
    /*Ensure that pMutex isn't pointing to a null mutex structure*/
    ASSERT(pMutex != NULL); 

    /*Ensure that mutex initial value whether 0 or 1 */
    ASSERT( (mutexinitval == 0u) || (mutexinitval == 1u));

    /*Assign the mutex initial value*/
    pMutex->value = mutexinitval;

    /*Initialize the mutex waiting list*/
    rtos_listInit((rtos_list_t *)&pMutex->waitinglist);


}


uint32_t rtos_mutexLock(rtos_mutex_t *pMutex, uint32_t waitstatus)
{
    ASSERT(pMutex != NULL);
    
    ASSERT((waitstatus == 0) || (waitstatus == 1));
    /*lock terminate used to terminate from the 
     *mutex locking retries if one of the following is achieved:
     * 1. Successfull access for the mutex
     *2. Mutex is aleady acquired by another thread
     */
    uint32_t lockterminate = 0; 

    /*The return status has the following values:
        1. returnstatus = 0 -> if the mutex is already acquired by another threadand no wait is needed
        2. returnstatus = 1 -> if the mutex is acquired by this task.
        2. returnstatus = 2 -> if mutex is already acquired by another thread but wait is needed*/
    uint32_t returnstatus = 0;

    /*Pointer to the current running thread*/
    rtos_thread_t* pRunningthread = rtos_RunningThreadGet();

    while(!lockterminate)
    {
        /*Try to lock the mutex using exclusive memory access
            * if The Mutex == 1 --> Mutex is free
            * if the Mutex == 0 --> Mutex is already acquired by other thread */
        if(1u == __LDREXW(&pMutex->value))
        {
            /* The mutex is free, try to lock it by clearing the mutex value
                * 1. if the exclusive access return equals 0 means successful store
                * under the exclusive monitor supervision
                * 2. if the exclusive accesss return equals 1 means unsuccessful store
                * and another task/exception tried to access this memory before the store
                * action*/
            if(0u == __STREXW(0, &pMutex->value))
            {
                lockterminate = 1u;
                returnstatus = 1u;
            }

        }
        else
        {
            lockterminate = 1u;
        }
    
    }

    /*Mutex locking retry is needed till successful acquire*/
    if( (returnstatus != 1) && (waitstatus == 1))
    {
        /*Push the current running thread to the mutex waiting list*/
        rtos_SortedlistInsert((rtos_list_t *)&pMutex->waitinglist, (rtos_listItem_t *)pRunningthread);

        /*Immediate context switching should be triggered after return from the SVC*/
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; // Set the PendSV exception
        
        /*The thread should waits for the mutex and to be pushed onto this mutex waiting list*/
        returnstatus = 2; /*The svc main handler has to re-call the lock again for contiuous acquire retries*/

    }
    return returnstatus;
}

/** @} */
