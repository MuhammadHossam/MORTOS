.syntax unified 
.cpu cortex-m4
.thumb 

.global RTOS_SVC_Handler
.global RTOS_PendSV_Handler


.text 


.type RTOS_SVC_Handler, %function
RTOS_SVC_Handler:
    bx lr /*return back*/


.type RTOS_PendSV_Handler, %function
RTOS_PendSV_Handler:
    bx lr /*return back*/