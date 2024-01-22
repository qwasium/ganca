# include <vector>
# include <cstdint>
# include <cmath>

namespace fixationfilter {

std::vector<std::vector<bool>> IVTFilter(
	const std::vector<double>& timestamp,
	const std::vector<bool>  & validityIn,
	const std::vector<double>& gazeX,
	const std::vector<double>& gazeY,
	const int& winX,
	const int& winY,
	const double& velocityThreshold);

}