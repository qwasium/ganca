# include "heatmap/Heatmap.hpp"

# include <string>
# include <vector>
# include <cmath>

namespace heatmap{

// swig will ignore const, check docs 5.2.4
std::vector<std::vector<double>> heatmapGauss(
    const std::vector<double>& fixX,
    const std::vector<double>& fixY,
    const std::vector<double>& fixDuration,
    int& winX, int& winY, double sigma_factor = 1) {
    /*
    Create heatmap matrix

    Parameters
    ----------
    fixX : std::vector<double>
        Vector of x coordinates of fixations
    fixY : std::vector<double>
        Vector of y coordinates of fixations
    fixDuration : std::vector<double>
        Vector of durations of fixations
        To implement kernel density estimation, input a vector with equal values
    winX : int
        Width of heatmap
    winY : int
        Height of heatmap
    sigma_factor : double
        Factor to calculate sigma of Gaussian

    Returns
    -------
    heatmap : std::vector<std::vector<double>>
        2D vector of heatmap

    Notes
    -----
    The return value will depend on the fixation duration.
    Make sure to report the fixation duration and keep it consistant.
    Technically, eye tracking data is not i.i.d. and the Gaussian kernel is not appropriate.
    Thus, this function is for visualization purposes only unless careful examination is done.

    */

    // Initialize 2D vector with dimensions winX x winY and fill with zeros
    std::vector<std::vector<double>> heatmap(winX, std::vector<double>(winY, 0));

    // Fill heatmapLayers with Gaussians
    for (int i = 0; i < fixX.size(); i++) {

        // Calculate sd
        double sigma = fixDuration[i] / sigma_factor;

        // iterate through each pixel
        for (double x = 0; x < winX; x++) {
            for (double y = 0; y < winY; y++) {

                // Calculate distance from fixation to current pixel
                double dist = std::sqrt(std::pow(x - fixX[i], 2) + std::pow(y - fixY[i], 2));

                // Add value of Gaussian to heatmap
                heatmap[x][y] +=
                    std::exp(- std::pow(dist, 2) / (2 * std::pow(sigma, 2))) / (sigma * sqrt(2 * M_PI ));
            }
        }
    }

    // take an average of the layers/fixations
    for (int x = 0; x < winX; x++) {
        for (int y = 0; y < winY; y++) {
            heatmap[x][y] /= fixX.size();
        }
    }

    return heatmap;
} // heatmapGauss()
} // namespace heatmap