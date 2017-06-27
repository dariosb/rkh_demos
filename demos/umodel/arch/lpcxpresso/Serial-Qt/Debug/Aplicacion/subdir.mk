################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicacion/AP_Mensajes.c \
../Aplicacion/main.c 

OBJS += \
./Aplicacion/AP_Mensajes.o \
./Aplicacion/main.o 

C_DEPS += \
./Aplicacion/AP_Mensajes.d \
./Aplicacion/main.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicacion/%.o: ../Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Aplicacion" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Drivers" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\KitInfo2" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Primitivas" -O0 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


