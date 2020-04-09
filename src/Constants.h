#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

//constants
const int image_width = 200;
const int image_height = 100;
const int samples_per_pixel = 100;
const int ray_depth = 30;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180;}
inline double ffmin(double a, double b){ return a <= b ? a : b; }
inline double ffmax(double a, double b){ return a >= b ? a : b; }

inline double clamp(double x, double min, double max){
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

inline double random_double(){
  // returns real in [0, 1)
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  static std::function<double()> rand_generator = std::bind(distribution, generator);
  return rand_generator();
 }
inline double random_double(double min, double max){ return min + (max-min)*random_double(); }

/* inline bool quadratic(const double& a, const double& b, const double& c, double& x0, double& x1) {
  double discr = b * b - 4 * a * c;
  if (discr < 0){return false;}
  else if (discr == 0){
    x0 = x1 = -0.5 * b / a;
  }
  else {
    double q = (b > 0) ?
      -0.5 * (b + sqrt(discr)) :
      -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  return true;
} */

#endif
