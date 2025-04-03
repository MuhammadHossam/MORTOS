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

/** @} */
