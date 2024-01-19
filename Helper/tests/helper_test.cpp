#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <vector>
#include <cmath> // for std::abs, to compare floating-point numbers

#include <helper/Helper.hpp>

namespace helper {

TEST_CASE("displayAreaToPixels Test", "[helper]") {
    SECTION("Conversion for Single Coordinate") {
        std::vector<double> coordsAbs = {0.25}; // Example coordinate between 0 and 1
        int resolution = 1080; // Example resolution (1080p)

        std::vector<double> result = displayAreaToPixels(coordsAbs, resolution);

        REQUIRE(result.size() == 1); // Ensure the size of the result vector is as expected

        // Calculate the expected result based on the formula in displayAreaToPixels
        double expectedValue = coordsAbs[0] * resolution;

        // Check that the result is approximately equal to the expected value
        REQUIRE(Catch::Approx(result[0]).epsilon(1e-6) == expectedValue);
    }

    SECTION("Conversion for Multiple Coordinates") {
        std::vector<double> coordsAbs = {0.1, 0.5, 0.9}; // Example coordinates between 0 and 1
        int resolution = 720; // Example resolution (720p)

        std::vector<double> result = displayAreaToPixels(coordsAbs, resolution);

        REQUIRE(result.size() == 3); // Ensure the size of the result vector is as expected

        // Calculate the expected results based on the formula in displayAreaToPixels
        std::vector<double> expectedValues;
        for (const auto& coord : coordsAbs) {
            expectedValues.push_back(coord * resolution);
        }

        // Check that each result is approximately equal to the corresponding expected value
        for (int i = 0; i < result.size(); ++i) {
            REQUIRE(Catch::Approx(result[i]).epsilon(1e-6) == expectedValues[i]);
        }
    }

    // Add more test cases as needed to cover different scenarios
}

} // namespace helper