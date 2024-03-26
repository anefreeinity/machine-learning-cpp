#include <vector>
#include <iostream>

class Matrix_ANE
{
private:
    std::vector<std::vector<float>> matrix;
    int rows;
    int cols;

public:
    Matrix_ANE()
    {
        rows = 0;
        cols = 0;
    }

    void Add(std::vector<float> vector)
    {
        if (rows == 0)
        {
            cols = vector.size();
            rows++;
        }
        else
        {
            rows++;
        }
        matrix.push_back(vector);
    }

    std::vector<std::vector<float>> GetMatrix() { return matrix; }
    int GetRows() { return rows; }
    int GetCols() { return cols; }

    void DisplayMatrix()
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    float &operator()(int r, int c) { return matrix[r][c]; }
};