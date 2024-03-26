#include <iostream>
#include "./deep-learning/activation_function.cpp"

int main()
{
    std::cout << ActivationFunction::Sigmoid(2) << std::endl;
    std::cout << ActivationFunction::Sigmoid(20) << std::endl;
    std::cout << ActivationFunction::Sigmoid(-2) << std::endl;
    std::cout << ActivationFunction::Sigmoid(200) << std::endl;
    std::cout << ActivationFunction::Sigmoid(12) << std::endl;

    Matrix_ANE *matrix = new Matrix_ANE();
    matrix->Add({2, 4});
    matrix->Add({3, 14});
    matrix->Add({4, 41});
    matrix->DisplayMatrix();

    std::cout << "---------" << std::endl;

    Matrix_ANE *sigmoid = ActivationFunction::Sigmoid(matrix);
    sigmoid->DisplayMatrix();
}

// g++ *.cpp ./deep-learning/*.cpp -std=c++11 -o  main.out