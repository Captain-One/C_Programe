################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

C_SRCS += \
../main.c \
../platform_osal_function.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./main.d \
./platform_osal_function.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./main.obj \
./platform_osal_function.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"main.obj" \
"platform_osal_function.obj" 

C_DEPS__QUOTED += \
"main.d" \
"platform_osal_function.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../main.c" \
"../platform_osal_function.c" 


