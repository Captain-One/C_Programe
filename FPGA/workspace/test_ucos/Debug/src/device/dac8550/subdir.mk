################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/device/dac8550/dac8550.c 

OBJS += \
./src/device/dac8550/dac8550.o 

C_DEPS += \
./src/device/dac8550/dac8550.d 


# Each subdirectory must supply rules for building sources it contributes
src/device/dac8550/%.o: ../src/device/dac8550/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v8 gcc compiler'
	aarch64-none-elf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../ucos_bsp/psu_cortexa53_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


