#include "../lib/hand_written_digit_tranning_model.h"

std::vector<double> ANEFreeInIty::HandWrittenDigitTranningModel::ConvertCharVectorToDoubleVectorAndNormalize(std::vector<unsigned char> &imageChar, int max)
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

int ANEFreeInIty::HandWrittenDigitTranningModel::reverseInt(int value)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = value & 255;
    ch2 = (value >> 8) & 255;
    ch3 = (value >> 16) & 255;
    ch4 = (value >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

std::vector<std::vector<double>> ANEFreeInIty::HandWrittenDigitTranningModel::ReadMnistIimages(std::string filename, int noOfImages)
{
    std::cout << "------------------------------------------------------------\n";
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return {};
    }

    int magic_number, num_images, rows, cols;
    file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    magic_number = reverseInt(magic_number); // If endianness is different
    file.read(reinterpret_cast<char *>(&num_images), sizeof(num_images));
    num_images = reverseInt(num_images);
    file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    rows = reverseInt(rows);
    file.read(reinterpret_cast<char *>(&cols), sizeof(cols));
    cols = reverseInt(cols);

    std::cout << "Magic number: " << magic_number << std::endl;
    std::cout << "Number of images: " << num_images << std::endl;
    std::cout << "Image dimensions: " << int(rows) << "x" << int(cols) << std::endl;

    std::vector<std::vector<double>> images;
    for (int i = 0; i < num_images && i < noOfImages; ++i)
    {
        std::vector<unsigned char> image(rows * cols);
        file.read(reinterpret_cast<char *>(image.data()), rows * cols);
        images.push_back(ConvertCharVectorToDoubleVectorAndNormalize(image, IMAGE_GRAY_SCALE_MAX_VALUE));
    }

    file.close();
    return images;
}

std::vector<double> ANEFreeInIty::HandWrittenDigitTranningModel::ReadMnistLabels(std::string filename, int noOfLabels)
{
    std::cout << "------------------------------------------------------------\n";
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return {};
    }

    int magic_number, num_labels;
    file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    magic_number = reverseInt(magic_number);
    file.read(reinterpret_cast<char *>(&num_labels), sizeof(num_labels));
    num_labels = reverseInt(num_labels);

    std::cout << "Magic number: " << magic_number << std::endl;
    std::cout << "Number of labels: " << num_labels << std::endl;

    int bufferLength = num_labels > noOfLabels ? noOfLabels : num_labels;
    std::vector<unsigned char> labels(bufferLength);
    file.read(reinterpret_cast<char *>(labels.data()), bufferLength);

    file.close();
    return ConvertCharVectorToDoubleVectorAndNormalize(labels, 1);
}

void ANEFreeInIty::HandWrittenDigitTranningModel::Verify(int index, bool isTranning)
{
    std::vector<std::vector<double>> &images = isTranning ? _tranningImages : _testImages;

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

    double num = isTranning ? _tranningLabels[index] : _testLabels[index];
    std::cout << "Label: " << num << std::endl;
}

void ANEFreeInIty::HandWrittenDigitTranningModel::DisplayImageData(std::vector<std::vector<double>> &images)
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

void ANEFreeInIty::HandWrittenDigitTranningModel::DisplayLabels(std::vector<double> &labels)
{
    for (auto label : labels)
    {
        std::cout << label << std::endl;
    }
}

std::vector<double> ANEFreeInIty::HandWrittenDigitTranningModel::MakeOutPutLabelVector(int digit)
{
    std::vector<double> output(OUTPUT_LAYER_LENGTH, 0.0);
    output[digit] = 1;
    return output;
}

void ANEFreeInIty::HandWrittenDigitTranningModel::LoadData()
{
    // std::string mnist_path = "./hand-written-digit/mnist-binary/";
    //  std::string mnist_path = "../mnist/";

    _tranningImages = ReadMnistIimages(MNIST_DATASET_PATH + MNIST_TRANNING_IMAGE_FILE_NAME, _traningDataSetSize);
    std::cout << "No of Images: " << _tranningImages.size() << std::endl;
    std::cout << "No Of Pixels: " << _tranningImages[0].size() << std::endl;
    // DisplayImageData(_tranningImages);

    _tranningLabels = ReadMnistLabels(MNIST_DATASET_PATH + MNIST_TRANNING_LABEL_FILE_NAME, _traningDataSetSize);
    std::cout << "No of Labels: " << _tranningLabels.size() << std::endl;
    // DisplayLabels(_tranningLabels);

    _testImages = ReadMnistIimages(MNIST_DATASET_PATH + MNIST_TEST_IMAGE_FILE_NAME, _testDataSetSize);
    std::cout << "No of Images: " << _testImages.size() << std::endl;
    std::cout << "No Of Pixels: " << _testImages[0].size() << std::endl;
    // DisplayImageData(_testImages);

    _testLabels = ReadMnistLabels(MNIST_DATASET_PATH + MNIST_TEST_LABEL_FILE_NAME, _testDataSetSize);
    std::cout << "No of Labels: " << _testLabels.size() << std::endl;
    // DisplayLabels(_testLabels);

    // Verify(1);
    // Verify(1, false);
}

ANEFreeInIty::HandWrittenDigitTranningModel::HandWrittenDigitTranningModel() {}

ANEFreeInIty::HandWrittenDigitTranningModel::HandWrittenDigitTranningModel(NeuralNetwork network, int tranningDataSetSize, int testDataSetSize)
{
    _network = network;
    _traningDataSetSize = MAX_TRANNING_DATA_SIZE;
    _testDataSetSize = MAX_TEST_DATA_SIZE;

    if (tranningDataSetSize < MAX_TRANNING_DATA_SIZE)
    {
        _traningDataSetSize = tranningDataSetSize;
    }

    if (testDataSetSize < MAX_TEST_DATA_SIZE)
    {
        _testDataSetSize = testDataSetSize;
    }

    LoadData();
}

void ANEFreeInIty::HandWrittenDigitTranningModel::TrainDataSet(int epoches)
{
    std::vector<std::vector<double>> outputs;

    for (double label : _tranningLabels)
    {
        outputs.push_back(MakeOutPutLabelVector(label));
    }

    _network.Train(_tranningImages, outputs, epoches);
}

void ANEFreeInIty::HandWrittenDigitTranningModel::PredictDigit()
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

void ANEFreeInIty::HandWrittenDigitTranningModel::TestDataSet()
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

        std::cout << "Label is: " << _testLabels[i] << " Prediction is: " << predictedDigit << std::endl;
        if (_testLabels[i] == predictedDigit)
        {
            accuracyCounter++;
        }
    }

    std::cout << "Total accuracy is: " << (double(accuracyCounter) / _testDataSetSize) * 100 << "%\n";
}