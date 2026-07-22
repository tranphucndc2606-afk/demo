################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/app_autoparking.c \
../App/src/app_control.c \
../App/src/app_pid.c \
../App/src/app_safety.c 

OBJS += \
./App/src/app_autoparking.o \
./App/src/app_control.o \
./App/src/app_pid.o \
./App/src/app_safety.o 

C_DEPS += \
./App/src/app_autoparking.d \
./App/src/app_control.d \
./App/src/app_pid.d \
./App/src/app_safety.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o App/src/%.su App/src/%.cyclo: ../App/src/%.c App/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/Xe_tham_hiem_v2/App/inc" -I"D:/ST/Xe_tham_hiem_v2/PAL/inc" -I"D:/ST/Xe_tham_hiem_v2/Protocol/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-src

clean-App-2f-src:
	-$(RM) ./App/src/app_autoparking.cyclo ./App/src/app_autoparking.d ./App/src/app_autoparking.o ./App/src/app_autoparking.su ./App/src/app_control.cyclo ./App/src/app_control.d ./App/src/app_control.o ./App/src/app_control.su ./App/src/app_pid.cyclo ./App/src/app_pid.d ./App/src/app_pid.o ./App/src/app_pid.su ./App/src/app_safety.cyclo ./App/src/app_safety.d ./App/src/app_safety.o ./App/src/app_safety.su

.PHONY: clean-App-2f-src

