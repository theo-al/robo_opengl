FREEGLUT_DIR=./freeglut/
FREEGLUT_HEADERS=./freeglut/include
LIB_DIR=./lib/

CFLAGS=-Wall -Wextra
LFLAGS=-I $(FREEGLUT_HEADERS) -I $(LIB_DIR) -L $(FREEGLUT_DIR) -lm -lGL -lGLU -lglut
FLAGS=$(CFLAGS) $(LFLAGS)


main: main.cpp
	g++ ./main.cpp ./lib/RgbImage.cpp -o main.exe $(FLAGS)



all: exemplos main


garra: ./exemplos/garra.cpp
	g++ ./exemplos/garra.cpp ./lib/RgbImage.cpp -o garra.exe $(FLAGS)
cabeca: ./exemplos/cabeca.cpp
	g++ ./exemplos/cabeca.cpp ./lib/RgbImage.cpp -o cabeca.exe $(FLAGS)

exemplos: garra cabeca

