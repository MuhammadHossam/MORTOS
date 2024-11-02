/**
 * @file rtos_config.h
 * @brief Real-Time Operating System (RTOS) configuration header file.
 *
 * This file contains configuration options, type definitions, and function
 * prototypes for the RTOS.
 *
 * @author [Mohamed HossamElDen Mohamed Soliman]
 * @date [13th November 2024]
 */

#ifndef RTOS_CONFIG_H
#define RTOS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup rtos_config RTOS Configuration
 * @{
 */

/**
 * @defgroup rtos_config_exported_typedefs RTOS Exported Typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_defines RTOS Configuration Defines
 * @{
 */

/**
 * @brief The stack size of the thread
 */
#define THREAD_STACK_SIZE ((uint32_t)1024u)

/**
 *  @brief The number of priority levels
 */
#define THREAD_PRIORITY_LEVELS ((uint32_t)16u)

/**
 * @brief The system clock frequency
 */
#define SYSTEM_CORE_CLOCK_HZ ((uint32_t)16000000u)

/**
 * @brief The system tick rate
 */
#define SYSTEM_TICK_RATE_HZ ((uint32_t)1000u)
/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_constants RTOS Configuration Constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_macros RTOS Configuration Macros
 * @{
 */

/**
 * @brief Macro to disable interrupts
 * @details Macro to disable interrupts
 */
#define ASSERT(x)                                                              \
  if ((x) == 0) {                                                              \
    __disable_irq();                                                           \
    while (1) {                                                                \
    };                                                                         \
  }
/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_structs RTOS Configuration Structs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_functions RTOS Configuration Functions
 * @{
 */

/**
 * @}
 * /

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
/* End of header file */
#endif /* RTOS_CONFIG_H */