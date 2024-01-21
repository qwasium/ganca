%module pyAOIHit

// %include "typemaps.i"
%include "stdint.i"
%include "std_vector.i"
%include "std_string.i"

%template(IntVector) std::vector<int>; // Will fail without this line: %template vector<vector<int>>
%template(IntVectorVector) std::vector<std::vector<int>>;
%template(DoubleVector) std::vector<double>;
%template(BoolVector) std::vector<bool>;

// Add necessary symbols to generated header
%{
#include <aoihit/AOIHit.hpp>
%}

%include "aoihit/AOIHit.hpp"