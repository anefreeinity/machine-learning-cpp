OS := $(shell uname)

ifeq ($(OS),Darwin)
    CC=g++
    CFLAGS=-c -std=c++11
    LDFLAGS=-dynamiclib
    TARGET=hand_written_digit_lib.dylib
    REMOVEFLAG=rm -f
else ifeq ($(OS),Linux)
    CC=g++
    CFLAGS=-c -std=c++11
    LDFLAGS=-shared
    TARGET=hand_written_digit_lib.so
    REMOVEFLAG=rm -f
else
    CC=g++
    CFLAGS=-c -std=c++11
    LDFLAGS=-shared
    TARGET=hand_written_digit_lib.dll
    REMOVEFLAG=del /F
endif

all: compile link

compile:
	$(CC) $(CFLAGS) *.cpp
	$(CC) $(CFLAGS) ../file-system/src/*.cpp
	$(CC) $(CFLAGS) ../deep-learning/src/*.cpp
	$(CC) $(CFLAGS) ../hand-written-digit/src/hand_written_digit_tranning_model.cpp

link:
	$(CC) $(LDFLAGS) -o $(TARGET) *.o

clean:
	$(REMOVEFLAG) *.o $(TARGET)
