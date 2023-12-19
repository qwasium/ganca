%module helpers

%{
#include "helpers.h"
%}

// %include stl.i
%include "std_vector.i"

%template(VectorDouble) std::vector<double>;

%include "helpers.h"