#baifo@etsii.ull.es
#OBJS especifica que archivos tenemos que compilar
OBJS = celda.cpp tablero.cpp main.cpp car.cpp

#CC especifica el compilador
CC = g++

#COMPILER_FLAGS especifica información adicional
COMPILER_FLAGS = -w -g

#LINKER_FLAGS especifica las librerias que vamos a linkar
LINKER_FLAGS = -lGL -lGLU -lglut

#OBJ_NAME especifica el nombre del ejecutable
OBJ_NAME = pract01

#comando
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
