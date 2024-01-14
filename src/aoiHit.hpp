# ifndef AOIHIT_HPP
# define AOIHIT_HPP

# include <string>
# include <vector>
# include <cmath>

std::vector<bool> aoiHit (std::vector<std::vector<int>> aoiMask,
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
            Vector of x coordinates of fixations
        fixY : std::vector<double>
            Vector of y coordinates of fixations
        winX : int
            Width of heatmap
        winY : int
            Height of heatmap

        Returns
        -------
        aoiHit : std::vector<bool>
            Vector of bools indicating whether a fixation hit an AOI

        Notes
        -----
        The input aoiMask is int for convenience.
        It should be bool, but images are often represented as int in programming.
        aoiMask will use memory but, it is faster, adaptable to custom shapes, and more intuitive.

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
        // iterate through each pixel
        for (int x = 0; x < winX; x++) {
            for (int y = 0; y < winY; y++) {
                // if fixation is inside AOI, set isInside to true
                isInside[i] = aoiMask[x][y] == 1 ? true : false;
            }
        }
    }

    return isInside;
}

# endif