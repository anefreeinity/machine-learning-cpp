#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include "./activation_function.h"

namespace ANEFreeInIty
{
    class NeuralNetwork
    {
    private:
        std::string HIDDEN_LAYER_WEIGHTS_FILE_NAME = "db/hidden_layer_weights.csv";
        std::string OUTPUT_LAYER_WEIGHTS_FILE_NAME = "db/output_layer_weights.csv";
        std::string HIDDEN_LAYER_BIASES_FILE_NAME = "db/hidden_layer_biases.csv";
        std::string OUTPUT_LAYER_BIASES_FILE_NAME = "db/output_layer_biases.csv";
        std::string _relativePath = "./";
        bool _extractWeightsAndBiases = false;

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
        void Save(std::vector<std::vector<double>> &, std::string fileName = "demo.csv");
        void Save(std::vector<double> &, std::string fileName = "demo.csv");
        std::vector<std::vector<double>> Read2DArray(std::string fileName = "demo.csv");
        std::vector<double> Read(std::string fileName = "demo.csv");

    public:
        NeuralNetwork();
        NeuralNetwork(int, int, int, double learningRate = 0.1, std::string relativePath = "./", bool extractWeightsAndBiases = false);
        std::vector<std::vector<double>> Normalize(std::vector<std::vector<double>> &, int, double factor = 0);
        void Train(std::vector<std::vector<double>> &trainingInputData, std::vector<std::vector<double>> &, int, int);
        std::vector<double> Predict(std::vector<double> &);
        std::string GetRelativePath();
        bool GetExtractWeightsAndBiases();
    };
}
