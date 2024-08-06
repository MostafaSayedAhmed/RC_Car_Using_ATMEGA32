################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/7Seg/7Seg.c 

OBJS += \
./MCAL/7Seg/7Seg.o 

C_DEPS += \
./MCAL/7Seg/7Seg.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/7Seg/%.o: ../MCAL/7Seg/%.c MCAL/7Seg/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


