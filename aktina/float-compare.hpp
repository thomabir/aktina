#include <cmath>

// set precision for comparisons of floats
const float RELTOL = 0.0001;
const float ABSTOL = 0.0001;

template <typename T, typename U>
bool isApproxEqual(T t, U u) {
  // compare two numbers for approximate equality

  // check if they are equal
  if (t == u) {
    return true;
  }
  // check if they are close enough
  T diff = std::abs(t - u);
  if (diff <= ABSTOL) {
    return true;
  }
  // check if they are close enough relative to the larger one
  T larger = std::abs(t);
  if (std::abs(u) > larger) {
    larger = std::abs(u);
  }
  if (diff <= larger * RELTOL) {
    return true;
  }
  // otherwise, they are not close enough
  return false;
}