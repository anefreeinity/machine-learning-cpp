#include <cmath>
#include "./matrix_anefreeinity.cpp"

class ActivationFunction
{
public:
    static Matrix_ANE *Sigmoid(Matrix_ANE *matrix)
    {
        Matrix_ANE *new_matrix = new Matrix_ANE();
        for (int i = 0; i < matrix->GetRows(); i++)
        {
            std::vector<float> row;
            for (int j = 0; j < matrix->GetCols(); j++)
            {
                row.push_back(SigmoidUtil((*matrix)(i, j)));
            }
            new_matrix->Add(row);
        }
        return new_matrix;
    }

    static float Sigmoid(float z)
    {
        return SigmoidUtil(z);
    }

private:
    static float SigmoidUtil(float x)
    {
        return 1 / (1 + exp(-x));
    }
};