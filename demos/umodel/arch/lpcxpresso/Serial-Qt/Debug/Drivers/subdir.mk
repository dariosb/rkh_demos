################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FW_ADC.c \
../Drivers/FW_DAC.c \
../Drivers/FW_Display7Seg.c \
../Drivers/FW_DisplayMatricial.c \
../Drivers/FW_EXP1IO.c \
../Drivers/FW_IO.c \
../Drivers/FW_LCD.c \
../Drivers/FW_RTC.c \
../Drivers/FW_Serie.c \
../Drivers/FW_Teclado.c \
../Drivers/FW_Timertick.c 

OBJS += \
./Drivers/FW_ADC.o \
./Drivers/FW_DAC.o \
./Drivers/FW_Display7Seg.o \
./Drivers/FW_DisplayMatricial.o \
./Drivers/FW_EXP1IO.o \
./Drivers/FW_IO.o \
./Drivers/FW_LCD.o \
./Drivers/FW_RTC.o \
./Drivers/FW_Serie.o \
./Drivers/FW_Teclado.o \
./Drivers/FW_Timertick.o 

C_DEPS += \
./Drivers/FW_ADC.d \
./Drivers/FW_DAC.d \
./Drivers/FW_Display7Seg.d \
./Drivers/FW_DisplayMatricial.d \
./Drivers/FW_EXP1IO.d \
./Drivers/FW_IO.d \
./Drivers/FW_LCD.d \
./Drivers/FW_RTC.d \
./Drivers/FW_Serie.d \
./Drivers/FW_Teclado.d \
./Drivers/FW_Timertick.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Aplicacion" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Drivers" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\KitInfo2" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Primitivas" -O0 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


