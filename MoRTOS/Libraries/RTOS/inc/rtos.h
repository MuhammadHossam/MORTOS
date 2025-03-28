/**
 * @file rtos_list.h
 * @brief Header file for RTOS.
 *
 * This file contains the definitions, macros, and function prototypes
 * required for the RTOS core/kernel functionality.
 *
 * @author Mohamed HossamElDin
 * @date 19 March 2025
 */

/**
 * @defgroup RTOS RTOS Kernel
 * @brief Group for RTOS Kernel and core functionality
 * @{
 */

#ifndef RTOS_H
#define RTOS_H

// Includes
#include <stdint.h>

/**
 * @defgroup RTOS_exported_Defines Defines
 * @brief Exported Defines used in RTOS core.
 * @{
 */

/** @} */ // End of RTOS_exported_Defines group

/**
 * @defgroup RTOS_exported_Macros Macros
 * @brief Macros used in RTOS core.
 * @{
 */
#define MEM32_ADDRESS(ADDRESS) (*((volatile uint32_t *)(ADDRESS)))
/** @} */ // End of RTOS_Macros group

/**
 * @defgroup RTOS_exported_Constants Constants
 * @brief Constants used in RTOS core.
 * @{
 */

/** @} */ // End of RTOS__exported_Constants group

/**
 * @defgroup RTOS__exported_Typedefs Typedefs
 * @brief Typedefs used in RTOS core.
 * @{
 */

/**
 * @brief Structure representing a list.
 */

/** @} */ // End of RTOS_exported_Typedefs group

/**
 * @defgroup RTOS_exported_Variables extern Variables
 * @brief Extern Variables used in RTOS core.
 * @{
 */

/** @} */ // End of RTOS_exported_Variables group

/**
 * @defgroup RTOS_exported_Functions Function Prototypes
 * @brief Function prototypes for RTOS core.
 * @{
 */
void rtos_init(void);
void rtos_svc_handler_main(uint32_t *svc_args);
void rtos_svc_schedulerStart(void);
void rtos_start_scheduler(void);
/** @} */ // End of RTOS_exported_Functions group

#endif // RTOS_LIST_H

/** @} */ // End of RTOS group
