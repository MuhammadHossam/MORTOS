.syntax unified 
.cpu cortex-m4
.thumb 


.global rtos_svc_threadCreate

.text 

.type rtos_svc_threadCreate, %function
rtos_svc_threadCreate:
    svc 1
    bx lr /*return back*/