.syntax unified 
.cpu cortex-m4
.thumb 

.global RTOS_SVC_Handler
.global RTOS_PendSV_Handler


.text 


.type RTOS_SVC_Handler, %function
RTOS_SVC_Handler:
    tst lr, #4                  /*Test bit #2 of EXC_RETURN*/
    ite eq                      /*if equal zero, MSP was used*/
    mrseq r0, MSP               /*Move MSP to R0 if MSP was used*/
    mrsne r0, PSP               /*Move PSP to R0 if MMSP was used*/
    ldr r1, =exc_return_temp    /*Store the address of temp exception return address*/
    str lr, [r1]                /*Load the link register in the exc_return_temp variable*/
    bl rtos_svc_handler_main    /*Branch to the svc main handler function implemented in C*/
    ldr r1, =exc_return_temp
    ldr lr, [r1]                /*load the lr back after return from the function*/
    bx lr                       /*return by branching back*/   


.type RTOS_PendSV_Handler, %function
RTOS_PendSV_Handler:
    bx lr /*return back*/