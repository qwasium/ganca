# include <catch2/catch_test_macros.hpp>
# include <iostream>
# include <numeric>
# include <string>

# include <fixationfilter/FixationFilter.hpp>

namespace fixationfilter {
TEST_CASE("IVTFilter test", "[IVTFilter]") {
    // Test data
    std::vector<double> timestamp = {0.0, 1.0, 2.0, 3.0};
    std::vector<bool> validityIn = {true, true, true, true};
    std::vector<double> gazeX = {0.0, 0.01, 7.0, 9.0};
    std::vector<double> gazeY = {0.0, 0.01, 7.0, 9.0};
    int winX = 10;
    int winY = 10;
    double velocityThreshold = 1.0;

    // Call the IVTFilter function
    auto result = IVTFilter(timestamp, validityIn, gazeX, gazeY, winX, winY, velocityThreshold);

    // Extract the results
    std::vector<bool> isFixation = result[0];
    std::vector<bool> validityOut = result[1];

    // Check the results
    REQUIRE(isFixation.size() == timestamp.size());
    REQUIRE(validityOut.size() == timestamp.size());

    // The first sample is always false because there's no previous sample to compare with
    REQUIRE_FALSE(isFixation[0]);
    REQUIRE_FALSE(validityOut[0]);

    // The second sample should be true as the velocity is below the threshold
    REQUIRE(isFixation[1]);
    REQUIRE(validityOut[1]);

    // The remaining samples should be false as the velocity is above the threshold
    for (size_t i = 2; i < timestamp.size(); ++i) {
        REQUIRE_FALSE(isFixation[i]);
        REQUIRE_FALSE(validityOut[i]);
    }
}
} // namespace fixationfilter