# pragma once

# include <cstdint>
# include <vector>
# include <string>

namespace aoihit{
	std::vector<bool> cntRasterAOI (std::vector<std::vector<int>> aoiMask,
									std::vector<double> fixX,
									std::vector<double> fixY,
									int winX, int winY);

	// void freeFunction(int level);
	// void freeFunction(int64_t level);

	// class AOIHit {
	// 	public:
	// 		static void staticFunction(int level);
	// 		static void staticFunction(int64_t level);

	// 		int getInt() const;
	// 		void setInt(int input);

	// 		int64_t getInt64() const;
	// 		void setInt64(int64_t input);

	// 		// Print object for debug.
	// 		std::string operator()() const;

	// 	private:
	// 		int     _intValue   = 0;
	// 		int64_t _int64Value = 0;
	// }; // class AOIHit
} // namespace aoihit