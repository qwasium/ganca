# pragma once

# include <vector>
# include <cstdint>

namespace fixationfilter {

class FixationFilter{
	public:

		// input
		std::vector<double> timestampIn;
		std::vector<bool>   validityIn;
		std::vector<double> gazeVectorX;
		std::vector<double> gazeVectorY;
		std::vector<double> gazeVectorZ;
		double velocityThreshold;

		// output
		std::vector<bool> isFixation;
		std::vector<bool> validityOut;
		std::vector<double> velocity;
		std::vector<double> timestampOut;

		// constructor
		FixationFilter(
			const std::vector<double>& timestampInInit,
			const std::vector<bool>  & validityInInit,
			const std::vector<double>& gazeVectorXInit,
			const std::vector<double>& gazeVectorYInit,
			const std::vector<double>& gazeVectorZInit
		);

		void IVTFilter(
			double velocityThresholdIn
		);

}; // class FixationFilter
} // namespace fixationfilter