#include "../lib/hand_written_digit_tranning_model.h"

ANEFreeInIty::HandWrittenDigitTrainingModel::HandWrittenDigitTrainingModel() {}

ANEFreeInIty::HandWrittenDigitTrainingModel::HandWrittenDigitTrainingModel(NeuralNetwork network, int trainingDataSetSize, int testDataSetSize, bool isLittleEndian)
{
    _network = network;
    _trainingDataSetSize = MAX_TRAINING_DATA_SIZE;
    _testDataSetSize = MAX_TEST_DATA_SIZE;
    _isLittleEndian = isLittleEndian;

    if (trainingDataSetSize < MAX_TRAINING_DATA_SIZE)
    {
        _trainingDataSetSize = trainingDataSetSize;
    }

    if (testDataSetSize < MAX_TEST_DATA_SIZE)
    {
        _testDataSetSize = testDataSetSize;
    }

    LoadData();
}

std::vector<double> ANEFreeInIty::HandWrittenDigitTrainingModel::ConvertCharVectorToDoubleVectorAndNormalize(std::vector<unsigned char> &imageChar, int max)
{
    if (imageChar.size() == 0)
    {
        return {};
    }

    std::vector<double> imageDouble;
    for (auto pixel : imageChar)
    {
        imageDouble.push_back(double(pixel) / max);
    }
    return imageDouble;
}

int ANEFreeInIty::HandWrittenDigitTrainingModel::reverseInt(int value)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = value & 255;
    ch2 = (value >> 8) & 255;
    ch3 = (value >> 16) & 255;
    ch4 = (value >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

std::vector<std::vector<double>> ANEFreeInIty::HandWrittenDigitTrainingModel::ReadMnistImages(std::string fileName, int noOfImages)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file: '" << fileName << "'" << std::endl;
        std::cout << "Exiting program..." << std::endl;
        exit(1);
    }

    int magicNumber, totalNumOfImages, rows, cols;
    file.read(reinterpret_cast<char *>(&magicNumber), sizeof(magicNumber));
    file.read(reinterpret_cast<char *>(&totalNumOfImages), sizeof(totalNumOfImages));
    file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    file.read(reinterpret_cast<char *>(&cols), sizeof(cols));

    if (_isLittleEndian)
    {
        magicNumber = reverseInt(magicNumber);
        totalNumOfImages = reverseInt(totalNumOfImages);
        rows = reverseInt(rows);
        cols = reverseInt(cols);
    }

    if (magicNumber != MAGIC_NUMBER_FOR_DATASET_IMAGE)
    {
        std::cout << "Error: Magic number is incorrect. File: '" << fileName << "', try with " << (_isLittleEndian ? "Big-Endian" : "Little-Endian") << std::endl;
        std::cout << "Exiting program..." << std::endl;
        exit(1);
    }

    std::cout << "Magic number: " << magicNumber << std::endl;
    std::cout << "Number of images: " << totalNumOfImages << std::endl;
    std::cout << "Image dimensions: " << int(rows) << "x" << int(cols) << std::endl;

    std::vector<std::vector<double>> images;
    for (int i = 0; i < totalNumOfImages && i < noOfImages; i++)
    {
        std::vector<unsigned char> image(rows * cols);
        file.read(reinterpret_cast<char *>(image.data()), rows * cols);
        images.push_back(ConvertCharVectorToDoubleVectorAndNormalize(image, IMAGE_GRAY_SCALE_MAX_VALUE));
    }

    file.close();
    return images;
}

