################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/device/lmx2594/lmx2594.c 

OBJS += \
./src/device/lmx2594/lmx2594.o 

C_DEPS += \
./src/device/lmx2594/lmx2594.d 


# Each subdirectory must supply rules for building sources it contributes
src/device/lmx2594/%.o: ../src/device/lmx2594/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v8 gcc compiler'
	aarch64-none-elf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../ucos_bsp/psu_cortexa53_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


