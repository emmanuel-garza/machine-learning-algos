#include <iostream>
#include <vector>
#include <fstream>

class Point
{
public:
    std::vector<std::vector<double>> features;

    std::vector<int> class_val;
};

int main()
{
    std::cout << "Hello world!" << std::endl;

    Point point;

    point.features = {{1, 2, 3}};

    std::cout << point.features[0][1] << std::endl;

    // Read data
    std::ifstream file("../data/cancer/wdbc.data");

    std::string value;

    while (file.good())
    {
        std::getline(file, value, ',');
        if (value.compare("\n")==0)
            std::cout << 'a' << std::endl;
        std::cout << value << std::endl;
    }

    return 0;
}