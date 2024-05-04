OS := $(shell uname)

ifeq ($(OS),Darwin)
    CC=g++
    CFLAGS=-std=c++11
    EXECUTABLE=main.out
	REMOVEFLAG=rm -f
else ifeq ($(OS),Linux)
    CC=g++
    CFLAGS=-std=c++11
    EXECUTABLE=main.out
	REMOVEFLAG=rm -f
else
    CC=g++
    CFLAGS=-std=c++11
    EXECUTABLE=main.exe
	REMOVEFLAG=del /F
endif

DLFILES=./deep-learning/src/*.cpp
HWDFILES=./hand-written-digit/src/*.cpp
FSFILES=./file-system/src/*.cpp

all: compile link

compile:
	$(CC) $(CFLAGS) *.cpp $(DLFILES) $(HWDFILES) $(FSFILES) -o $(EXECUTABLE)

link:
	./$(EXECUTABLE)

clean:
	${REMOVEFLAG} $(EXECUTABLE)
