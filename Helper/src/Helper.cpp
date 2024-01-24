#include "helper/Helper.hpp"
#include <vector>
#include <algorithm>
#include <cmath>

namespace helper{

std::vector<double> displayAreaToPixels(std::vector<double> coordsAbs, int resolution) {
    std::vector<double> result = coordsAbs;
    for (int i = 0; i < coordsAbs.size(); ++i) {
        result[i] = coordsAbs[i] * resolution;
    }
    return result;
}
} // namespace helper