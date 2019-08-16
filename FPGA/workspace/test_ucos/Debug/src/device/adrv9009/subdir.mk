################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/device/adrv9009/talise.c \
../src/device/adrv9009/talise_agc.c \
../src/device/adrv9009/talise_arm.c \
../src/device/adrv9009/talise_cals.c \
../src/device/adrv9009/talise_error.c \
../src/device/adrv9009/talise_gpio.c \
../src/device/adrv9009/talise_hal.c \
../src/device/adrv9009/talise_jesd204.c \
../src/device/adrv9009/talise_radioctrl.c \
../src/device/adrv9009/talise_rx.c \
../src/device/adrv9009/talise_tx.c \
../src/device/adrv9009/talise_user.c 

OBJS += \
./src/device/adrv9009/talise.o \
./src/device/adrv9009/talise_agc.o \
./src/device/adrv9009/talise_arm.o \
./src/device/adrv9009/talise_cals.o \
./src/device/adrv9009/talise_error.o \
./src/device/adrv9009/talise_gpio.o \
./src/device/adrv9009/talise_hal.o \
./src/device/adrv9009/talise_jesd204.o \
./src/device/adrv9009/talise_radioctrl.o \
./src/device/adrv9009/talise_rx.o \
./src/device/adrv9009/talise_tx.o \
./src/device/adrv9009/talise_user.o 

C_DEPS += \
./src/device/adrv9009/talise.d \
./src/device/adrv9009/talise_agc.d \
./src/device/adrv9009/talise_arm.d \
./src/device/adrv9009/talise_cals.d \
./src/device/adrv9009/talise_error.d \
./src/device/adrv9009/talise_gpio.d \
./src/device/adrv9009/talise_hal.d \
./src/device/adrv9009/talise_jesd204.d \
./src/device/adrv9009/talise_radioctrl.d \
./src/device/adrv9009/talise_rx.d \
./src/device/adrv9009/talise_tx.d \
./src/device/adrv9009/talise_user.d 


# Each subdirectory must supply rules for building sources it contributes
src/device/adrv9009/%.o: ../src/device/adrv9009/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v8 gcc compiler'
	aarch64-none-elf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../ucos_bsp/psu_cortexa53_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


