%module helpers

// Add necessary symbols to generated header
// %{
// #include "helpers.hpp"
// %}

%include "std_vector.i"
%template(DoubleVector) std::vector<double>;

// std::vector<double> displayAreaToPixels(std::vector<double> coordsAbs, int resolution);

// Process symbols in header
// %include "helpers.hpp"