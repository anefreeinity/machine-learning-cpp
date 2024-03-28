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
