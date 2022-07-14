################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Button.c \
../Core/Src/Buzzer.c \
../Core/Src/Cli.c \
../Core/Src/Clock.c \
../Core/Src/Communication.c \
../Core/Src/Led.c \
../Core/Src/LedState.c \
../Core/Src/LightSensor.c \
../Core/Src/MyMain.c \
../Core/Src/main.c \
../Core/Src/music.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/Button.o \
./Core/Src/Buzzer.o \
./Core/Src/Cli.o \
./Core/Src/Clock.o \
./Core/Src/Communication.o \
./Core/Src/Led.o \
./Core/Src/LedState.o \
./Core/Src/LightSensor.o \
./Core/Src/MyMain.o \
./Core/Src/main.o \
./Core/Src/music.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/Button.d \
./Core/Src/Buzzer.d \
./Core/Src/Cli.d \
./Core/Src/Clock.d \
./Core/Src/Communication.d \
./Core/Src/Led.d \
./Core/Src/LedState.d \
./Core/Src/LightSensor.d \
./Core/Src/MyMain.d \
./Core/Src/main.d \
./Core/Src/music.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/Cli.d ./Core/Src/Cli.o ./Core/Src/Cli.su ./Core/Src/Clock.d ./Core/Src/Clock.o ./Core/Src/Clock.su ./Core/Src/Communication.d ./Core/Src/Communication.o ./Core/Src/Communication.su ./Core/Src/Led.d ./Core/Src/Led.o ./Core/Src/Led.su ./Core/Src/LedState.d ./Core/Src/LedState.o ./Core/Src/LedState.su ./Core/Src/LightSensor.d ./Core/Src/LightSensor.o ./Core/Src/LightSensor.su ./Core/Src/MyMain.d ./Core/Src/MyMain.o ./Core/Src/MyMain.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/music.d ./Core/Src/music.o ./Core/Src/music.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

