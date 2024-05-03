#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../../deep-learning/lib/neural_network.h"

namespace ANEFreeInIty
{
    class HandWrittenDigitTrainingModel
    {
    private:
        const std::string MNIST_DATASET_PATH = "hand-written-digit/mnist-binary/";
        const std::string MNIST_TRAINING_IMAGE_FILE_NAME = "train-images-idx3-ubyte";
        const std::string MNIST_TRAINING_LABEL_FILE_NAME = "train-labels-idx1-ubyte";
        const std::string MNIST_TEST_IMAGE_FILE_NAME = "t10k-images-idx3-ubyte";
        const std::string MNIST_TEST_LABEL_FILE_NAME = "t10k-labels-idx1-ubyte";
        const int OUTPUT_LAYER_LENGTH = 10;
        const int IMAGE_GRAY_SCALE_MAX_VALUE = 255;
        const int MAX_OUTPUT_DIGIT = 9;
        const int PIXEL_ROWS_AND_COLS = 28;
        const int TOTAL_PIXELS = 784;
        const int MAX_TRAINING_DATA_SIZE = 60000;
        const int MAX_TEST_DATA_SIZE = 10000;
        const int MAGIC_NUMBER_FOR_DATASET_IMAGE = 2051;
        const int MAGIC_NUMBER_FOR_DATASET_LABEL = 2049;
        std::string RELATIVE_PATH = "./";

        NeuralNetwork _network;
        std::vector<std::vector<double>> _trainingImages;
        std::vector<std::vector<double>> _testImages;
        std::vector<double> _trainingLabels;
        std::vector<double> _testLabels;
        int _trainingDataSetSize;
        int _testDataSetSize;
        bool _isLittleEndian;

        std::vector<double> ConvertCharVectorToDoubleVectorAndNormalize(std::vector<unsigned char> &imageChar, int max);
        int reverseInt(int value);
        std::vector<std::vector<double>> ReadMnistImages(std::string filename, int noOfImages);
        std::vector<double> ReadMnistLabels(std::string filename, int noOfLabels);
        void Verify(int index, bool isTraining = true);
        void DisplayImageData(std::vector<std::vector<double>> &images);
        void DisplayLabels(std::vector<double> &labels);
        std::vector<double> MakeOutPutLabelVector(int digit);
        void LoadData();

    public:
        HandWrittenDigitTrainingModel();
        HandWrittenDigitTrainingModel(NeuralNetwork network, int trainingDataSetSize, int testDataSetSize, bool isLittleEndian = true);
        void TrainDataSet(int epochs, int batchSize);
        void PredictDigit();
        void TestDataSet();
        int Predict(std::vector<double> &pixels);
    };
}