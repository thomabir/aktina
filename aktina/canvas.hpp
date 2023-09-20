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

  void clamp() {
    // multiply all by 255
    for (int i = 0; i < width * height; ++i) {
      pixels[i].r *= 255;
      pixels[i].g *= 255;
      pixels[i].b *= 255;
    }

    // clamp to [0, 255]
    for (int i = 0; i < width * height; ++i) {
      if (pixels[i].r < 0) pixels[i].r = 0;
      if (pixels[i].g < 0) pixels[i].g = 0;
      if (pixels[i].b < 0) pixels[i].b = 0;
      if (pixels[i].r > 255) pixels[i].r = 255;
      if (pixels[i].g > 255) pixels[i].g = 255;
      if (pixels[i].b > 255) pixels[i].b = 255;
    }
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
  // r g b r g b ... (times width)
  // ...
  // r g b r g b ... (times width)
  // where r, g, b are integers in [0, 255].

  friend std::ostream& operator<<(std::ostream& os, const Canvas<T>& c) {
    // ppm header
    os << "P3\n" << c.width << " " << c.height << "\n255\n";

    // clamp the canvas
    Canvas<T> c2 = c;
    c2.clamp();

    // round to the nearest integer, using an int Canvas
    Canvas<int> c3(c.width, c.height);
    for (int i = 0; i < c.width; ++i) {
      for (int j = 0; j < c.height; ++j) {
        c3(i, j).r = std::round(c2(i, j).r);
        c3(i, j).g = std::round(c2(i, j).g);
        c3(i, j).b = std::round(c2(i, j).b);
      }
    }

    // print the pixels in the format r g b r g b ...
    // until either the width of the canvas is reached, or
    // the maximum line length of 70 characters is reached.
    for (int j = 0; j < c.height; ++j) {
      int line_length = 0;
      for (int i = 0; i < c.width; ++i) {
        os << c3(i, j).r << " " << c3(i, j).g << " " << c3(i, j).b << " ";
        line_length += 12;
        if (line_length >= 70) {
          os << "\n";
          line_length = 0;
        }
      }
      os << "\n";
    }
    return os;
  }
};