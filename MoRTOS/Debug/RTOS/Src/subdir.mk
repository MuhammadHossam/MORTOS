################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../RTOS/Src/rtos_asm.s \
../RTOS/Src/rtos_svc_calls.s 

C_SRCS += \
../RTOS/Src/rtos.c \
../RTOS/Src/rtos_list.c \
../RTOS/Src/rtos_thread.c 

OBJS += \
./RTOS/Src/rtos.o \
./RTOS/Src/rtos_asm.o \
./RTOS/Src/rtos_list.o \
./RTOS/Src/rtos_svc_calls.o \
./RTOS/Src/rtos_thread.o 

S_DEPS += \
./RTOS/Src/rtos_asm.d \
./RTOS/Src/rtos_svc_calls.d 

C_DEPS += \
./RTOS/Src/rtos.d \
./RTOS/Src/rtos_list.d \
./RTOS/Src/rtos_thread.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS/Src/%.o RTOS/Src/%.su RTOS/Src/%.cyclo: ../RTOS/Src/%.c RTOS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F446xx -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"E:/Repositories/MORTOS/MoRTOS/Libraries/CMSIS/RTOS/Inc" -I"E:/Repositories/MORTOS/MoRTOS/Libraries/CMSIS/Inc" -I"E:/Repositories/MORTOS/MoRTOS/Libraries/System_stm32f4xx/Inc" -I"E:/Repositories/MORTOS/MoRTOS/RTOS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
RTOS/Src/%.o: ../RTOS/Src/%.s RTOS/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-RTOS-2f-Src

clean-RTOS-2f-Src:
	-$(RM) ./RTOS/Src/rtos.cyclo ./RTOS/Src/rtos.d ./RTOS/Src/rtos.o ./RTOS/Src/rtos.su ./RTOS/Src/rtos_asm.d ./RTOS/Src/rtos_asm.o ./RTOS/Src/rtos_list.cyclo ./RTOS/Src/rtos_list.d ./RTOS/Src/rtos_list.o ./RTOS/Src/rtos_list.su ./RTOS/Src/rtos_svc_calls.d ./RTOS/Src/rtos_svc_calls.o ./RTOS/Src/rtos_thread.cyclo ./RTOS/Src/rtos_thread.d ./RTOS/Src/rtos_thread.o ./RTOS/Src/rtos_thread.su

.PHONY: clean-RTOS-2f-Src

