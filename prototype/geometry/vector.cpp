/* Parts of a C++ raytracer. This file serves to quickly test some ideas.*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// set precision for comparisons of floats
const float RELTOL = 0.0001;
const float ABSTOL = 0.0001;

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

template <typename T, typename U>
bool isApproxEqual(T t, U u) {
  // compare two numbers for equality

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
  // compare two tuples for equality
  return isApproxEqual(t.x, u.x) && isApproxEqual(t.y, u.y) &&
         isApproxEqual(t.z, u.z) && isApproxEqual(t.w, u.w);
}

int main() {
  // test Tuple
  Tup4<float> t1(4.3, -4.2, 3.1, 1.0);
  assert(isApproxEqual(t1, Tup4<double>(4.3, -4.2, 3.1, 1.0)));
  assert(isApproxEqual(t1.x, 4.3));
  assert(isApproxEqual(t1.y, -4.2));
  assert(isApproxEqual(t1.z, 3.1));
  assert(isApproxEqual(t1.w, 1.0));
  assert(t1.isPoint());
  assert(!t1.isVector());

  Tup4<float> t2(4.3, -4.2, 3.1, 0.0);
  assert(isApproxEqual(t2.x, 4.3));
  assert(isApproxEqual(t2.y, -4.2));
  assert(isApproxEqual(t2.z, 3.1));
  assert(isApproxEqual(t2.w, 0.0));
  assert(!t2.isPoint());
  assert(t2.isVector());

  // test Point
  Point<float> p1(4, -4, 3);
  assert(isApproxEqual(p1.x, 4.0));
  assert(isApproxEqual(p1.y, -4.0));
  assert(isApproxEqual(p1.z, 3.0));
  assert(isApproxEqual(p1.w, 1.0));
  assert(p1.isPoint());
  assert(!p1.isVector());

  // test Direction
  Direction<float> v1(4, -4, 3);
  assert(isApproxEqual(v1.x, 4.0));
  assert(isApproxEqual(v1.y, -4.0));
  assert(isApproxEqual(v1.z, 3.0));
  assert(isApproxEqual(v1.w, 0.0));
  assert(!v1.isPoint());
  assert(v1.isVector());

  // make it fail, just to check
  // assert(1 == 0);

  // print Done
  std::cout << "Done" << std::endl;

  return 0;
}