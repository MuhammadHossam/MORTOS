################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/System_stm32f4xx/Src/stm32f4xx_it.c \
../Libraries/System_stm32f4xx/Src/system_stm32f4xx.c 

OBJS += \
./Libraries/System_stm32f4xx/Src/stm32f4xx_it.o \
./Libraries/System_stm32f4xx/Src/system_stm32f4xx.o 

C_DEPS += \
./Libraries/System_stm32f4xx/Src/stm32f4xx_it.d \
./Libraries/System_stm32f4xx/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/System_stm32f4xx/Src/%.o Libraries/System_stm32f4xx/Src/%.su Libraries/System_stm32f4xx/Src/%.cyclo: ../Libraries/System_stm32f4xx/Src/%.c Libraries/System_stm32f4xx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F446xx -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"E:/Repositories/MORTOS/MoRTOS/Libraries/CMSIS/RTOS/Inc" -I"E:/Repositories/MORTOS/MoRTOS/Libraries/CMSIS/Inc" -I"E:/Repositories/MORTOS/MoRTOS/Libraries/System_stm32f4xx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-System_stm32f4xx-2f-Src

clean-Libraries-2f-System_stm32f4xx-2f-Src:
	-$(RM) ./Libraries/System_stm32f4xx/Src/stm32f4xx_it.cyclo ./Libraries/System_stm32f4xx/Src/stm32f4xx_it.d ./Libraries/System_stm32f4xx/Src/stm32f4xx_it.o ./Libraries/System_stm32f4xx/Src/stm32f4xx_it.su ./Libraries/System_stm32f4xx/Src/system_stm32f4xx.cyclo ./Libraries/System_stm32f4xx/Src/system_stm32f4xx.d ./Libraries/System_stm32f4xx/Src/system_stm32f4xx.o ./Libraries/System_stm32f4xx/Src/system_stm32f4xx.su

.PHONY: clean-Libraries-2f-System_stm32f4xx-2f-Src

