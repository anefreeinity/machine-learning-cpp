#include "../lib/activation_function.h"

double ANEFreeInIty::ActivationFunction::Sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double ANEFreeInIty::ActivationFunction::SigmoidDerivation(double x)
{
    return exp(-x) / pow((1 + exp(-x)), 2);
    // return x * (1 - x);
}

double ANEFreeInIty::ActivationFunction::ReLU(double x)
{
    return x > 0 ? x : 0;
}

double ANEFreeInIty::ActivationFunction::ReLUDerivation(double x)
{
    return x > 0 ? 1 : 0;
}

std::vector<double> ANEFreeInIty::ActivationFunction::SoftmaxLayer(const std::vector<double> &layerOutputs)
{
    std::vector<double> softmaxOutputs(layerOutputs.size());
    double sumExp = 0.0;
    for (double val : layerOutputs)
    {
        sumExp += exp(val);
    }
    for (size_t i = 0; i < layerOutputs.size(); ++i)
    {
        softmaxOutputs[i] = exp(layerOutputs[i]) / sumExp;
    }
    return softmaxOutputs;
}