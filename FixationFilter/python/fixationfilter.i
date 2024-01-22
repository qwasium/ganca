%module pyFixationFilter

%include "stdint.i"
%include "std_vector.i"

%template(BoolVector) std::vector<bool>;
%template(DoubleVector) std::vector<double>;
%template(BoolVectorVector) std::vector<std::vector<bool>>;

%{
#include <fixationfilter/FixationFilter.hpp>
%}

%include "fixationfilter/FixationFilter.hpp"