#include "vector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cmath>

TEST_CASE("Vector") {
  Vector<float> v1{4.3, -4.2, 3.1};
  Vector<float> v2{4.3, -4.2, 3.1};

  SECTION("Constructors") {
    // default constructor
    Vector<float> v3;
    REQUIRE(isApproxEqual(v3, Vector<float>{0, 0, 0}));

    // component-wise constructor
    REQUIRE(isApproxEqual(v1, Vector<float>{4.3, -4.2, 3.1}));

    // copy constructor
    Vector<float> v4{v1};
    REQUIRE(isApproxEqual(v4, Vector<float>{4.3, -4.2, 3.1}));

    // copy assignment operator
    Vector<float> v5;
    v5 = v1;
    REQUIRE(isApproxEqual(v5, Vector<float>{4.3, -4.2, 3.1}));
  }

  SECTION("Equality") {
    REQUIRE(isApproxEqual(v1, Vector<double>{4.3, -4.2, 3.1}));
    REQUIRE(isApproxEqual(v2, Vector<double>{4.3, -4.2, 3.1}));

    REQUIRE(!isApproxEqual(v1, Vector<double>{4.3, -4.2, 3.2}));
  }

  SECTION("Component") {
    REQUIRE(isApproxEqual(v1.x, 4.3));
    REQUIRE(isApproxEqual(v1.y, -4.2));
    REQUIRE(isApproxEqual(v1.z, 3.1));

    REQUIRE(isApproxEqual(v2.x, 4.3));
    REQUIRE(isApproxEqual(v2.y, -4.2));
    REQUIRE(isApproxEqual(v2.z, 3.1));
  }

  SECTION("Addition") {
    Vector<double> a1{3, -2, 5};
    Vector<double> a2{-2, 3, 1};
    auto sum = a1 + a2;
    REQUIRE(isApproxEqual(sum, Vector<double>{1, 1, 6}));
  }

  SECTION("Subtraction") {
    Vector<double> a1{3, 2, 1};
    Vector<double> a2{5, 6, 7};
    auto diff = a1 - a2;
    REQUIRE(isApproxEqual(diff, Vector<double>{-2, -4, -6}));
  }

  SECTION("Unary minus") {
    Vector<double> a1{1, -2, 3};
    auto neg = -a1;
    REQUIRE(isApproxEqual(neg, Vector<double>{-1, 2, -3}));
  }

  SECTION("Scalar multiplication") {
    Vector<double> a1{1, -2, 3};
    auto prod = a1 * 3.5;
    REQUIRE(isApproxEqual(prod, Vector<double>{3.5, -7, 10.5}));
  }

  SECTION("Scalar division") {
    Vector<double> a1{1, -2, 3};
    auto quot = a1 / 2;
    REQUIRE(isApproxEqual(quot, Vector<double>{0.5, -1, 1.5}));
  }

  SECTION("Length") {
    Vector<double> v1{1, 0, 0};
    REQUIRE(isApproxEqual(v1.length(), 1.0));

    Vector<double> v2{0, 1, 0};
    REQUIRE(isApproxEqual(v2.length(), 1.0));

    Vector<double> v3{0, 0, 1};
    REQUIRE(isApproxEqual(v3.length(), 1.0));

    Vector<double> v4{1, 2, 3};
    REQUIRE(isApproxEqual(v4.length(), sqrt(14)));

    Vector<double> v5{-1, -2, -3};
    REQUIRE(isApproxEqual(v5.length(), sqrt(14)));

    Vector<double> v6{0, 0, 0};
    REQUIRE(isApproxEqual(v6.length(), 0.0));
  }

  SECTION("Normalise") {
    Vector<double> v1{4, 0, 0};
    REQUIRE(isApproxEqual(v1.normalise(), Vector<double>{1, 0, 0}));

    Vector<double> v2{1, 2, 3};
    REQUIRE(isApproxEqual(
        v2.normalise(),
        Vector<double>{1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)}));
  }

  SECTION("Magnitude of a normalised vector") {
    Vector<double> v1{1, 2, 3};
    REQUIRE(isApproxEqual(v1.normalise().length(), 1.0));
  }

  SECTION("Dot product") {
    Vector<double> v1{1, 2, 3};
    Vector<double> v2{2, 3, 4};
    REQUIRE(isApproxEqual(dot(v1, v2), 20));
  }

  SECTION("Cross product") {
    Vector<double> v1{1, 2, 3};
    Vector<double> v2{2, 3, 4};
    REQUIRE(isApproxEqual(cross(v1, v2), Vector<double>{-1, 2, -1}));
    REQUIRE(isApproxEqual(cross(v2, v1), Vector<double>{1, -2, 1}));
  }
}
