################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/debounce/Src/API_debounce.c 

OBJS += \
./Drivers/debounce/Src/API_debounce.o 

C_DEPS += \
./Drivers/debounce/Src/API_debounce.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/debounce/Src/%.o Drivers/debounce/Src/%.su Drivers/debounce/Src/%.cyclo: ../Drivers/debounce/Src/%.c Drivers/debounce/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/CMSIS/Include -I../Drivers/debounce/Inc -I../Drivers/delay/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-debounce-2f-Src

clean-Drivers-2f-debounce-2f-Src:
	-$(RM) ./Drivers/debounce/Src/API_debounce.cyclo ./Drivers/debounce/Src/API_debounce.d ./Drivers/debounce/Src/API_debounce.o ./Drivers/debounce/Src/API_debounce.su

.PHONY: clean-Drivers-2f-debounce-2f-Src

