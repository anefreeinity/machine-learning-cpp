#include <iomanip>
#include "./hand-written-digit/lib/hand_written_digit_tranning_model.h"
using namespace ANEFreeInIty;

int main()
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    const int inputLayerSize = 784;
    const int hiddenLayerSize = 55;
    const int outputLayerSize = 10;
    const double learningRate = 0.04;
    const int epoches = 7;
    const int batchSize = 32;
    const int tranningDataSetSize = 60000;
    const int testDataSetSize = 10000;
    const bool isLittleEndian = true;

    NeuralNetwork network(inputLayerSize, hiddenLayerSize, outputLayerSize, learningRate);
    HandWrittenDigitTranningModel model(network, tranningDataSetSize, testDataSetSize, isLittleEndian);
    model.TrainDataSet(epoches, batchSize);
    model.TestDataSet();
    // model.PredictDigit();

    return 0;
}
