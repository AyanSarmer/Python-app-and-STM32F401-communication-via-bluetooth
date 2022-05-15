# Основные параметры проекта
FILE 				= fileName
CPU					= cortex-m4
# Папки хранения файлов
SRC_DIR       		= src
INC_DIR       		= inc
EXE_DIR       		= exe
SPL_PATH			= D:/GNU/ARM/SPL
STARTUP_PATH		= $(SPL_PATH)/STM32F4/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7

# Список объектных файлов
SOURCES 			= $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES 		= $(STARTUP_PATH)/startup_stm32f401xx.s 
OBJECTS 			= $(SOURCES:.c=.o)
OBJECTS       		+= $(ASM_SOURCES:.s=.o)
# Компилятор GCC и опции его утилит
PREAMBLE 			= arm-none-eabi-
CC 					= $(PREAMBLE)gcc
	CC_OPTIONS  	= -mcpu=$(CPU)
	CC_OPTIONS  	+= -mthumb
	CC_OPTIONS  	+= -D STM32F401xx
	CC_OPTIONS  	+= -I $(INC_DIR)
	CC_OPTIONS  	+= -I $(SPL_PATH)/STM32F4/Libraries/CMSIS/Device/ST/STM32F4xx/Include
	CC_OPTIONS  	+= -I $(SPL_PATH)/STM32F4/Libraries/CMSIS/Include
	CC_OPTIONS  	+= -Og
	CC_OPTIONS  	+= -fdata-sections
	CC_OPTIONS  	+= -ffunction-sections
	CC_OPTIONS  	+= -Wall
	CC_OPTIONS  	+= -c
	CC_OPTIONS  	+= -o
AS					= $(PREAMBLE)gcc
	AS_OPTIONS		= -x assembler-with-cpp
	LL_OPTIONS  	= -mcpu=$(CPU)
	LL_OPTIONS  	+= -mthumb
	LL_OPTIONS		+= -specs=nano.specs
	LL_OPTIONS		+= -specs=nosys.specs
	LL_OPTIONS		+= -u _printf_float
	LL_OPTIONS		+= -TLinkerScript.ld
	LL_OPTIONS		+= -Wl,--gc-sections
	LL_OPTIONS		+= -o
# Копировщик и его опции
COPIER				= $(PREAMBLE)objcopy
	CP_OPTIONS		= -O ihex
# Загрузчик и его опции
UPLOADER      		= openocd
	U_OPTIONS		= -f interface/stlink-v2.cfg
	U_OPTIONS		+= -f target/stm32f4x.cfg 
	U_OPTIONS		+= -c "init"
	U_OPTIONS		+= -c "reset init"
	U_OPTIONS		+= -c "flash write_image erase $(EXE_DIR)/$(FILE).hex"
	U_OPTIONS		+= -c "reset" -c "exit"