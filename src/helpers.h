#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <iostream>

// #include <algorithm>
// #include <cmath>

// std::vector<double> displayAreaToPixels(std::vector<double> coordsAbs, int resolution) {
//     std::transform(coordsAbs.begin(), coordsAbs.end(), coordsAbs.begin(),[resolution](double coordAbs) {
//         return coordAbs * resolution;
//     });
// }

std::vector<double> displayAreaToPixels(std::vector<double> coordsAbs, int resolution) {
    std::vector<double> result = coordsAbs;
    for (int i = 0; i < coordsAbs.size(); ++i) {
        result[i] = coordsAbs[i] * resolution;
        std::cout << result[i] << std::endl;
    }
    return result;
}

#endif // HELPERS_H