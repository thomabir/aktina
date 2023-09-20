#include "canvas.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("Canvas") {
  SECTION("Constructors") {
    // default constructor
    Canvas<float> c2(10, 20);
    REQUIRE(c2.width == 10);
    REQUIRE(c2.height == 20);
    for (int i = 0; i < 10 * 20; ++i) {
      REQUIRE(isApproxEqual(c2.pixels[i], Color<float>{0.0f, 0.0f, 0.0f}));
    }
  }

  SECTION("Set and get") {
    Canvas<float> c(10, 20);
    c(2, 3) = Color<float>{1.0f, 2.0f, 3.0f};
    REQUIRE(isApproxEqual(c(2, 3), Color<float>{1.0f, 2.0f, 3.0f}));
    // all others are 0
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 20; ++j) {
        if (i != 2 && j != 3) {
          REQUIRE(isApproxEqual(c(i, j), Color<float>{0.0f, 0.0f, 0.0f}));
        }
      }
    }
  }

  SECTION("Clamp") {
    Canvas<float> c(10, 20);
    c(2, 3) = Color<float>{-1.0f, 0.5f, 1.3f};
    c.clamp();
    REQUIRE(isApproxEqual(c(2, 3), Color<float>{0.0f, 127.5f, 255.0f}));
  }

  SECTION("Print to file") {
    Canvas<float> c(5, 3);
    c(0, 0) = Color<float>{1.5f, 0.0f, 0.0f};
    c(2, 1) = Color<float>{0.0f, 0.5f, 0.0f};
    c(4, 2) = Color<float>{-0.5f, 0.0f, 1.0f};
    std::stringstream ss;
    ss << c;
    REQUIRE(ss.str() ==
            "P3\n5 3\n255\n"
            "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n");
  }

  SECTION("Print to file with max. 70 characters per line") {
    Canvas<float> c(10, 2);
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 2; ++j) {
        c(i, j) = Color<float>{1.0f, 0.8f, 0.6f};
      }
    }
    std::stringstream ss;
    ss << c;
    REQUIRE(ss.str() ==
            "P3\n10 2\n255\n"
            "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 "
            "255 204\n"
            "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
            "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 "
            "255 204\n"
            "153 255 204 153 255 204 153 255 204 153 255 204 153\n");
  }
}