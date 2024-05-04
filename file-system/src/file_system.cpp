#include "../lib/file_system.h"

void ANEFreeInIty::FileSystem::SaveAsCSV(std::vector<std::vector<double>> &data, std::string fileName)
{
    std::cout << "saving...\n";
    std::ofstream outfile(fileName);

    for (const auto &row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            outfile << row[i];
            if (i != row.size() - 1)
            {
                outfile << ",";
            }
        }
        outfile << "\n";
    }

    outfile.close();
    std::cout << "data saved to " << fileName << std::endl;
}

void ANEFreeInIty::FileSystem::SaveAsCSV(std::vector<double> &data, std::string fileName)
{
    std::cout << "saving...\n";
    std::ofstream outfile(fileName);

    for (const auto &row : data)
    {
        outfile << row << "\n";
    }

    outfile.close();
    std::cout << "data saved to " << fileName << std::endl;
}

std::vector<std::vector<double>> ANEFreeInIty::FileSystem::Read2DDataFromCSV(std::string fileName)
{
    std::cout << "Reading data from " << fileName << std::endl;
    std::vector<std::vector<double>> data;
    std::ifstream infile(fileName);

    std::string line;
    while (std::getline(infile, line))
    {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            try
            {
                double value = std::stod(cell);
                row.push_back(value);
            }
            catch (...)
            {
                std::cerr << "Error parsing cell: " << cell << std::endl;
            }
        }
        data.push_back(row);
    }

    infile.close();
    std::cout << "completed reading data from " << fileName << std::endl;

    return data;
}

std::vector<double> ANEFreeInIty::FileSystem::ReadDataFromCSV(std::string fileName)
{
    std::cout << "Reading data from " << fileName << std::endl;
    std::vector<double> data;
    std::ifstream infile(fileName);
    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            data.push_back(std::stod(cell));
        }
    }

    infile.close();
    std::cout << "completed reading data from " << fileName << std::endl;

    return data;
}