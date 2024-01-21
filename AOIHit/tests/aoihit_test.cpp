#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <iostream>

#include <aoihit/AOIHit.hpp> // Replace 'your_namespace' with the actual namespace

namespace aoihit {

TEST_CASE("cntRasterAOI Test", "[aoihit]") {
    SECTION("Fixations Inside AOI") {
        // Create a small AOI mask with a fixation inside
		// 0 0 0
		// 0 1 0
		// 0 0 0
        std::vector<std::vector<int>> aoiMask{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        std::vector<double> fixX{1}; // Fixation inside AOI
        std::vector<double> fixY{1};
        int winX = 3;
        int winY = 3;

        std::vector<bool> result = cntRasterAOI(aoiMask, fixX, fixY, winX, winY);

        // Only one fixation, so the result should be true
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == true);
    }

    SECTION("Fixations Outside AOI") {
        // Create a small AOI mask with no fixations inside
		// 0 0 0
		// 0 0 0
		// 0 0 0
        std::vector<std::vector<int>> aoiMask{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        std::vector<double> fixX{1}; // Fixation outside AOI
        std::vector<double> fixY{1};
        int winX = 3;
        int winY = 3;

        std::vector<bool> result = cntRasterAOI(aoiMask, fixX, fixY, winX, winY);

        // Only one fixation, so the result should be false
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == false);
    }

    // SECTION("Empty Fixation List") {
    //     // Empty fixation list should result in an empty bool vector
    //     // 0 0 0
    //     // 0 0 0
    //     // 0 0 0
    //     std::vector<std::vector<int>> aoiMask{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    //     std::vector<double> fixX{};
    //     std::vector<double> fixY{};
    //     int winX = 3;
    //     int winY = 3;

    //     std::vector<bool> result = cntRasterAOI(aoiMask, fixX, fixY, winX, winY);

    //     REQUIRE(result.empty());
    // }

}

} // namespace aoihit
