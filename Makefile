LDLIBS=-lglut -lGL -lGLU -lGLEW
all: main
clean:
	rm -f *.o main
.PHONY: all clean