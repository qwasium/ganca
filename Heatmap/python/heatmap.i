%module pyHeatmap

%include "std_string.i"
%include "std_vector.i"

%template(DoubleVector) std::vector<double>;
%template(DoubleVectorVector) std::vector<std::vector<double>>;

%{
#include <heatmap/Heatmap.hpp>
%}

%include "heatmap/Heatmap.hpp"