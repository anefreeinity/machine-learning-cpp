#pragma once
#include <cmath>
#include <vector>

namespace ANEFreeInIty
{
    class ActivationFunction
    {
    public:
        static double Sigmoid(double);
        static double SigmoidDerivation(double x);
        static double ReLU(double x);
        static double ReLUDerivation(double x);
        static std::vector<double> SoftmaxLayer(const std::vector<double> &layerOutputs);
    };
}
