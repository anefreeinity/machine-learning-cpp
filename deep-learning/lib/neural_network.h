#pragma once
#include <vector>
// #include <cstdlib>
// #include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
#include "./activation_function.h"

namespace ANEFreeInIty
{
    class NeuralNetwork
    {
    private:
        int _inputLayerSize;
        int _hiddenLayerSize;
        int _outputLayerSize;

        std::vector<std::vector<double>> _hiddenLayerWeights;
        std::vector<std::vector<double>> _outputLayerWeights;

        std::vector<double> _hiddenLayerBiases;
        std::vector<double> _outputLayerBiases;

        std::vector<double> _hiddenLayerCalculatedOutput;
        std::vector<double> _outputLayerCalculatedOutput;

        double _learningRate;

        double GetNormalizedRandom();
        std::vector<double> Forward(std::vector<double> &);
        void BackPropagate(std::vector<double> &, std::vector<double> &);

    public:
        NeuralNetwork();
        NeuralNetwork(int, int, int, double learningRate = 0.1);
        std::vector<std::vector<double>> Normalize(std::vector<std::vector<double>> &, int, double factor = 0);
        void Train(std::vector<std::vector<double>> &trainingInputData, std::vector<std::vector<double>> &, int, int);
        std::vector<double> Predict(std::vector<double> &);
    };
}
