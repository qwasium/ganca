# include <csv.hpp> // git submodule csv-parser

# include <iostream>
# include <vector>
# include <string>
# include <cmath>

int main() {

    // initialize variables
    // csv::CSVReader reader("../test_data/aka_timeseries.csv");
    csv::CSVReader reader("../test_data/midori_timeseries.csv");
    std::vector<double> gazeLeftX;
    std::vector<double> gazeLeftY;
    std::vector<double> gazeRightX;
    std::vector<double> gazeRightY;

    // get column eyetracker_timestamp
    int rowCnt = 0;
    for (auto& row : reader) {
        if (row["validity_gaze_left"] == "1") {
            // Convert string to double and store in vectors
            gazeLeftX.push_back(row["left_gaze_in_pixel_x"].get<double>());
            gazeLeftY.push_back(row["left_gaze_in_pixel_y"].get<double>());
            gazeRightX.push_back(row["right_gaze_in_pixel_x"].get<double>());
            gazeRightY.push_back(row["right_gaze_in_pixel_y"].get<double>());
        } else {
            // Store NaN if validity is not 1
            gazeLeftX.push_back(std::nan(""));
            gazeLeftY.push_back(std::nan(""));
            gazeRightX.push_back(std::nan(""));
            gazeRightY.push_back(std::nan(""));
        }
        rowCnt++;
    }

    // Print out the first 10 elements
    for (int i = 0; i < 10; i++) {
        std::cout << "X: " << gazeLeftX[i] << " Y: " << gazeLeftY[i] << std::endl;
    }
}
