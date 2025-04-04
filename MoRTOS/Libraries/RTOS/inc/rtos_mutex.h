/**
 * @file rtos_mutex.h
 * @brief Header file for RTOS mutex management.
 *
 * This file contains the definitions, macros, and function prototypes
 * required for managing mutexes in the RTOS.
 *
 * @author Mohamed HossamElDin
 * @date 3 April 2025
 */

/**
 * @defgroup RTOS_Mutex RTOS Mutex Management
 * @brief Group for RTOS mutex-related definitions and functions.
 * @{
 */

#ifndef RTOS_MUTEX_H
#define RTOS_MUTEX_H

// Includes
#include "rtos_list.h"
#include <stdint.h>

/**
 * @defgroup RTOS_Mutex_exported_Defines Defines
 * @brief Exported Defines used in RTOS mutex management.
 * @{
 */

/** @} */ // End of RTOS_Mutex_exported_Defines group

/**
 * @defgroup RTOS_Mutex_exported_Macros Macros
 * @brief Macros used in RTOS mutex management.
 * @{
 */

/** @} */ // End of RTOS_Mutex_Macros group

/**
 * @defgroup RTOS_Mutex_exported_Constants Constants
 * @brief Constants used in RTOS mutex management.
 * @{
 */

/** @} */ // End of RTOS_Mutex_exported_Constants group

/**
 * @defgroup RTOS_Mutex_exported_Typedefs Typedefs
 * @brief Typedefs used in RTOS mutex management.
 * @{
 */
typedef struct {
  uint32_t value;          /*The mutex value*/
  rtos_list_t waitinglist; /*The waiting list for this mutex */
} rtos_mutex_t;

/** @} */ // End of RTOS_Mutex_exported_Typedefs group

/**
 * @defgroup RTOS_Mutex_exported_Variables extern Variables
 * @brief Extern Variables used in RTOS mutex management.
 * @{
 */

/** @} */ // End of RTOS_Mutex_exported_Variables group

/**
 * @defgroup RTOS_Mutex_exported_Functions Function Prototypes
 * @brief Function prototypes for RTOS mutex management.
 * @{
 */
void rtos_svc_mutexCreate(rtos_mutex_t *pMutex, uint32_t mutexinitval);
void rtos_mutexCreate(rtos_mutex_t *pMutex, uint32_t mutexinitval);
uint32_t rtos_svc_mutexLock(rtos_mutex_t *pMutex, uint32_t waitstatus);
uint32_t rtos_mutexLock(rtos_mutex_t *pMutex, uint32_t waitstatus);
/** @} */ // End of RTOS_Mutex_exported_Functions group

#endif // RTOS_MUTEX_H

/** @} */ // End of RTOS_Mutex group
