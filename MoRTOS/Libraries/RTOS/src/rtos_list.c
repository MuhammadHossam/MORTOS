/**
 * @file rtos_list.c
 * @brief Implementation of RTOS list utilities.
 * 
 * @author [Your Name]
 * @date [Date]
 */

// -----------------------------------------------------------------------------
// Includes
#include "rtos_list.h"
#include <stddef.h>
// -----------------------------------------------------------------------------
// Private Typedefs
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Typedefs Private Typedefs
 * @brief Typedefs used internally in RTOS list implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Defines
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Defines Private Defines
 * @brief Macro definitions used internally in RTOS list implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Macros
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Macros Private Macros
 * @brief Macros used internally in RTOS list implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Constants
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Constants Private Constants
 * @brief Constants used internally in RTOS list implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Variables
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Variables Private Variables
 * @brief Variables used internally in RTOS list implementation.
 * @{
 */
/** @} */

// -----------------------------------------------------------------------------
// Private Functions
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Private_Functions Private Functions
 * @brief Static Functions used internally in RTOS list implementation.
 * @{
 */
/** @} */


// -----------------------------------------------------------------------------
// Function Implementations
// -----------------------------------------------------------------------------
/**
 * @defgroup RTOS_List_Implementations RTOS List Function Implementations
 * @brief Implementations of RTOS list functions.
 * @{
 */

 void rtos_listInit(rtos_list_t *pList) {
    pList->numofItems = 0; /* Initialize the number of items to 0 */
    pList->pHead = (rtos_listItem_t *) &pList->end; /* Initialize the head of the list to the end */
    pList->end.pNext = (rtos_listItem_t *) &pList->end; /* Initialize the next pointer of the end to the end */
    pList->end.pPrev = (rtos_listItem_t *) &pList->end; /* Initialize the previous pointer of the end to the end */
}


void rtos_listInsert(rtos_list_t *pList, rtos_listItem_t *pNewItem) {
   pNewItem->pNext = pList->pHead->pNext; /* Set the next pointer of the new item to the head of the list */
   pNewItem->pPrev = pList->pHead; /* Set the previous pointer of the new item to the head of the list */
   pList->pHead->pNext->pPrev = pNewItem; /* Set the previous pointer of the End of the list to the new item */
   pList->pHead->pNext = pNewItem; /* Set the next pointer of the head of the list to the new item */
   pList->pHead = pNewItem; /* Set the head of the list to the new item */
   pNewItem->pList = (void*)pList; /* Set the list pointer of the new item to the list */
   pList->numofItems++; /* Increment the number of items in the list */
}

void rtos_listRemove(rtos_listItem_t *pRemovedItem) {
    pRemovedItem->pNext->pPrev = pRemovedItem->pPrev; /* Set the previous pointer of the next item to the previous item */
    pRemovedItem->pPrev->pNext = pRemovedItem->pNext; /*Point the next of the removed item to the previous of the removed item*/
    ((rtos_list_t *)pRemovedItem->pList)->numofItems--; /* Decrement the number of items in the list */
    if(((rtos_list_t *)pRemovedItem->pList)->pHead == pRemovedItem) { /* If the removed item is the head of the list */
        ((rtos_list_t *)pRemovedItem->pList)->pHead = pRemovedItem->pPrev; /* Set the head of the list to the previous item */
    }
    else{
        /* Do nothing */
    }
    pRemovedItem->pList = NULL; /* Set the list pointer of the removed item to NULL */
    pRemovedItem->pNext = NULL; /* Set the next pointer of the removed item to NULL */
    pRemovedItem->pPrev = NULL; /* Set the previous pointer of the removed item to NULL */
}
/** @} */
