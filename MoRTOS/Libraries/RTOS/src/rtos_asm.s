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
    ldr r1, =svcEXEReturn       /*Store the address of temp exception return address*/
    str lr, [r1]                /*Load the link register in the svcEXEReturn variable*/
    bl rtos_svc_handler_main    /*Branch to the svc main handler function implemented in C*/
    ldr r1, =svcEXEReturn
    ldr lr, [r1]                /*load the lr back after return from the function*/
    bx lr                       /*return by branching back*/   


.type RTOS_PendSV_Handler, %function
RTOS_PendSV_Handler:
    /*Save the context switching*/
    mrs r1, psp                         /* Move the psp to r1*/
    tst lr, #0x10                       /* Check the FPU to save them if needed.*/
    it eq                               /* zero flag is set */
    vstmdbeq r1!, {s16-s31}             /* Store the floating point registers s16-s31 */
    mov r2, lr                          /* Store the content of LR (EXC_RETURN of current task) to r2 */
    mrs r3, control                     /* Store the content of control register to r3 */
    stmdb r1!, {r2-r11}                 /* Store R4-R11 + Contrl + LR before R1, then update R1 */
    bl rtos_RunningThreadGet            /* Return the current running thread and it's pointing to the thread stack pointer.*/
    str r1, [r0]                        /* Store the r1 (contains the current stack pointer value) to return of the function (thread stack pointer)*/
    
    /*load the context of the new running task*/
    mov r1, #1 							/* Load r1 with #1*/
	msr basepri, r1						/* Mask all interrupts with priority equals to or higher than #1*/
	bl rtos_threadSwitchingRunning		/* Run the thread switching routine.*/
	mov r1, #0							/* Load r1 with #0*/
	msr basepri, r1						/* Mask all interrupts with priority equals to or higher than #0*/
	bl rtos_RunningThreadGet            /* Return the current running thread and it's pointing to the thread stack pointer.*/
	ldr r1, [r0]						/* Load r1 with the address content of r0 which is the current thread stack pointer*/
	ldmia r1!, {r2-r11}					/* Load the stack frame to r2-r11 and it will be then pointing to the r0*/
	mov lr, r2							/* Store the content of r2 (EXEC_RETURN) to the link register*/
	msr control, r3						/* Store content of r3 to the control register*/
	isb									/* Instruction synchronization barrier and CPU cache flushing.*/
	tst lr, #0x10						/* Check the FPU to save them if needed*/
	it eq
	vldmiaeq r1!, {s16-s31}				/* Restore the FPU registers in case of the task was using the FPU*/
	msr psp, r1							/* Update the psp with the content of r1 which is the stack address pointing to r0 (beginning of ISR stack frame)*/
    bx lr /*return back*/
