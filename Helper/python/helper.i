%module pyHelper

%include "std_vector.i"

%template(DoubleVector) std::vector<double>;

%{
#include <helper/Helper.hpp>
%}

%include "helper/Helper.hpp"