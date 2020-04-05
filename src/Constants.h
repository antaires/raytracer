#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "./Vec3.h"
#include "./Ray.h"
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

//constants
const int image_width = 800;
const int image_height = 400;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180;}
inline double ffmin(double a, double b){ return a <= b ? a : b; }
inline double ffmax(double a, double b){ return a >= b ? a : b; }

#endif
