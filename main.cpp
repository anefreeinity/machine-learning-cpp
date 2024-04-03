#include <iomanip>
#include "./hand-written-digit/lib/hand_written_digit_tranning_model.h"
using namespace ANEFreeInIty;

int main()
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    const int inputLayerSize = 784;
    const int hiddenLayerSize = 12;
    const int outputLayerSize = 10;
    const int epoches = 7;
    const int tranningDataSetSize = 60000;
    const int testDataSetSize = 10000;

    NeuralNetwork network(inputLayerSize, hiddenLayerSize, outputLayerSize);
    HandWrittenDigitTranningModel model(network, tranningDataSetSize, testDataSetSize);
    model.TrainDataSet(epoches);
    model.TestDataSet();
    // model.PredictDigit();

    return 0;
}
