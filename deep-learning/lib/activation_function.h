#pragma once
#include <cmath>

namespace ANEFreeInIty
{
    class ActivationFunction
    {
    public:
        static double Sigmoid(double);
        static double SigmoidDerivation(double x);
    };
}
