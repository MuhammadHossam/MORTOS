/**
 * @file rtos_list.h
 * @brief Header file for RTOS list management.
 *
 * This file contains the definitions, macros, and function prototypes
 * required for managing lists in the RTOS.
 *
 * @author Mohamed HossamElDin
 * @date 19 March 2025
 */

/**
 * @defgroup RTOS_List RTOS List Management
 * @brief Group for RTOS list-related definitions and functions.
 * @{
 */

#ifndef RTOS_LIST_H
#define RTOS_LIST_H

// Includes
#include <stdint.h>

/**
 * @defgroup RTOS_List_exported_Defines Defines
 * @brief Exported Defines used in RTOS list management.
 * @{
 */

/** @} */ // End of RTOS_List_exported_Defines group

/**
 * @defgroup RTOS_List_exported_Macros Macros
 * @brief Macros used in RTOS list management.
 * @{
 */

/** @} */ // End of RTOS_List_Macros group

/**
 * @defgroup RTOS_List_exported_Constants Constants
 * @brief Constants used in RTOS list management.
 * @{
 */

/** @} */ // End of RTOS_List_exported_Constants group

/**
 * @defgroup RTOS_List_exported_Typedefs Typedefs
 * @brief Typedefs used in RTOS list management.
 * @{
 */

/**
 * @brief Structure representing a list item.
 */
struct listItem_t {
  struct listItem_t *pNext; /**< Pointer to the next list item. */
  struct listItem_t *pPrev; /**< Pointer to the previous list item. */
  void *pThread; /**< Pointer to the thread associated with the list item. */
  void *pList;   /**< Pointer to the list containing the list item. */
};

typedef struct listItem_t rtos_listItem_t;

/**
 * @brief Structure representing the end of a list.
 */
typedef struct {
  rtos_listItem_t *pNext; /**< Pointer to the next list item. */
  rtos_listItem_t *pPrev; /**< Pointer to the previous list item. */
} rtos_listEnd_t;

/**
 * @brief Structure representing a list.
 */
typedef struct {
  uint32_t numofItems;    /**< Number of items in the list. */
  rtos_listEnd_t end;     /**< End of the list. */
  rtos_listItem_t *pHead; /**< Pointer to the head of the list. */
} rtos_list_t;
/** @} */ // End of RTOS_List_exported_Typedefs group

/**
 * @defgroup RTOS_List_exported_Variables extern Variables
 * @brief Extern Variables used in RTOS list management.
 * @{
 */

/** @} */ // End of RTOS_List_exported_Variables group

/**
 * @defgroup RTOS_List_exported_Functions Function Prototypes
 * @brief Function prototypes for RTOS list management.
 * @{
 */
void rtos_listInit(rtos_list_t *pList);
void rtos_listInsert(rtos_list_t *pList, rtos_listItem_t *pNewItem);
void rtos_listRemove(rtos_listItem_t *pRemovedItem);
/** @} */ // End of RTOS_List_exported_Functions group

#endif // RTOS_LIST_H

/** @} */ // End of RTOS_List group
