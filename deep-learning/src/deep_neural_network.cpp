#include "../lib/deep_neural_network.h"

double ANEFreeInIty::DeepNeuralNetwork::GetNormalizedRandom()
{
    return rand() / double(RAND_MAX);
}

ANEFreeInIty::DeepNeuralNetwork::DeepNeuralNetwork() {}

ANEFreeInIty::DeepNeuralNetwork::DeepNeuralNetwork(int inputLayerSize, std::vector<int> hiddenLayerSizes, int outputLayerSize, double learningRate, std::string relativePath, bool extractWeightsAndBiases)
{
    _relativePath = relativePath;
    _inputLayerSize = inputLayerSize;
    _hiddenLayerSizes = hiddenLayerSizes;
    _outputLayerSize = outputLayerSize;

    _learningRate = learningRate;
    _extractWeightsAndBiases = extractWeightsAndBiases;

    for (int i = 0; i < _hiddenLayerSizes.size(); i++)
    {
        std::vector<std::vector<double>> layer;
        int row = -1;
        if (i == 0)
        {
            row = _inputLayerSize;
        }
        else
        {
            row = _hiddenLayerSizes[i - 1];
        }
        for (int j = 0; j < row; j++)
        {
            layer.push_back(std::vector<double>(_hiddenLayerSizes[i], 0.0));
        }
        _hiddenLayerWeights.push_back(layer);
    }

    for (int i = 0; i < _hiddenLayerWeights.size(); ++i)
    {
        std::cout << i + 1 << "hidden layer weight is: " << _hiddenLayerWeights[i].size() << "x" << _hiddenLayerWeights[i][0].size() << std::endl;
    }
    _outputLayerWeights.resize(_hiddenLayerSizes[_hiddenLayerSizes.size() - 1], std::vector<double>(_outputLayerSize, 0.0));

    for (int i = 0; i < _hiddenLayerSizes.size(); i++)
    {
        std::vector<double> layers;
        layers.resize(_hiddenLayerSizes[i], 0.0);
        _hiddenLayerBiases.push_back(layers);
    }
    _outputLayerBiases.resize(_outputLayerSize, 0.0);

    for (int i = 0; i < _hiddenLayerSizes.size(); i++)
    {
        _hiddenLayerCalculatedOutput.push_back(std::vector<double>(_hiddenLayerSizes[i], 0.0));
    }
    _outputLayerCalculatedOutput.resize(_outputLayerSize, 0.0);

    if (_extractWeightsAndBiases)
    {
        // _hiddenLayerWeights = _fileSystem.Read2DDataFromCSV(_relativePath + HIDDEN_LAYER_WEIGHTS_FILE_NAME);
        // _outputLayerWeights = _fileSystem.Read2DDataFromCSV(_relativePath + OUTPUT_LAYER_WEIGHTS_FILE_NAME);
        // _hiddenLayerBiases = _fileSystem.ReadDataFromCSV(_relativePath + HIDDEN_LAYER_BIASES_FILE_NAME);
        // _outputLayerBiases = _fileSystem.ReadDataFromCSV(_relativePath + OUTPUT_LAYER_BIASES_FILE_NAME);
    }
    else
    {
        for (int i = 0; i < _hiddenLayerSizes.size(); i++)
        {
            int row = -1;
            if (i == 0)
            {
                row = _inputLayerSize;
            }
            else
            {
                row = _hiddenLayerSizes[i - 1];
            }
            for (int j = 0; j < row; j++)
            {
                for (int k = 0; k < _hiddenLayerSizes[i]; k++)
                {
                    _hiddenLayerWeights[i][j][k] = GetNormalizedRandom();
                }
            }
        }

        for (int i = 0; i < _hiddenLayerSizes[_hiddenLayerSizes.size() - 1]; i++)
        {
            for (int j = 0; j < _outputLayerSize; j++)
            {
                _outputLayerWeights[i][j] = GetNormalizedRandom();
            }
        }

        for (int i = 0; i < _hiddenLayerSizes.size(); i++)
        {
            for (int j = 0; j < _hiddenLayerSizes[i]; j++)
            {
                _hiddenLayerBiases[i][j] = GetNormalizedRandom();
            }
        }

        for (int i = 0; i < _outputLayerSize; i++)
        {
            _outputLayerBiases[i] = GetNormalizedRandom();
        }
    }
}

