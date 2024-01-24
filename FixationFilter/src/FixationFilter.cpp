# include "fixationfilter/FixationFilter.hpp"

# include <vector>
# include <cmath>

namespace fixationfilter {
/*
*	Identification by Velocity Thresholding (IVT) filter for single eye.
*
*   Attributes
*   ----------
*   timestamp : vector<double>
*       Timestamps of the gaze data, UNIX time, can be eyetracker timestamp or system timestamp
*   validityIn : vector<bool>
*       Validity of the gaze data, true for valid, false for invalid
*   gazeVectorX : vector<double>
*       Gaze vector x
*   gazeVectorY : vector<double>
*       Gaze vector y
*   gazeVectorZ : vector<double>
*       Gaze vector z
*   velocityThreshold : double
*       Threshold for velocity, in degrees per second
*       Tobii I-VT sets 30 deg/s for screen based eye tracker, 100 deg/s for head mounted eye tracker
*	isFixation : vector<bool>
*		True for fixation, false for saccade or invalid
*   validityOut : vector<bool>
*       Validity of the fixation, true for valid, false for invalid
*   velocity : vector<double>
*       Velocity of the gaze data, in degrees per second
*   timestampOut : vector<double>
*       Timestamps of the fixations, depends on timestampIn
*/

// constructor
FixationFilter::FixationFilter(
	const std::vector<double>& timestampInInit,
	const std::vector<bool>  & validityInInit,
	const std::vector<double>& gazeVectorXInit,
	const std::vector<double>& gazeVectorYInit,
	const std::vector<double>& gazeVectorZInit
) : timestampIn(timestampInInit),
	validityIn(validityInInit),
	gazeVectorX(gazeVectorXInit),
	gazeVectorY(gazeVectorYInit),
	gazeVectorZ(gazeVectorZInit){}

// IVT filter
void FixationFilter::IVTFilter(
	double velocityThresholdIn
){
	/*
	Identification by Velocity Thresholding (IVT) filter for single eye.

	Parameters
	----------
	velocityThresholdIn : double
		Threshold for velocity, in pixels per second.
		Sets attribute velocityThreshold.

	Notes
	-----
	Output will be stored in attributes isFixation and validityOut.

	*/

	// initialize
	velocityThreshold = velocityThresholdIn;
	isFixation.resize(timestampIn.size()-1, false);
	validityOut.resize(timestampIn.size()-1, false);
	timestampOut.resize(timestampIn.size()-1, 0);
	velocity.resize(timestampIn.size()-1, 0);

	// iterate through all samples
	// output index [i] is between input index [i] and [i+1].
	// order in time: timestampIn[i] -> timestampOut[i] -> timestampIn[i+1]
	for (size_t i = 0; i < timestampIn.size()-1; i++) { // output is shorter than input

		timestampOut[i] = ((timestampIn[i] + timestampIn[i + 1]) / 2);

		// check if sample is valid
		if (!validityIn[i] || !validityIn[i + 1]) {
			// validityOut and isFixation are already initialized as false
			continue;
		}

		// calculate velocity using dot product
		// angle = arccos( x_i * x_{i-1} + y_i * y_{i-1} + z_i * z_{i-1} / (|vector_i| + |vector_i-1|))
		// time  = timestamp_i - timestamp_{i-1}
		// velocity = angle / time
		velocity[i] = acos(
			(gazeVectorX[i] * gazeVectorX[i + 1] + gazeVectorY[i] * gazeVectorY[i + 1] + gazeVectorZ[i] * gazeVectorZ[i + 1])
			 / (sqrt(gazeVectorX[i] * gazeVectorX[i] + gazeVectorY[i] * gazeVectorY[i] + gazeVectorZ[i] * gazeVectorZ[i])
			 * sqrt(gazeVectorX[i + 1] * gazeVectorX[i + 1] + gazeVectorY[i + 1] * gazeVectorY[i + 1] + gazeVectorZ[i + 1] * gazeVectorZ[i + 1]))
		) / (timestampIn[i + 1] - timestampIn[i]);

		// check if velocity is below threshold
		if (velocity[i] < velocityThreshold) {
			isFixation[i] = true;
			validityOut[i] = true;
		}
	}
};
} // namespace fixationfilter