# include "fixationfilter/FixationFilter.hpp"

# include <vector>
# include <cmath>

namespace fixationfilter {

std::vector<std::vector<bool>> IVTFilter(
	const std::vector<double>& timestamp,
	const std::vector<bool>  & validityIn,
	const std::vector<double>& gazeX,
	const std::vector<double>& gazeY,
	const int& winX,
	const int& winY,
	const double& velocityThreshold) {
	/*
	*	Identification by Velocity Thresholding (IVT) filter for single eye.
	*
	*   Parameters
	*   ----------
	*   timestamp : vector<double>
	*       Timestamps of the gaze data, UNIX time, can be eyetracker timestamp or system timestamp
	*   validityIn : vector<bool>
	*       Validity of the gaze data, true for valid, false for invalid
	*   gazeX : vector<double>
	*       Gaze x position, in pixels, top left of screen is (0,0)
	*   gazeY : vector<double>
	*       Gaze y position, in pixels, top left of screen is (0,0)
	*   winX : int
	*       Window size in x direction, in pixels
	*   winY : int
	*       Window size in y direction, in pixels
	*   dist : int
	*       distance of eye to screen, in cm
	*   velocityThreshold : double
	*       Threshold for velocity, in pixels per second
	*
	*   Returns
	*   -------
	*   vector<isFixation, validityOut>
	*	isFixation : vector<bool>
	*		True for fixation, false for saccade or invalid
	*   validityOut : vector<bool>
	*       Validity of the fixation, true for valid, false for invalid
	*/

	// Initialize output
	std::vector<bool> isFixation(timestamp.size(), false);
	std::vector<bool> validityOut(timestamp.size(), false);
	double velocity;

	// iterate through all samples
	for (int i = 1; i < timestamp.size(); i++) { // start from 1, because we need to compare with previous sample
		// check if sample is valid
		if (!validityIn[i - 1] || !validityIn[i]) {
			// validityOut and isFixation are already initialized as false
			continue;
		}

		// calculate velocity
		velocity = sqrt(
			pow(gazeX[i] - gazeX[i - 1], 2) + pow(gazeY[i] - gazeY[i - 1], 2))
			 / (timestamp[i] - timestamp[i - 1]);

		// check if velocity is below threshold
		if (velocity < velocityThreshold) {
			isFixation[i] = true;
			validityOut[i] = true;
		}
	}

    // Return the results as a vector
    return {isFixation, validityOut};

} // function IVTFilter
} // namespace fixationfilter