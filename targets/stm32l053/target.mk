LIBNAME = opencm3_stm32l0
DEFS += STM32L0

LD_FILE := stm32l0xx8.ld

FP_FLAGS ?= -msoft-float
ARCH_FLAGS = -mthumb -mcpu=cortex-m0plus $(FP_FLAGS)

INCS += libopencm3/include/

LIBS += -lopencm3_stm32l0
