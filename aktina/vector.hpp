#pragma once

#include <cmath>
#include <float-compare.hpp>

template <typename T>
struct Vector {
  T x, y, z, w;
  Vector(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} {}
  Vector() = default;
  Vector(const Vector<T>& other)
      : x{other.x}, y{other.y}, z{other.z}, w{other.w} {}
  Vector& operator=(const Vector<T>& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
      z = other.z;
      w = other.w;
    }
    return *this;
  }

  bool isPoint() { return w == 1; }
  bool isDirection() { return w == 0; }

  Vector<T> operator-() { return Vector<T>(-x, -y, -z, -w); }
  T length() { return sqrt(dot(*this, *this)); }
  Vector<T> normalise() {
    T len = this->length();
    return Vector<T>{this->x / len, this->y / len, this->z / len,
                     this->w / len};
  }
};

// add
template <typename T, typename U>
Vector<T> operator+(Vector<T> t, Vector<U> u) {
  return Vector<T>{t.x + u.x, t.y + u.y, t.z + u.z, t.w + u.w};
}

// subtract
template <typename T, typename U>
Vector<T> operator-(Vector<T> t, Vector<U> u) {
  return t + (-u);
}

// scalar multiplication
template <typename T, typename U>
Vector<T> operator*(Vector<T> t, U u) {
  return Vector<T>{t.x * u, t.y * u, t.z * u, t.w * u};
}

template <typename T, typename U>
Vector<U> operator*(T u, Vector<U> t) {
  return t * u;
}

// scalar division
template <typename T, typename U>
Vector<T> operator/(Vector<T> t, U u) {
  return Vector<T>{t.x / u, t.y / u, t.z / u, t.w / u};
}

template <typename T, typename U>
T dot(Vector<T> t, Vector<U> u) {
  return t.x * u.x + t.y * u.y + t.z * u.z + t.w * u.w;
}

template <typename T, typename U>
Vector<T> cross(Vector<T> t, Vector<U> u) {
  return Vector<T>(t.y * u.z - t.z * u.y, t.z * u.x - t.x * u.z,
                   t.x * u.y - t.y * u.x, 0.0);
}

template <typename T, typename U>
bool isApproxEqual(Vector<T> t, Vector<U> u) {
  // compare two Vectors for approximate equality
  return isApproxEqual(t.x, u.x) && isApproxEqual(t.y, u.y) &&
         isApproxEqual(t.z, u.z) && isApproxEqual(t.w, u.w);
}

// Function to initialise a Vector as Direction, with w = 0
template <typename T>
Vector<T> direction(T x, T y, T z) {
  return Vector<T>{x, y, z, 0};
}

// Function to initialise a Vector as point, with w = 1
template <typename T>
Vector<T> point(T x, T y, T z) {
  return Vector<T>{x, y, z, 1};
}