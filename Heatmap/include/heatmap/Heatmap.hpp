# pragma once

# include <cstdint>
# include <vector>

namespace heatmap{
	std::vector<std::vector<double>> heatmapGauss(
		const std::vector<double>& fixX,
		const std::vector<double>& fixY,
		const std::vector<double>& fixDuration,
		int winX,
		int winY,
		double sigma_factor);
}