std::vector<double> ANEFreeInIty::DeepNeuralNetwork::Forward(std::vector<double> &input)
{
    for (int i = 0; i < _hiddenLayerSizes.size(); i++)
    {
        _hiddenLayerCalculatedOutput.push_back(std::vector<double>(_hiddenLayerSizes[i], 0.0));
    }
    _outputLayerCalculatedOutput.resize(_outputLayerSize, 0.0);

    // std::cout << "stage 1\n";

    // for (int i = 0; i < _hiddenLayerSizes; i++)
    // {
    //     double z1 = 0;
    //     for (int j = 0; j < _inputLayerSize; j++)
    //     {
    //         z1 += input[j] * _hiddenLayerWeights[j][i];
    //     }
    //     _hiddenLayerCalculatedOutput[i] = ActivationFunction::Sigmoid(z1 + _hiddenLayerBiases[i]);
    // }

    for (int layer = 0; layer < _hiddenLayerSizes.size(); layer++)
    {
        for (int i = 0; i < _hiddenLayerSizes[layer]; i++)
        {
            double z1 = 0;
            int row = -1;
            if (layer == 0)
            {
                row = _inputLayerSize;
            }
            else
            {
                row = _hiddenLayerSizes[layer - 1];
            }
            for (int j = 0; j < row; j++)
            {
                z1 += input[j] * _hiddenLayerWeights[layer][j][i];
            }
            _hiddenLayerCalculatedOutput[layer][i] = ActivationFunction::Sigmoid(z1 + _hiddenLayerBiases[layer][i]);
        }
    }
    // std::cout << "stage 2\n";

    for (int i = 0; i < _outputLayerSize; i++)
    {
        double z2 = 0;
        for (int j = 0; j < _hiddenLayerSizes[_hiddenLayerSizes.size() - 1]; j++)
        {
            z2 += _hiddenLayerCalculatedOutput[_hiddenLayerCalculatedOutput.size() - 1][j] * _outputLayerWeights[j][i];
        }
        _outputLayerCalculatedOutput[i] = ActivationFunction::Sigmoid(z2 + _outputLayerBiases[i]);
    }

    return _outputLayerCalculatedOutput;
}