std::vector<double> ANEFreeInIty::HandWrittenDigitTrainingModel::ReadMnistLabels(std::string fileName, int noOfLabels)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file: '" << fileName << "'" << std::endl;
        std::cout << "Exiting program..." << std::endl;
        exit(1);
    }

    int magicNumber, totalNumOfLabels;
    file.read(reinterpret_cast<char *>(&magicNumber), sizeof(magicNumber));
    file.read(reinterpret_cast<char *>(&totalNumOfLabels), sizeof(totalNumOfLabels));

    if (_isLittleEndian)
    {
        magicNumber = reverseInt(magicNumber);
        totalNumOfLabels = reverseInt(totalNumOfLabels);
    }

    if (magicNumber != MAGIC_NUMBER_FOR_DATASET_LABEL)
    {
        std::cout << "Error: Magic number is incorrect. File: '" << fileName << "', try with " << (_isLittleEndian ? "Big-Endian" : "Little-Endian") << std::endl;
        std::cout << "Exiting program..." << std::endl;
        exit(1);
    }

    std::cout << "Magic number: " << magicNumber << std::endl;
    std::cout << "Number of labels: " << totalNumOfLabels << std::endl;

    int bufferLength = totalNumOfLabels > noOfLabels ? noOfLabels : totalNumOfLabels;
    std::vector<unsigned char> labels(bufferLength);
    file.read(reinterpret_cast<char *>(labels.data()), bufferLength);

    file.close();
    return ConvertCharVectorToDoubleVectorAndNormalize(labels, 1);
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::Verify(int index, bool isTraining)
{
    std::vector<std::vector<double>> &images = isTraining ? _trainingImages : _testImages;

    for (int i = 0; i < TOTAL_PIXELS; i++)
    {
        if (images[index][i] == 0)
        {
            std::cout << "  ";
        }
        else
        {
            std::cout << "**";
        }

        if ((i + 1) % PIXEL_ROWS_AND_COLS == 0)
        {
            std::cout << std::endl;
        }
    }

    double num = isTraining ? _trainingLabels[index] : _testLabels[index];
    std::cout << "Label: " << int(num) << std::endl;
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::DisplayImageData(std::vector<std::vector<double>> &images)
{
    for (std::vector<double> image : images)
    {
        for (int i = 0; i < TOTAL_PIXELS; i++)
        {
            std::cout << image[i] << std::endl;
        }
        break;
    }
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::DisplayLabels(std::vector<double> &labels)
{
    for (auto label : labels)
    {
        std::cout << label << std::endl;
    }
}

std::vector<double> ANEFreeInIty::HandWrittenDigitTrainingModel::MakeOutPutLabelVector(int digit)
{
    std::vector<double> output(OUTPUT_LAYER_LENGTH, 0.0);
    output[digit] = 1;
    return output;
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::LoadData()
{
    std::cout << "Selected Endianness: " << (_isLittleEndian ? "Little-Endian" : "Big-Endian") << std::endl;
    std::cout << "Reading training images.....\n";
    _trainingImages = ReadMnistImages(MNIST_DATASET_PATH + MNIST_TRAINING_IMAGE_FILE_NAME, _trainingDataSetSize);
    std::cout << "No of Images fetched: " << _trainingImages.size() << std::endl;
    std::cout << "No Of Pixels: " << _trainingImages[0].size() << std::endl;
    std::cout << "------------------------------------------------------------\n";

    std::cout << "Reading training labels.....\n";
    _trainingLabels = ReadMnistLabels(MNIST_DATASET_PATH + MNIST_TRAINING_LABEL_FILE_NAME, _trainingDataSetSize);
    std::cout << "No of Labels fetched: " << _trainingLabels.size() << std::endl;
    std::cout << "------------------------------------------------------------\n";

    std::cout << "Reading test images.....\n";
    _testImages = ReadMnistImages(MNIST_DATASET_PATH + MNIST_TEST_IMAGE_FILE_NAME, _testDataSetSize);
    std::cout << "No of Images fetched: " << _testImages.size() << std::endl;
    std::cout << "No Of Pixels: " << _testImages[0].size() << std::endl;
    std::cout << "------------------------------------------------------------\n";

    std::cout << "Reading test labels.....\n";
    _testLabels = ReadMnistLabels(MNIST_DATASET_PATH + MNIST_TEST_LABEL_FILE_NAME, _testDataSetSize);
    std::cout << "No of Labels fetched: " << _testLabels.size() << std::endl;
    std::cout << "------------------------------------------------------------\n";
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::TrainDataSet(int epochs, int batchSize)
{
    std::cout << "Training Network.....\n";
    std::vector<std::vector<double>> outputs;

    for (double label : _trainingLabels)
    {
        outputs.push_back(MakeOutPutLabelVector(label));
    }

    _network.Train(_trainingImages, outputs, epochs, batchSize);
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::PredictDigit()
{
    for (int i = 0; i < _testImages.size(); i++)
    {
        std::vector<double> predictedDigit = _network.Predict(_testImages[i]);
        std::cout << "Predicted Digit is: " << std::endl;
        for (int i = 0; i < OUTPUT_LAYER_LENGTH; i++)
        {
            std::cout << i << " : " << predictedDigit[i] << std::endl;
        }
        Verify(i, false);
    }
}

void ANEFreeInIty::HandWrittenDigitTrainingModel::TestDataSet()
{
    int accuracyCounter = 0;
    for (int i = 0; i < _testImages.size(); i++)
    {
        std::vector<double> predictedDigitBuffer = _network.Predict(_testImages[i]);
        double max = predictedDigitBuffer[0];
        int predictedDigit = 0;

        for (int j = 1; j < OUTPUT_LAYER_LENGTH; j++)
        {
            if (max < predictedDigitBuffer[j])
            {
                max = predictedDigitBuffer[j];
                predictedDigit = j;
            }
        }

        std::cout << "Label is: " << int(_testLabels[i]) << " Prediction is: " << predictedDigit << std::endl;
        if (_testLabels[i] == predictedDigit)
        {
            accuracyCounter++;
        }
    }

    std::cout << "Total Accuracy is: " << (double(accuracyCounter) / _testDataSetSize) * 100 << "%\n";
}