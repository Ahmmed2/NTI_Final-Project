################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HAL/DC_MOTOR.c \
../Core/Src/HAL/Ultrasonic.c 

OBJS += \
./Core/Src/HAL/DC_MOTOR.o \
./Core/Src/HAL/Ultrasonic.o 

C_DEPS += \
./Core/Src/HAL/DC_MOTOR.d \
./Core/Src/HAL/Ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/HAL/%.o Core/Src/HAL/%.su Core/Src/HAL/%.cyclo: ../Core/Src/HAL/%.c Core/Src/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-HAL

clean-Core-2f-Src-2f-HAL:
	-$(RM) ./Core/Src/HAL/DC_MOTOR.cyclo ./Core/Src/HAL/DC_MOTOR.d ./Core/Src/HAL/DC_MOTOR.o ./Core/Src/HAL/DC_MOTOR.su ./Core/Src/HAL/Ultrasonic.cyclo ./Core/Src/HAL/Ultrasonic.d ./Core/Src/HAL/Ultrasonic.o ./Core/Src/HAL/Ultrasonic.su

.PHONY: clean-Core-2f-Src-2f-HAL

