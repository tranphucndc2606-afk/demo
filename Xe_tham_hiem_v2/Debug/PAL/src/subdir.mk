################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PAL/src/dev_ds18b20.c \
../PAL/src/dev_encoder.c \
../PAL/src/dev_motor.c \
../PAL/src/dev_oled.c \
../PAL/src/dev_sonar.c 

OBJS += \
./PAL/src/dev_ds18b20.o \
./PAL/src/dev_encoder.o \
./PAL/src/dev_motor.o \
./PAL/src/dev_oled.o \
./PAL/src/dev_sonar.o 

C_DEPS += \
./PAL/src/dev_ds18b20.d \
./PAL/src/dev_encoder.d \
./PAL/src/dev_motor.d \
./PAL/src/dev_oled.d \
./PAL/src/dev_sonar.d 


# Each subdirectory must supply rules for building sources it contributes
PAL/src/%.o PAL/src/%.su PAL/src/%.cyclo: ../PAL/src/%.c PAL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/Xe_tham_hiem_v2/App/inc" -I"D:/ST/Xe_tham_hiem_v2/PAL/inc" -I"D:/ST/Xe_tham_hiem_v2/Protocol/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PAL-2f-src

clean-PAL-2f-src:
	-$(RM) ./PAL/src/dev_ds18b20.cyclo ./PAL/src/dev_ds18b20.d ./PAL/src/dev_ds18b20.o ./PAL/src/dev_ds18b20.su ./PAL/src/dev_encoder.cyclo ./PAL/src/dev_encoder.d ./PAL/src/dev_encoder.o ./PAL/src/dev_encoder.su ./PAL/src/dev_motor.cyclo ./PAL/src/dev_motor.d ./PAL/src/dev_motor.o ./PAL/src/dev_motor.su ./PAL/src/dev_oled.cyclo ./PAL/src/dev_oled.d ./PAL/src/dev_oled.o ./PAL/src/dev_oled.su ./PAL/src/dev_sonar.cyclo ./PAL/src/dev_sonar.d ./PAL/src/dev_sonar.o ./PAL/src/dev_sonar.su

.PHONY: clean-PAL-2f-src

