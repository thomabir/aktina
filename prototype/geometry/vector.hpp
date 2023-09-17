#pragma once

#include <cmath>

// set precision for comparisons of floats
const float RELTOL = 0.0001;
const float ABSTOL = 0.0001;

// define a concept for scalars
template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <typename T>
struct Tup4 {
  // 4-tuple, 4th component is used to distinguish between points and directions
  T x, y, z, w;
  Tup4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
  Tup4() : x(0), y(0), z(0), w(0) {}
  bool isPoint() { return w == 1.0; }
  bool isVector() { return w == 0.0; }
};

template <typename T>
struct Point : public Tup4<T> {
  Point(T x, T y, T z) : Tup4<T>(x, y, z, 1.0) {}
  Point() : Tup4<T>() {}
};

template <typename T>
struct Direction : public Tup4<T> {
  Direction(T x, T y, T z) : Tup4<T>(x, y, z, 0.0) {}
  Direction() : Tup4<T>() {}
};

template <Scalar T, Scalar U>
bool isApproxEqual(T t, U u) {
  // compare two numbers for approximate equality

  // check if they are equal
  if (t == u) {
    return true;
  }
  // check if they are close enough
  T diff = abs(t - u);
  if (diff <= ABSTOL) {
    return true;
  }
  // check if they are close enough relative to the larger one
  T larger = abs(t);
  if (abs(u) > larger) {
    larger = abs(u);
  }
  if (diff <= larger * RELTOL) {
    return true;
  }
  // otherwise, they are not close enough
  return false;
}

template <typename T, typename U>
bool isApproxEqual(Tup4<T> t, Tup4<U> u) {
  // compare two tuples for approximate equality
  return isApproxEqual(t.x, u.x) && isApproxEqual(t.y, u.y) &&
         isApproxEqual(t.z, u.z) && isApproxEqual(t.w, u.w);
}