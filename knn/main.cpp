#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // For sort
#include <math.h>

using namespace std;

// To sort in reverse
// https://www.geeksforgeeks.org/keep-track-of-previous-indexes-after-sorting-a-vector-in-c-stl/
bool sortinrev(pair<double, int> &a,
               pair<double, int> &b)
{
    return (a.first < b.first);
}

class DataSet
{
public:
    vector<int> class_val;
    vector<vector<double>> features;

    int n_features;

    void read_cancer_data()
    {

        // Read data
        ifstream file("../data/cancer/wdbc.data");
        string line_values;

        // Set the number of rows
        /* 
        Very careful here, if we put do the resize of class_val after features,
        because we will resize features we get problems afterwards
        */
        this->class_val.resize(569);
        this->features.resize(569);

        // cout << this->class_val[0] << endl;
        int row = -1;
        while (file.good())
        {
            row++;

            // Resize the columns
            this->features[row].resize(32 - 2);

            // Read the entire line
            getline(file, line_values, '\n');

            // Now we read each value (constructor of stringstream)
            stringstream ss = stringstream(line_values);

            string line_value;

            int col = 0;
            while (getline(ss, line_value, ','))
            {
                // cout << line_value << endl;

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
                    this->features[row][col - 2] = stod(line_value);
                }
                col++;
            }
            // cout << row + 1 << " " << data.class_val[row] << endl;
        }

        this->n_features = this->features[0].size();
    }

    void test_knn()
    {

        int n_neighbors = 5;

        // Predict for the values in indices 559-568
        int ind_start = 500;
        int ind_end = 568;

        // We need a vector to compute the distance for each element in the traing set (size 559)
        vector<pair<double, int>> dist_vec(ind_start);

        cout << "[" << endl;
        for (int ind_test = ind_start; ind_test <= ind_end; ind_test++)
        {
            for (int ind_train = 0; ind_train < dist_vec.size(); ind_train++)
            {

                // To keep track of the indices
                dist_vec[ind_train].first = 0.0;
                dist_vec[ind_train].second = ind_train;

                for (int ind_feat = 0; ind_feat < this->n_features; ind_feat++)
                {

                    dist_vec[ind_train].first += pow(this->features[ind_test][ind_feat] - this->features[ind_train][ind_feat], 2.0);
                }
            }

            // Sort the values
            sort(dist_vec.begin(), dist_vec.end(), sortinrev);
            // cout << dist_vec[0].first << ' ' << dist_vec[1].first << ' ' << dist_vec[2].first << endl;
            // cout << dist_vec[0].second << ' ' << dist_vec[1].second << ' ' << dist_vec[2].second << endl;

            double sum = 0.0;
            for (int ind = 0; ind < n_neighbors; ind++)
            {
                sum += class_val[dist_vec[ind].second];
            }

            if (sum < n_neighbors / 2.0)
            {
                cout << "[" << ind_test << ", " << 0 << "]," << endl;
            }
            else
            {
                cout << "[" << ind_test << ", " << 1 << "]," << endl;
            }
        }
        cout << "]" << endl;
    }
};

int main()
{

    DataSet data;

    data.read_cancer_data();
    data.test_knn();

    // for (int row = 0; row < data.features.size(); row++)
    // {
    //     for (int col = 0; col < data.features[row].size(); col++)
    //     {
    //         cout << data.features[row][col] << ' ' << scientific;
    //     }
    //     cout << endl;
    // }

    // for (int row = 0; row < data.class_val.size(); row++)
    // {
    //     cout << row + 1 << " " << data.class_val[row] << endl;
    // }

    // cout << data.features[0].size() << endl;

    return 0;
}