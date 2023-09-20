#include "color.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Color") {
  SECTION("Equality") {
    REQUIRE(isApproxEqual(Color<double>{1.0, 2.0, 3.0},
                          Color<double>{1.0, 2.0, 3.0}));
    REQUIRE(!isApproxEqual(Color<double>{1.0, 2.0, 3.0},
                           Color<double>{1.0, 2.0, 4.0}));
  }

  SECTION("Default constructor") {
    Color<float> c;
    REQUIRE(isApproxEqual(c.r, 0.0f));
    REQUIRE(isApproxEqual(c.g, 0.0f));
    REQUIRE(isApproxEqual(c.b, 0.0f));
    REQUIRE(isApproxEqual(c, Color<double>{0.0, 0.0, 0.0}));
  }

  SECTION("Component-wise Constructor") {
    Color<float> c{1.0f, 2.0f, 3.0f};
    REQUIRE(isApproxEqual(c, Color<double>{1.0, 2.0, 3.0}));
  }

  SECTION("Copy constructor") {
    Color<float> c{1.0f, 2.0f, 3.0f};
    Color<float> d(c);
    REQUIRE(isApproxEqual(d, Color<double>{1.0, 2.0, 3.0}));
  }

  SECTION("Copy assignment") {
    Color<float> c{1.0f, 2.0f, 3.0f};
    Color<float> d;
    d = c;
    REQUIRE(isApproxEqual(d, Color<double>{1.0, 2.0, 3.0}));
  }

  SECTION("Addition") {
    Color<double> c1{0.9, 0.6, 0.75};
    Color<double> c2{0.7, 0.1, 0.25};
    auto sum = c1 + c2;
    REQUIRE(isApproxEqual(sum, Color<double>{1.6, 0.7, 1.0}));
  }

  SECTION("Subtraction") {
    Color<double> c1{0.9, 0.6, 0.75};
    Color<double> c2{0.7, 0.1, 0.25};
    auto diff = c1 - c2;
    REQUIRE(isApproxEqual(diff, Color<double>{0.2, 0.5, 0.5}));
  }

  SECTION("Scalar multiplication") {
    Color<double> c{0.2, 0.3, 0.4};
    auto prod = c * 2.0;
    REQUIRE(isApproxEqual(prod, Color<double>{0.4, 0.6, 0.8}));
  }

  SECTION("Scalar division") {
    Color<double> c{0.2, 0.3, 0.4};
    auto quot = c / 2.0;
    REQUIRE(isApproxEqual(quot, Color<double>{0.1, 0.15, 0.2}));
  }

  SECTION("Schur product") {
    Color<double> c1{1.0, 0.2, 0.4};
    Color<double> c2{0.9, 1.0, 0.1};
    auto prod = c1 * c2;
    REQUIRE(isApproxEqual(prod, Color<double>{0.9, 0.2, 0.04}));
  }
}