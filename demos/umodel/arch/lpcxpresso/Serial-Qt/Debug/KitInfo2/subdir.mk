################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../KitInfo2/KitInic.c \
../KitInfo2/KitInic_Expansiones.c \
../KitInfo2/UtilesInfo2.c \
../KitInfo2/cr_startup_lpc176x.c 

OBJS += \
./KitInfo2/KitInic.o \
./KitInfo2/KitInic_Expansiones.o \
./KitInfo2/UtilesInfo2.o \
./KitInfo2/cr_startup_lpc176x.o 

C_DEPS += \
./KitInfo2/KitInic.d \
./KitInfo2/KitInic_Expansiones.d \
./KitInfo2/UtilesInfo2.d \
./KitInfo2/cr_startup_lpc176x.d 


# Each subdirectory must supply rules for building sources it contributes
KitInfo2/%.o: ../KitInfo2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Aplicacion" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Drivers" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\KitInfo2" -I"D:\UTN_2016\rkh_demos\demos\umodel\Serial-Qt\Primitivas" -O0 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


