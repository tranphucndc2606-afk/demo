################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Protocol/src/protocol_uart.c 

OBJS += \
./Protocol/src/protocol_uart.o 

C_DEPS += \
./Protocol/src/protocol_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Protocol/src/%.o Protocol/src/%.su Protocol/src/%.cyclo: ../Protocol/src/%.c Protocol/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/Xe_tham_hiem_v2/App/inc" -I"D:/ST/Xe_tham_hiem_v2/PAL/inc" -I"D:/ST/Xe_tham_hiem_v2/Protocol/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Protocol-2f-src

clean-Protocol-2f-src:
	-$(RM) ./Protocol/src/protocol_uart.cyclo ./Protocol/src/protocol_uart.d ./Protocol/src/protocol_uart.o ./Protocol/src/protocol_uart.su

.PHONY: clean-Protocol-2f-src