void ANEFreeInIty::DeepNeuralNetwork::BackPropagate(std::vector<double> &input, std::vector<double> &target)
{
    Forward(input);

    std::vector<double> outputLayerErrors(_outputLayerSize, 0.0);
    for (int i = 0; i < _outputLayerSize; i++)
    {
        outputLayerErrors[i] = 2 * (_outputLayerCalculatedOutput[i] - target[i]) * ActivationFunction::SigmoidDerivation(_outputLayerCalculatedOutput[i]);
    }

    for (int i = 0; i < _hiddenLayerSizes[_hiddenLayerSizes.size() - 1]; i++)
    {
        for (int j = 0; j < _outputLayerSize; j++)
        {
            _outputLayerWeights[i][j] -= _learningRate * _hiddenLayerCalculatedOutput[_hiddenLayerCalculatedOutput.size() - 1][i] * outputLayerErrors[j];
        }
    }

    for (int i = 0; i < _outputLayerSize; i++)
    {
        _outputLayerBiases[i] -= _learningRate * outputLayerErrors[i];
    }

    // std::vector<double> hiddenLayerErrors(_hiddenLayerSizes, 0.0);
    std::vector<std::vector<double>> hiddenLayerErrors;
    for (int i = 0; i < _hiddenLayerSizes.size(); i++)
    {
        hiddenLayerErrors.push_back(std::vector<double>(_hiddenLayerSizes[i], 0.0));
    }

    // for (int i = 0; i < _hiddenLayerSizes; i++)
    // {
    //     double sum = 0.0;
    //     for (int j = 0; j < _outputLayerSize; j++)
    //     {
    //         sum += outputLayerErrors[j] * _outputLayerWeights[i][j];
    //     }
    //     hiddenLayerErrors[i] = sum * ActivationFunction::SigmoidDerivation(_hiddenLayerCalculatedOutput[i]);
    // }

    for (int layer = _hiddenLayerSizes.size() - 1; layer >= 0; layer--)
    {
        for (int i = 0; i < _hiddenLayerSizes[layer]; i++)
        {
            double sum = 0.0;
            if (layer == _hiddenLayerSizes.size() - 1)
            {
                for (int j = 0; j < _outputLayerSize; j++)
                {
                    sum += outputLayerErrors[j] * _outputLayerWeights[i][j];
                }
            }
            else
            {
                for (int j = 0; j < _hiddenLayerSizes[layer + 1]; j++)
                {
                    sum += hiddenLayerErrors[layer][j] * _hiddenLayerWeights[layer][i][j];
                }
            }
            hiddenLayerErrors[layer][i] = sum * ActivationFunction::SigmoidDerivation(_hiddenLayerCalculatedOutput[layer][i]);
        }
    }

    for (int i = 0; i < _inputLayerSize; i++)
    {
        for (int j = 0; j < _hiddenLayerSizes[0]; j++)
        {
            _hiddenLayerWeights[0][i][j] -= _learningRate * input[i] * hiddenLayerErrors[0][j];
        }
    }

    for (int layer = 0; layer < _hiddenLayerSizes.size() - 1; layer++)
    {
        for (int i = 0; i < _hiddenLayerSizes[layer]; i++)
        {
            _hiddenLayerBiases[layer][i] -= _learningRate * hiddenLayerErrors[layer][i];
        }
    }
}

std::vector<std::vector<double>> ANEFreeInIty::DeepNeuralNetwork::Normalize(std::vector<std::vector<double>> &data, int layerSize, double factor)
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

void ANEFreeInIty::DeepNeuralNetwork::Train(std::vector<std::vector<double>> &trainingInputData, std::vector<std::vector<double>> &trainingOutputData, int epochs, int batchSize)
{
    int trainingInputDataSize = trainingInputData.size();
    for (int epoch = 0; epoch < epochs; epoch++)
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

            std::cout << "Training Network current Epoch: (" << epoch + 1 << "/" << epochs << "), current Batch: (" << ((i + 1) / batchSize) + 1 << "/" << trainingInputDataSize / batchSize << ")" << std::endl;

            for (int j = 0; j < batchSize; j++)
            {
                BackPropagate(batchData[j], batchLabels[j]);
            }
        }
    }
    std::cout << "Training Completed\n";
    // _fileSystem.SaveAsCSV(_hiddenLayerWeights, _relativePath + HIDDEN_LAYER_WEIGHTS_FILE_NAME);
    // _fileSystem.SaveAsCSV(_outputLayerWeights, _relativePath + OUTPUT_LAYER_WEIGHTS_FILE_NAME);
    // _fileSystem.SaveAsCSV(_hiddenLayerBiases, _relativePath + HIDDEN_LAYER_BIASES_FILE_NAME);
    // _fileSystem.SaveAsCSV(_outputLayerBiases, _relativePath + OUTPUT_LAYER_BIASES_FILE_NAME);
}

std::vector<double> ANEFreeInIty::DeepNeuralNetwork::Predict(std::vector<double> &input)
{
    return Forward(input);
}

std::string ANEFreeInIty::DeepNeuralNetwork::GetRelativePath()
{
    return _relativePath;
}

bool ANEFreeInIty::DeepNeuralNetwork::GetExtractWeightsAndBiases()
{
    return _extractWeightsAndBiases;
}