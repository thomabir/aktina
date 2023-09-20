#pragma once

#include <cmath>
#include <float-compare.hpp>

template <typename T>
struct Color {
  T r, g, b;
  Color(T r, T g, T b) : r{r}, g{g}, b{b} {}
  Color() = default;
  Color(const Color<T>& other) : r{other.r}, g{other.g}, b{other.b} {}
  Color& operator=(const Color<T>& other) {
    if (this != &other) {
      r = other.r;
      g = other.g;
      b = other.b;
    }
    return *this;
  }

  Color<T> operator-() { return Color<T>(-r, -g, -b); }
};

// add
template <typename T, typename U>
Color<T> operator+(Color<T> t, Color<U> u) {
  return Color<T>{t.r + u.r, t.g + u.g, t.b + u.b};
}

// subtract
template <typename T, typename U>
Color<T> operator-(Color<T> t, Color<U> u) {
  return t + (-u);
}

// scalar multiplication
template <typename T, typename U>
Color<T> operator*(Color<T> t, U u) {
  return Color<T>{t.r * u, t.g * u, t.b * u};
}

template <typename T, typename U>
Color<U> operator*(T u, Color<U> t) {
  return t * u;
}

// scalar division
template <typename T, typename U>
Color<T> operator/(Color<T> t, U u) {
  return Color<T>{t.r / u, t.g / u, t.b / u};
}

// Schur / Hadamard product
template <typename T, typename U>
Color<T> operator*(Color<T> t, Color<U> u) {
  return Color<T>{t.r * u.r, t.g * u.g, t.b * u.b};
}

template <typename T, typename U>
bool isApproxEqual(Color<T> t, Color<U> u) {
  // compare two Colors for approximate equality
  return isApproxEqual(t.r, u.r) && isApproxEqual(t.g, u.g) &&
         isApproxEqual(t.b, u.b);
}