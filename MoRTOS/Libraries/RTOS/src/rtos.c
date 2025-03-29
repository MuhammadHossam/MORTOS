/**
 * @file rtos.c
 * @brief Implementation of the Real-Time Operating System (RTOS) core functionalities.
 * 
 * This file contains the core logic and functions for the RTOS, including task management,
 * scheduling, and inter-task communication.
 * 
 * @author Mohamed HossamElDin
 * @date 26 March 2025
 */

/** @defgroup RTOS_Core RTOS Core
 *  @brief Core functionalities of the RTOS.
 *  @{
 */

/** @defgroup RTOS_Includes Includes
 *  @brief Header files included in the RTOS implementation.
 *  @{
 */

 #include "rtos.h"
 #include "rtos_thread.h"
 #include "rtos_cfg.h"
 #include "stm32f446xx.h"
/** @} */ // End of RTOS_Includes

/** @defgroup RTOS_Typedefs Typedefs
 *  @brief Typedefs used in the RTOS.
 *  @{
 */

/** @} */ // End of RTOS_Typedefs

/** @defgroup RTOS_Private_Macros Private Macros
 *  @brief Private macros used internally by the RTOS.
 *  @{
 */

 /** @} */ // End of RTOS_Private_Macros

/** @defgroup RTOS_Private_Constants Private Constants
 *  @brief Private constants used internally by the RTOS.
 *  @{
 */

 /** @} */ // End of RTOS_Private_Constants

/** @defgroup RTOS_Private_Variables Private Variables
 *  @brief Private variables used internally by the RTOS.
 *  @{
 */

/** @brief Exception return value. 
 *  @note This value is used to return to the thread mode using the PSP.
*/
uint32_t exc_return_temp = 0u;
static volatile uint32_t sysTickCounter = 0;
 /** @} */ // End of RTOS_Private_Variables

/** @defgroup RTOS_Private_Functions Private Functions
 *  @brief Private functions used internally by the RTOS.
 *  @{
 */

 /** @} */ // End of RTOS_Private_Functions

/** @defgroup RTOS_Private_Implementations Private Implementations
 *  @brief Private implementations of RTOS functionalities.
 *  @{
 */

 /** @} */ // End of RTOS_Private_Implementations

/** @defgroup RTOS_Extern_Functions Extern Functions
 *  @brief Externally accessible functions provided by the RTOS.
 *  @{
 */

/**
 * @brief Initializes the RTOS core.
 *
 * This function initializes the RTOS core by configuring the NVIC and the
 * SysTick timer. It also initializes the thread lists and enables the PendSV
 * and SVC interrupts.
 *
 * @note This function must be called before any other RTOS functions are
 *       called.
 *
 * @pre The function must be called before any other RTOS functions are
 *      called.
 *
 * @post The RTOS core is initialized and ready to use.
 */
 void rtos_init(void){
    __disable_irq(); // Disable interrupts by disable all maskable interrupts except NMI and HardFault
    
    /*Enable the double word alignment to comply with the AAPCS ARM architecture call procedure*/
    SCB->CCR |= SCB_CCR_STKALIGN_Msk; 
    
    /*Configure the systick timer to 1ms*/
    SysTick_Config(SYSTEM_CORE_CLOCK_HZ / SYSTEM_TICK_RATE_HZ);

    /* Set priority group to 3
    * bits[3:0] are the sub-priority,
    * bits[7:4] are the preempt priority (0-15) */
    NVIC_SetPriorityGrouping(3);

    NVIC_SetPriority(SVCall_IRQn, 0); // Set the priority of the SVC call
    NVIC_SetPriority(PendSV_IRQn, 0xFF); // Set the priority of the PendSV to the lowest priority in the system
    NVIC_SetPriority(SysTick_IRQn, 1); // Set the priority of the SysTick to the lowest priority in the system

    NVIC_EnableIRQ(SVCall_IRQn); // Enable the SVC call interrupt
    NVIC_EnableIRQ(PendSV_IRQn); // Enable the PendSV interrupt

    /*Mask all interrupts with priority >= 1 which means only SVC is permitted to be serviced*/
    __set_BASEPRI(1); 

    rtos_threadListsInit(); // Initialize the thread lists

    __enable_irq(); // Enable interrupts and will not overwrite the BASEPRI
 }

 
/**
 * @brief Start the RTOS scheduler.
 *
 * This function is used to start the RTOS scheduler. The scheduler is responsible
 * for scheduling threads and performing context switching. The scheduler is
 * started by calling this function after the RTOS initialization.
 *
 * @pre The function must be called after the RTOS initialization.
 *
 * @post The RTOS scheduler is started and ready to schedule threads.
 */
 void rtos_start_scheduler(void){
    
 }
 
/**
 * @brief The main SVC handler function for the RTOS.
 *
 * This function is the entry point for all SVC calls. It is responsible for
 * handling the SVC calls and calling the appropriate functions.
 *
 * @param svc_args The arguments passed to the SVC call.
 *
 * @pre The function must be called through an SVC call.
 *
 * @post The appropriate function is called based on the SVC number.
 */
void rtos_svc_handler_main(uint32_t *svc_args){
   uint8_t svc_number = ((uint8_t *) svc_args[6])[-2];

   switch(svc_number){
      case RTOS_CREATE_TASK:
         rtos_threadCreate((rtos_thread_t *) svc_args[0], (rtos_stack_t *) svc_args[1], (uint32_t) svc_args[2], (void (*)(void)) svc_args[3]);
         break;
      case RTOS_START_SCHEDULER:
         rtos_start_scheduler();
         break;
      default:
         ASSERT(0); // Invalid SVC call
         break;
   }
}

volatile int32_t i = 0;
void RTOS_SysTick_Handler(void)
{
   /*Set the PendSV to pending state to start context switching.*/
   SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; 
   
   /*Increment systick counter*/
	++sysTickCounter;
}
/** @} */ // End of RTOS_Extern_Functions

/** @} */ // End of RTOS_Core


