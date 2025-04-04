.syntax unified 
.cpu cortex-m4
.thumb 


.global rtos_svc_threadCreate
.global rtos_svc_schedulerStart
.global rtos_svc_mutexCreate
.global rtos_svc_mutexLock

.text 

.type rtos_svc_threadCreate, %function
rtos_svc_threadCreate:
    svc 1
    bx lr /*return back*/


.type rtos_svc_schedulerStart, %function
rtos_svc_schedulerStart:
    svc 0
    bx lr /*return back*/


.type rtos_svc_mutexCreate, %function
rtos_svc_mutexCreate:
    svc 2
    bx lr /*return back*/


.type rtos_svc_mutexLock, %function
rtos_svc_mutexLock:
    svc 3
    bx lr /*return back*/