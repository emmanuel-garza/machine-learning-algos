#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class DataSet
{
public:
    std::vector<int> class_val;
    std::vector<std::vector<double>> features;

    void read_cancer_data()
    {

        // Read data
        std::ifstream file("../data/cancer/wdbc.data");
        std::string line_values;

        // Set the number of rows
        /* 
        Very careful here, if we put do the resize of class_val after features,
        because we will resize features we get problems afterwards
        */
        this->class_val.resize(569);
        this->features.resize(569);

        // std::cout << this->class_val[0] << std::endl;
        int row = -1;
        while (file.good())
        {
            row++;

            // Resize the columns
            this->features[row].resize(32 - 2);

            // Read the entire line
            std::getline(file, line_values, '\n');

            // Now we read each value (constructor of stringstream)
            std::stringstream ss = std::stringstream(line_values);

            std::string line_value;

            int col = 0;
            while (std::getline(ss, line_value, ','))
            {
                // std::cout << line_value << std::endl;

                if (col == 1)
                {
                    if (line_value.compare("M") == 0)
                    {
                        this->class_val[row] = 1;
                    }
                    else
                    {
                        this->class_val[row] = 0;
                    }
                }

                if (col > 1)
                {
                    // Convert to double
                    // -> Ignore the first two columns that have the ID and the class value
                    this->features[row][col - 2] = std::stod(line_value);
                }
                col++;
            }
            // std::cout << row + 1 << " " << data.class_val[row] << std::endl;
        }
    }
};

int main()
{

    DataSet data;

    data.read_cancer_data();

    // // Read data
    // std::ifstream file("../data/cancer/wdbc.data");
    // std::string line_values;

    // // Set the number of rows
    // /*
    //     Very careful here, if we put do the resize of class_val after features,
    //     because we will resize features we get problems afterwards
    // */
    // data.class_val.resize(569);
    // data.features.resize(569);

    // // std::cout << data.class_val[0] << std::endl;
    // int row = -1;
    // while (file.good())
    // {
    //     row++;

    //     // Resize the columns
    //     data.features[row].resize(32 - 2);

    //     // Read the entire line
    //     std::getline(file, line_values, '\n');

    //     // Now we read each value (constructor of stringstream)
    //     std::stringstream ss = std::stringstream(line_values);

    //     std::string line_value;

    //     int col = 0;
    //     while (std::getline(ss, line_value, ','))
    //     {
    //         // std::cout << line_value << std::endl;

    //         if (col == 1)
    //         {
    //             if (line_value.compare("M") == 0)
    //             {
    //                 data.class_val[row] = 1;
    //             }
    //             else
    //             {
    //                 data.class_val[row] = 0;
    //             }
    //         }

    //         if (col > 1)
    //         {
    //             // Convert to double
    //             data.features[row][col - 2] = std::stod(line_value);
    //         }
    //         col++;
    //     }
    //     // std::cout << row + 1 << " " << data.class_val[row] << std::endl;
    // }

    for (int row = 0; row < data.features.size(); row++)
    {
        for (int col = 0; col < data.features[row].size(); col++)
        {
            std::cout << data.features[row][col] << ' ' << std::scientific;
        }
        std::cout << std::endl;
    }

    for (int row = 0; row < data.class_val.size(); row++)
    {
        std::cout << row + 1 << " " << data.class_val[row] << std::endl;
    }

    return 0;
}