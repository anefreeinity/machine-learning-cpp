ifeq ($(OS),Windows_NT)
    build:
		g++ *.cpp ./deep-learning/src/*.cpp ./hand-written-digit/src/hand_written_digit_tranning_model.cpp -std=c++11 -o  main.exe
else
    build:
		g++ *.cpp ./deep-learning/src/*.cpp ./hand-written-digit/src/hand_written_digit_tranning_model.cpp -std=c++11 -o  main.out
endif