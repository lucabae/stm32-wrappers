# Compilador cruzado para ARM bare-metal
CC = arm-none-eabi-gcc

# Flags: -c (solo compilar, no enlazar), -mcpu (ajusta según tu familia STM32, ej: cortex-m4, cortex-m0)
CFLAGS = -Wall -Wextra -c -mcpu=cortex-m4 -mthumb

# Rutas de inclusión. Es vital que apuntes bien a las carpetas CMSIS
INCLUDES = -I./inc -I./CMSIS/Include -I./CMSIS/Device # Ajusta esta última ruta a la subcarpeta de tu STM32 exacto

SRC = src/gpio.c
OBJ = gpio.o

# Target principal para verificar
check:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(OBJ)
	@echo "Si no hay errores arriba, la sintaxis y los nombres de registros son correctos."

clean:
	rm -f $(OBJ)
