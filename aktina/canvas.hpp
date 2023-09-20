#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "color.hpp"

// A canvas is an std::vector of pixels, where each pixel is a Color<T>.
template <typename T>
struct Canvas {
  int width, height;
  std::vector<Color<T>> pixels;

  Canvas(int width, int height) : width{width}, height{height} {
    if (width <= 0 || height <= 0) {
      throw std::invalid_argument("width and height must be > 0");
    }
    pixels.resize(width * height);
  }

  Color<T>& operator()(int x, int y) { return pixels[y * width + x]; }

  const Color<T>& operator()(int x, int y) const {
    return pixels[y * width + x];
  }

  // println: print in the following format:
  // (i, j) r g b
  void println() {
    for (int i = 0; i < width; ++i) {
      for (int j = 0; j < height; ++j)
        std::cout << "(" << i << ", " << j << ") " << pixels[j * width + i].r
                  << " " << pixels[j * width + i].g << " "
                  << pixels[j * width + i].b << "\n";
    }
  }

  // use the ostream operator to create a .ppm file.
  // The header is:
  // P3
  // width height
  // 255
  // Then, each pixel is printed in the following format:
  // r g b
  friend std::ostream& operator<<(std::ostream& os, const Canvas<T>& c) {
    os << "P3\n" << c.width << " " << c.height << "\n255\n";
    for (int i = 0; i < c.width; ++i) {
      for (int j = 0; j < c.height; ++j) {
        os << c(i, j).r << " " << c(i, j).g << " " << c(i, j).b << "\n";
      }
    }
    return os;
  }
};