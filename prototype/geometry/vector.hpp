#pragma once

#include <cmath>
#include <float-compare.hpp>

template <typename T>
struct Vector {
  T x, y, z;
  Vector(T x, T y, T z) : x{x}, y{y}, z{z} {}
  Vector() = default;
  Vector(const Vector<T>& other) : x{other.x}, y{other.y}, z{other.z} {}
  Vector& operator=(const Vector<T>& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
      z = other.z;
    }
    return *this;
  }

  Vector<T> operator-() { return Vector<T>(-x, -y, -z); }
  T length() { return sqrt(dot(*this, *this)); }
  Vector<T> normalise() {
    T len = this->length();
    return Vector<T>(this->x / len, this->y / len, this->z / len);
  }
};

// add
template <typename T, typename U>
Vector<T> operator+(Vector<T> t, Vector<U> u) {
  return Vector<T>{t.x + u.x, t.y + u.y, t.z + u.z};
}

// subtract
template <typename T, typename U>
Vector<T> operator-(Vector<T> t, Vector<U> u) {
  return t + (-u);
}

// scalar multiplication
template <typename T, typename U>
Vector<T> operator*(Vector<T> t, U u) {
  return Vector<T>{t.x * u, t.y * u, t.z * u};
}

template <typename T, typename U>
Vector<U> operator*(T u, Vector<U> t) {
  return t * u;
}

// scalar division
template <typename T, typename U>
Vector<T> operator/(Vector<T> t, U u) {
  return Vector<T>{t.x / u, t.y / u, t.z / u};
}

template <typename T, typename U>
T dot(Vector<T> t, Vector<U> u) {
  return t.x * u.x + t.y * u.y + t.z * u.z;
}

template <typename T, typename U>
Vector<T> cross(Vector<T> t, Vector<U> u) {
  return Vector<T>(t.y * u.z - t.z * u.y, t.z * u.x - t.x * u.z,
                   t.x * u.y - t.y * u.x);
}

template <typename T, typename U>
bool isApproxEqual(Vector<T> t, Vector<U> u) {
  // compare two Vectors for approximate equality
  return isApproxEqual(t.x, u.x) && isApproxEqual(t.y, u.y) &&
         isApproxEqual(t.z, u.z);
}
