#include "canvas.hpp"

#include <catch2/catch_test_macros.hpp>

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
}