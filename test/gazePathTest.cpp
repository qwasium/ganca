# include <gazePath.hpp> // src
# include <csv.hpp> // git submodule csv-parser

# include <iostream>
# include <vector>


int main(){

    // create CSV Reader object
    // csv::CSVReader reader("../test_data/aka_fixation.csv");
    csv::CSVReader reader("../test_data/midori_fixation.csv");

    // input image path
    std::string inFilePath = "../test_data/bgImg.png";

    // output image path
    std::string outFilePath = "../test_data/midori_gazePath.png";

    // get fixation data
    std::vector<double> fixX;
    std::vector<double> fixY;
    std::vector<double> fixDuration;
    std::vector<double> fixStart
    std::vector<double> fixEnd;

    for (auto& row : reader) {
        // Convert string to double and store in vectors
        fixX.push_back(row["XPos"].get<double>());
        fixY.push_back(row["YPos"].get<double>());
        fixDuration.push_back(row["FixDur"].get<double>());
        fixStart.push_back(row["FixStart"].get<double>());
        fixEnd.push_back(row["FixEnd"].get<double>());
    }

    // plot gaze path
    exitCode = plotGazePath(inFilePath, outFilePath);

    // print exit code
    std::cout << "Exit code: " << exitCode << std::endl;

}