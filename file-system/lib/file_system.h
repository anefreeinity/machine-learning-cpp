#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ANEFreeInIty
{
    class FileSystem
    {
    public:
        void SaveAsCSV(std::vector<std::vector<double>> &data, std::string fileName = "demo.csv");
        void SaveAsCSV(std::vector<double> &data, std::string fileName = "demo.csv");
        std::vector<std::vector<double>> Read2DDataFromCSV(std::string fileName);
        std::vector<double> ReadDataFromCSV(std::string fileName);
    };
}