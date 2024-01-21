# include "aoihit/AOIHit.hpp"

# include <string>
# include <vector>
# include <iostream>

namespace aoihit{

std::vector<bool> cntRasterAOI (std::vector<std::vector<int>> aoiMask,
                          std::vector<double> fixX,
                          std::vector<double> fixY,
                          int winX, int winY){
    /*
        Parameters
        ----------
        aoiMask : std::vector<std::vector<int>>
            2D vector of AOI mask
                - AOI     : 1
                - Non-AOI : 0
        fixX : std::vector<double>
            Vector of x coordinates of fixations, coordinate range: [0, winX - 1]
        fixY : std::vector<double>
            Vector of y coordinates of fixations, coordinate range: [0, winY - 1]
        winX : int
            Width of heatmap, count from 1
        winY : int
            Height of heatmap, count from 1

        Returns
        -------
        aoiHit : std::vector<bool>
            Vector of bools indicating whether a fixation hit an AOI

        Notes
        -----
        The input aoiMask is int for convenience.
        It should be bool, but images are often represented as int in programming.
        We usually round the value of aoiMask in Python or R anyway so it is implemented here.

        TODO: It should be divided into two functions, one for int and one for bool.
    */

    std::vector<bool> isInside(fixX.size(), false);

    // aoiMask might include gray values so round it to 0 or 1
    for (int x = 0; x < winX; x++) {
        for (int y = 0; y < winY; y++) {
            // if < 0.5, round to 0 else round to 1
            aoiMask[x][y] = aoiMask[x][y] - 0.5 > 0 ? 1 : 0;
        }
    }

    // iterate through each fixation
    for (int i = 0; i < fixX.size(); i++) {
        if (fixX[i] < 0 || fixX[i] >= winX || fixY[i] < 0 || fixY[i] >= winY) {
            // if fixation is outside heatmap, set isInside to false
            isInside[i] = false;
            continue;
        }
        // if fixation is inside AOI, set isInside to true
        isInside[i] = aoiMask[int(fixX[i])][int(fixY[i])] == 1 ? true : false;
    }

    return isInside;
}

// void freeFunction(int level) {
//     std::cout << "[" << level << "] Enter " << __func__ << "(int)" << std::endl;
//     std::cout << "[" << level << "] Exit " << __func__ << "(int)" << std::endl;
// }

// void freeFunction(int64_t level) {
//     std::cout << "[" << level << "] Enter " << __func__ << "(int64_t)" << std::endl;
//     std::cout << "[" << level << "] Exit " << __func__ << "(int64_t)" << std::endl;
// }

// void AOIHit::staticFunction(int level) {
//     std::cout << "[" << level << "] Enter " << __func__ << "(int)" << std::endl;
//     freeFunction(level + 1);
//     std::cout << "[" << level << "] Exit " << __func__ << "(int)" << std::endl;
// }

// void AOIHit::staticFunction(int64_t level) {
//     std::cout << "[" << level << "] Enter " << __func__ << "(int64_t)" << std::endl;
//     freeFunction(level + 1);
//     std::cout << "[" << level << "] Exit " << __func__ << "(int64_t)" << std::endl;
// }

// int AOIHit::getInt() const {
//     return _intValue;
// }

// void AOIHit::setInt(int input) {
//     _intValue = input;
// }

// int64_t AOIHit::getInt64() const {
//     return _int64Value;
// }

// void AOIHit::setInt64(int64_t input) {
//     _int64Value = input;
// }

// std::string AOIHit::operator()() const {
//     return std::string{"\"AOIHit\":{\"int\":"} + std::to_string(_intValue) +
//             ",\"int64\":" + std::to_string(_int64Value) + "}";
// }
} // namespace aoihit