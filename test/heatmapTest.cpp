# include <heatmap.hpp>
# include <csv.hpp> // git submodule csv-parser

# include <iostream>
# include <vector>
# include <string>
# include <cmath>


int main(){

    // initialize variables
    // csv::CSVReader reader("../test_data/midori_fixation.csv");
    csv::CSVReader reader("../test_data/aka_fixation.csv");
    int winX = 1920;
    int winY = 1080;
    double sigma_scaler = 1;
    std::string outpath = "outdata/heatmap.csv";

    std::vector<double> fixX;
    std::vector<double> fixY;
    std::vector<double> fixDuration;

    // get fixation data
    int rowCnt = 0;
    for (auto& row : reader) {
        // Convert string to double and store in vectors
        fixX.push_back(row["XPos"].get<double>());
        fixY.push_back(row["YPos"].get<double>());
        fixDuration.push_back(row["FixDur"].get<double>());
        rowCnt++;
    }

    // test
    std::vector<std::vector<double>> heatmap = heatmapGauss(fixX, fixY, fixDuration, winX, winY, sigma_scaler);

    // export heatmap to csv
    std::ofstream heatmapFile;
    heatmapFile.open(outpath);
    for (int x = 0; x < winX; x++) {
        for (int y = 0; y < winY; y++) {
            heatmapFile << heatmap[x][y] << ",";
        }
        heatmapFile << "\n";
    }
}