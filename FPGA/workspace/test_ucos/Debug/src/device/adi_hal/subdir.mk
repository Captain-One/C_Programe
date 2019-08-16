################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/device/adi_hal/axi_adc_core.c \
../src/device/adi_hal/axi_adxcvr.c \
../src/device/adi_hal/axi_dac_core.c \
../src/device/adi_hal/axi_dmac.c \
../src/device/adi_hal/axi_jesd204_rx.c \
../src/device/adi_hal/axi_jesd204_tx.c \
../src/device/adi_hal/clk_axi_clkgen.c \
../src/device/adi_hal/no_os_hal.c \
../src/device/adi_hal/platform_drivers.c \
../src/device/adi_hal/util.c \
../src/device/adi_hal/xilinx_transceiver.c 

OBJS += \
./src/device/adi_hal/axi_adc_core.o \
./src/device/adi_hal/axi_adxcvr.o \
./src/device/adi_hal/axi_dac_core.o \
./src/device/adi_hal/axi_dmac.o \
./src/device/adi_hal/axi_jesd204_rx.o \
./src/device/adi_hal/axi_jesd204_tx.o \
./src/device/adi_hal/clk_axi_clkgen.o \
./src/device/adi_hal/no_os_hal.o \
./src/device/adi_hal/platform_drivers.o \
./src/device/adi_hal/util.o \
./src/device/adi_hal/xilinx_transceiver.o 

C_DEPS += \
./src/device/adi_hal/axi_adc_core.d \
./src/device/adi_hal/axi_adxcvr.d \
./src/device/adi_hal/axi_dac_core.d \
./src/device/adi_hal/axi_dmac.d \
./src/device/adi_hal/axi_jesd204_rx.d \
./src/device/adi_hal/axi_jesd204_tx.d \
./src/device/adi_hal/clk_axi_clkgen.d \
./src/device/adi_hal/no_os_hal.d \
./src/device/adi_hal/platform_drivers.d \
./src/device/adi_hal/util.d \
./src/device/adi_hal/xilinx_transceiver.d 


# Each subdirectory must supply rules for building sources it contributes
src/device/adi_hal/%.o: ../src/device/adi_hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v8 gcc compiler'
	aarch64-none-elf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../ucos_bsp/psu_cortexa53_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


