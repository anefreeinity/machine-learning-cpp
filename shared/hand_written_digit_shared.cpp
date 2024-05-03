#include "../hand-written-digit/lib/hand_written_digit_tranning_model.h"
using namespace ANEFreeInIty;

int HandWrittenDigitShared(std::vector<double> &pixels)
{
    const int inputLayerSize = 784;
    const int hiddenLayerSize = 55;
    const int outputLayerSize = 10;
    const double learningRate = 0.04;
    const int epochs = 7;
    const int batchSize = 32;
    const int trainingDataSetSize = 60000;
    const int testDataSetSize = 10000;
    const bool isLittleEndian = true;
    const std::string relativePath = "../";
    bool readWeightsAndBiasesFromFile = true;

    NeuralNetwork network(inputLayerSize, hiddenLayerSize, outputLayerSize, learningRate, relativePath, readWeightsAndBiasesFromFile);
    HandWrittenDigitTrainingModel model(network, trainingDataSetSize, testDataSetSize, isLittleEndian);
    return model.Predict(pixels);
}

extern "C"
{
    int HandWrittenDigitShared_C(int *pixels, int length)
    {
        std::vector<double> pixelsVector(length, 0.0);
        for (int i = 0; i < length; i++)
        {
            pixelsVector[i] = (double)pixels[i] / 255;
        }

        if (pixelsVector.size() == 784)
        {
            return HandWrittenDigitShared(pixelsVector);
        }
        return -1;
    }
}

// g++ -c -fPIC *.cpp -std=c++11
// g++ -c -fPIC ../deep-learning/src/*.cpp -std=c++11
// g++ -c -fPIC ../hand-written-digit/src/hand_written_digit_tranning_model.cpp -std=c++11

// g++ -dynamiclib -o hand_written_digit_lib.dylib *.o

// for linux
// g++ -shared -o shared.so *.o