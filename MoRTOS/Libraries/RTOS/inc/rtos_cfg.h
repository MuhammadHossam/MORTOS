/**
 * @file rtos_cfg.h
 * @brief Configuration file for the MoRTOS Real-Time Operating System.
 *
 * This file contains configuration macros and settings for the RTOS.
 * Modify these settings as per your application requirements.
 *
 * @author Mohamed HossamElDin
 * @date 19 March 2025
 *
 * @addtogroup RTOS_Configuration
 * @{
 */

#ifndef RTOS_CFG_H
#define RTOS_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "cmsis_gcc.h"

/**
 * @defgroup RTOS_Configuration_exported_defines
 * @{
 */

/** @brief The system clock frequency in Hz. */
#define SYSTEM_CORE_CLOCK_HZ ((uint32_t)16000000u)

/** @brief The SysTick timer rate in Hz. */
#define SYSTEM_TICK_RATE_HZ ((uint32_t)1000u)

/** @brief The number of priority levels supported by the RTOS. */
#define THREAD_PRIORITY_LEVELS ((uint32_t)16u)

/** @brief The size of the stack for each thread in double words (1024 =
 * 8kbytes)
 * @note The stack size must be a multiple of 8 bytes to avoid alignment issues
 * and it is recommended for fast context switching.
 */
#define THREAD_STACK_SIZE ((uint32_t)1024u)
/* 18 registers in the stack frame 
    (R0 -> R15 not including R13(SP), xPSR), Control Register, and EXC Return*/
#define THREAD_STACK_FRAME ((uint32_t)18u) 

/** @brief RTOS commands */
#define RTOS_START_SCHEDULER   0x00  /**< Start the RTOS scheduler */
#define RTOS_CREATE_TASK       0x01  /**< Create a new task */
#define RTOS_MUTEX_CREATE      0x02  /**< Create a new mutex */
#define RTOS_MUTEX_LOCK        0x03  /**< Lock a mutex */
/**
 * @}
 */

/**
 * @defgroup RTOS_Configuration_exported_macros
 * @{
 */
#define ASSERT(x)                                                              \
  if ((x) == 0) {                                                              \
    __disable_irq();                                                           \
    while (1)                                                                  \
      ;                                                                        \
  }
/**
 * @}
 */

/**
 * @defgroup RTOS_Configuration_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup RTOS_Configuration_exported_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup RTOS_Configuration_exported_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup RTOS_Configuration_exported_functions
 * @{
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // RTOS_CFG_H

/**
 * @}
 */
