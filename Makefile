FREEGLUT_DIR=./freeglut/
LIB_DIR=./lib/
FREEGLUT_HEADERS=./freeglut/include

CFLAGS=-Wall -Wextra
LFLAGS=-I $(FREEGLUT_HEADERS) -I $(LIB_DIR) -L $(FREEGLUT_DIR) -lm -lGL -lGLU -lglut
FLAGS=$(CFLAGS) $(LFLAGS)


all: garra cabeca

garra: garra.cpp
	g++ garra.cpp ./lib/RgbImage.cpp -o garra.exe $(FLAGS)

cabeca: cabeca.cpp
	g++ cabeca.cpp ./lib/RgbImage.cpp -o cabeca.exe $(FLAGS)

