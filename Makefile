ifeq ($(OS),Windows_NT)
    build:
		g++ *.cpp ./deep-learning/src/*.cpp -std=c++11 -o  main.exe
else
    build:
		g++ *.cpp ./deep-learning/src/*.cpp -std=c++11 -o  main.out
endif