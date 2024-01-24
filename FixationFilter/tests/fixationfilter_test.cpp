# include <catch2/catch_test_macros.hpp>
# include <iostream>
# include <numeric>
# include <string>

# include <fixationfilter/FixationFilter.hpp>

namespace fixationfilter {
TEST_CASE("FixationFilter IVTFilter Test", "[FixationFilter]") {
    // Test data
    std::vector<double> timestampIn = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<bool> validityIn = {true, true, true, true, true};
    std::vector<double> gazeVectorX = {1.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<double> gazeVectorY = {0.0, 1.0, 0.0, 0.0, 0.0};
    std::vector<double> gazeVectorZ = {0.0, 0.0, 1.0, 0.0, 0.0};

    // Create FixationFilter instance
    fixationfilter::FixationFilter fixationFilter(timestampIn, validityIn, gazeVectorX, gazeVectorY, gazeVectorZ);

    // Call IVTFilter
    fixationFilter.IVTFilter(1.0);

    // Check the results
    REQUIRE(fixationFilter.isFixation.size() == timestampIn.size() - 1);
    REQUIRE(fixationFilter.validityOut.size() == timestampIn.size() - 1);
    REQUIRE(fixationFilter.velocity.size() == timestampIn.size() - 1);

    // // Assuming your data should result in all fixations, modify as needed
    // for (size_t i = 0; i < timestampIn.size() - 1; ++i) {
    //     REQUIRE(fixationFilter.isFixation[i]);
    //     REQUIRE(fixationFilter.validityOut[i]);
    // }
}
} // namespace fixationfilter