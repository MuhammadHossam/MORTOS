/**
 * @file rtos_thread.h
 * @brief Thread management interface for the RTOS.
 *
 * This file contains declarations for thread-related operations
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

#ifndef RTOS_THREAD_H
#define RTOS_THREAD_H

// Includes
#include "rtos_cfg.h"
#include "rtos_list.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup RTOS_Thread_ExportedDefines Exported Defines
 * @brief Exported defines for thread management.
 * @{
 */

/** @} */ // End of RTOS_Thread_ExportedDefines group

/**
 * @defgroup RTOS_Thread_ExportedConstants Exported Constants
 * @brief Exported constants for thread management.
 * @{
 */
// Add exported constants here.
/** @} */ // End of RTOS_Thread_ExportedConstants group

/**
 * @defgroup RTOS_Thread_ExportedVariables Exported Variables
 * @brief Exported variables for thread management.
 * @{
 */
// Add exported variables here.
/** @} */ // End of RTOS_Thread_ExportedVariables group

/**
 * @defgroup RTOS_Thread_Macros Thread Macros
 * @brief Macros used for thread management.
 * @{
 */

/** @} */ // End of RTOS_Thread_Macros group

/**
 * @defgroup RTOS_Thread_Typedefs Thread Type Definitions
 * @brief Type definitions used for thread management.
 * @{
 */

/** Thread structure. */
typedef struct thread_t {
  uint32_t pStack;      /**< Pointer to the thread's stack. */
  uint32_t priority;    /**< Thread priority. */
  rtos_listItem_t item; /**< List item for the thread. */
} rtos_thread_t;

typedef struct {
  uint64_t stack[THREAD_STACK_SIZE]; /**< Thread stack. */
} rtos_stack_t;
/** @} */ // End of RTOS_Thread_Types group

/**
 * @defgroup RTOS_Thread_Functions  Thread Function Prototypes
 * @brief Function declarations for thread management.
 * @{
 */
void rtos_threadCreate(rtos_thread_t * pthread, rtos_stack_t * pstack, uint32_t priority, void (*pfunc)(void));
rtos_thread_t * rtos_threadGetNext(void);
/** @} */ // End of RTOS_Thread_Functions group

#ifdef __cplusplus
}
#endif

#endif // RTOS_THREAD_H

/** @} */ // End of RTOS_Thread group
