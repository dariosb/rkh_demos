################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/PR_Display7Seg.c \
../Primitivas/PR_DisplayMatricial.c \
../Primitivas/PR_IO.c \
../Primitivas/PR_Serie.c \
../Primitivas/PR_Teclado.c \
../Primitivas/PR_Timer.c \
../Primitivas/PR_lcd.c 

OBJS += \
./Primitivas/PR_Display7Seg.o \
./Primitivas/PR_DisplayMatricial.o \
./Primitivas/PR_IO.o \
./Primitivas/PR_Serie.o \
./Primitivas/PR_Teclado.o \
./Primitivas/PR_Timer.o \
./Primitivas/PR_lcd.o 

C_DEPS += \
./Primitivas/PR_Display7Seg.d \
./Primitivas/PR_DisplayMatricial.d \
./Primitivas/PR_IO.d \
./Primitivas/PR_Serie.d \
./Primitivas/PR_Teclado.d \
./Primitivas/PR_Timer.d \
./Primitivas/PR_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Aplicacion" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Drivers" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\KitInfo2" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Primitivas" -O0 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


