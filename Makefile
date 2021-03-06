#Makefile for building project for Linux
OBJS=main.o 3dm.o gl.o basic.o vbo.o app.o glad/glad.o
O=corridor

CFLAGS=-nocpp -g3 -Og -pipe -m64 -march=native -mtune=native
CFLAGS+=-ftree-vectorize -ffast-math -funroll-loops
LDFLAGS=-lSDL2 -lm -ldl

all: ${O}

clean:
	@rm -fv ${O} ${OBJS}

${O}: ${OBJS}
	${CC} $^ -o $@ ${LDFLAGS}
