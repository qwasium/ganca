# file: runme.py

# This file illustrates the proxy class C++ interface generated
# by SWIG.w

import os
from add_path import AddPath
lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'python_build')
with AddPath(lib_path):
    import example

# ----- Object creation -----

print("Creating some objects:")
c = example.Circle(10)
print("    Created circle %s" % c)
s = example.Square(10)
print("    Created square %s" % s)

# ----- Access a static member -----

print("\nA total of %d shapes were created" % example.cvar.Shape_nshapes)

# ----- Member data access -----

# Set the location of the object

c.x = 20
c.y = 30

s.x = -10
s.y = 5

print("\nHere is their current position:")
print("    Circle = (%f, %f)" % (c.x, c.y))
print("    Square = (%f, %f)" % (s.x, s.y))

# ----- Call some methods -----

print("\nHere are some properties of the shapes:")
for o in [c, s]:
    print("    %s" % o)
    print("        area      = %s" % o.area())
    print("        perimeter = %s" % o.perimeter())
# prevent o from holding a reference to the last object looked at
o = None

print("\nGuess I'll clean up now")

# Note: this invokes the virtual destructor
del c
del s

print("%d shapes remain" % example.cvar.Shape_nshapes)
print("Goodbye")
