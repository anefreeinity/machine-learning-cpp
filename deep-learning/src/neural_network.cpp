#include "../lib/neural_network.h"

double ANEFreeInIty::NeuralNetwork::GetNormalizedRandom()
{
    return rand() / double(RAND_MAX);
}

ANEFreeInIty::NeuralNetwork::NeuralNetwork() {}

ANEFreeInIty::NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayerSize, int outputLayerSize, double learningRate)
{
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));
    _inputLayerSize = inputLayerSize;
    _hiddenLayerSize = hiddenLayerSize;
    _outputLayerSize = outputLayerSize;

    _learningRate = learningRate;

    _hiddenLayerWeights.resize(_inputLayerSize, std::vector<double>(_hiddenLayerSize, 0.0));
    _outputLayerWeights.resize(_hiddenLayerSize, std::vector<double>(_outputLayerSize, 0.0));

    _hiddenLayerBiases.resize(_hiddenLayerSize, 0.0);
    _outputLayerBiases.resize(_outputLayerSize, 0.0);

    _hiddenLayerCalculatedOutput.resize(_hiddenLayerSize, 0.0);
    _outputLayerCalculatedOutput.resize(_outputLayerSize, 0.0);

    for (int i = 0; i < _inputLayerSize; i++)
    {
        for (int j = 0; j < _hiddenLayerSize; j++)
        {
            _hiddenLayerWeights[i][j] = GetNormalizedRandom();
        }
    }

    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        for (int j = 0; j < _outputLayerSize; j++)
        {
            _outputLayerWeights[i][j] = GetNormalizedRandom();
        }
    }

    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        _hiddenLayerBiases[i] = GetNormalizedRandom();
    }

    for (int i = 0; i < _outputLayerSize; i++)
    {
        _outputLayerBiases[i] = GetNormalizedRandom();
    }
}

std::vector<double> ANEFreeInIty::NeuralNetwork::Forward(std::vector<double> &input)
{
    _hiddenLayerCalculatedOutput.resize(_hiddenLayerSize, 0.0);
    _outputLayerCalculatedOutput.resize(_outputLayerSize, 0.0);

    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        double z1 = 0;
        for (int j = 0; j < _inputLayerSize; j++)
        {
            z1 += input[j] * _hiddenLayerWeights[j][i];
        }
        _hiddenLayerCalculatedOutput[i] = ActivationFunction::Sigmoid(z1 + _hiddenLayerBiases[i]);
    }

    for (int i = 0; i < _outputLayerSize; i++)
    {
        double z2 = 0;
        for (int j = 0; j < _hiddenLayerSize; j++)
        {
            z2 += _hiddenLayerCalculatedOutput[j] * _outputLayerWeights[j][i];
        }
        _outputLayerCalculatedOutput[i] = ActivationFunction::Sigmoid(z2 + _outputLayerBiases[i]);
    }

    return _outputLayerCalculatedOutput;
}

void ANEFreeInIty::NeuralNetwork::BackPropagate(std::vector<double> &input, std::vector<double> &target)
{
    Forward(input);

    std::vector<double> outputLayerErrors(_outputLayerSize, 0.0);
    for (int i = 0; i < _outputLayerSize; i++)
    {
        outputLayerErrors[i] = 2 * (_outputLayerCalculatedOutput[i] - target[i]) * ActivationFunction::SigmoidDerivation(_outputLayerCalculatedOutput[i]);
    }

    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        for (int j = 0; j < _outputLayerSize; j++)
        {
            _outputLayerWeights[i][j] -= _learningRate * _hiddenLayerCalculatedOutput[i] * outputLayerErrors[j];
        }
    }

    for (int i = 0; i < _outputLayerSize; i++)
    {
        _outputLayerBiases[i] -= _learningRate * outputLayerErrors[i];
    }

    std::vector<double> hiddenLayerErrors(_hiddenLayerSize, 0.0);
    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < _outputLayerSize; j++)
        {
            sum += outputLayerErrors[j] * _outputLayerWeights[i][j];
        }
        hiddenLayerErrors[i] = sum * ActivationFunction::SigmoidDerivation(_hiddenLayerCalculatedOutput[i]);
    }

    for (int i = 0; i < _inputLayerSize; i++)
    {
        for (int j = 0; j < _hiddenLayerSize; j++)
        {
            _hiddenLayerWeights[i][j] -= _learningRate * input[i] * hiddenLayerErrors[j];
        }
    }

    for (int i = 0; i < _hiddenLayerSize; i++)
    {
        _hiddenLayerBiases[i] -= _learningRate * hiddenLayerErrors[i];
    }
}

std::vector<std::vector<double>> ANEFreeInIty::NeuralNetwork::Normalize(std::vector<std::vector<double>> &data, int layerSize, double factor)
{
    int entries = data.size();
    std::vector<double> maxCols;

    if (factor)
    {
        maxCols.push_back(factor);
    }
    else
    {
        for (int i = 0; i < layerSize; i++)
        {
            double max = data[0][i];
            for (int j = 1; j < entries; j++)
            {
                if (max < data[j][i])
                {
                    max = data[j][i];
                }
            }
            maxCols.push_back(max);
        }
    }

    std::vector<std::vector<double>> normalizedData(entries, std::vector<double>(layerSize, 0.0));

    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < layerSize; j++)
        {
            normalizedData[i][j] = data[i][j] / maxCols[j];
        }
    }

    return normalizedData;
}

void ANEFreeInIty::NeuralNetwork::Train(std::vector<std::vector<double>> &trainingInputData, std::vector<std::vector<double>> &trainingOutputData, int epoches, int batchSize)
{
    // for (int epoch = 0; epoch < epoches; epoch++)
    // {
    //     for (int i = 0; i < trainingInputData.size(); i++)
    //     {
    //         BackPropagate(trainingInputData[i], trainingOutputData[i]);
    //     }
    // }

    int tranningInputDataSize = trainingInputData.size();
    for (int epoch = 0; epoch < epoches; epoch++)
    {
        std::vector<int> indices(trainingInputData.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), std::default_random_engine());

        for (int i = 0; i < trainingInputData.size(); i += batchSize)
        {
            std::vector<std::vector<double>> batchData(batchSize);
            std::vector<std::vector<double>> batchLabels(batchSize);
            for (int j = 0; j < batchSize; j++)
            {
                int idx = indices[i + j];
                batchData[j] = trainingInputData[idx];
                batchLabels[j] = trainingOutputData[idx];
            }

            std::cout << "Tranning Network current Epoch: (" << epoch + 1 << "/" << epoches << "), current Batch: (" << ((i + 1) / batchSize) + 1 << "/" << tranningInputDataSize / batchSize << ")" << std::endl;

            for (int j = 0; j < batchSize; j++)
            {
                BackPropagate(batchData[j], batchLabels[j]);
            }
        }
    }
    std::cout << "Tranning Completed\n";
}

std::vector<double> ANEFreeInIty::NeuralNetwork::Predict(std::vector<double> &input)
{
    return Forward(input);
}