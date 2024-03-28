#include <iostream>
#include <iomanip>
#include "./deep-learning/lib/neural_network.h"
using namespace ANEFreeInIty;

int main()
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    const int inputLayerSize = 2;
    const int hiddenLayerSize = 3;
    const int outputLayerSize = 1;
    const int epoches = 10000;

    NeuralNetwork network(inputLayerSize, hiddenLayerSize, outputLayerSize);

    // traning input data consists of {{hour of sleeping, hour of studying}}
    // traning output data consists of {{score on exam}}
    std::vector<std::vector<double>> trainingInputData = {{3, 5}, {5, 1}, {10, 2}};
    std::vector<std::vector<double>> tranningOutputData = {{75}, {82}, {93}};

    trainingInputData = network.Normalize(trainingInputData, inputLayerSize);
    tranningOutputData = network.Normalize(tranningOutputData, outputLayerSize, 100);
    network.Train(trainingInputData, tranningOutputData, epoches);

    for (int i = 0; i < trainingInputData.size(); i++)
    {
        std::vector<double> output = network.Predict(trainingInputData[i]);
        std::cout << output[0] * 100 << "%" << std::endl;
    }

    return 0;
}
