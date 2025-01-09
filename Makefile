FREEGLUT_DIR=./freeglut/
FREEGLUT_HEADERS=./freeglut/include
LIB_DIR=./lib/

CFLAGS=-Wall -Wextra
LFLAGS=-I $(FREEGLUT_HEADERS) -I $(LIB_DIR) -L $(FREEGLUT_DIR) -lm -lGL -lGLU -lglut
FLAGS=$(CFLAGS) $(LFLAGS)


principal: main main2

main: main.cpp
	g++ ./main.cpp ./lib/RgbImage.cpp -o main.exe $(FLAGS)
main2: main2.cpp
	g++ ./main2.cpp ./lib/RgbImage.cpp -o main2.exe $(FLAGS)


all: exemplos principal


exemplos: garra cabeca

garra: ./exemplos/garra.cpp
	g++ ./exemplos/garra.cpp ./lib/RgbImage.cpp -o garra.exe $(FLAGS)
cabeca: ./exemplos/cabeca.cpp
	g++ ./exemplos/cabeca.cpp ./lib/RgbImage.cpp -o cabeca.exe $(FLAGS)

