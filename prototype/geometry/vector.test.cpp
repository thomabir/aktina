#include "vector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cmath>

TEST_CASE("Vector") {
  Vector<float> v1{4.3, -4.2, 3.1, 0};
  Vector<float> v2{4.3, -4.2, 3.1, 1};

  SECTION("Constructors") {
    // default constructor
    Vector<float> v3;
    REQUIRE(isApproxEqual(v3, Vector<float>{0., 0., 0., 0.}));

    // component-wise constructor
    REQUIRE(isApproxEqual(v1, Vector<float>{4.3, -4.2, 3.1, 0}));

    // copy constructor
    Vector<float> v4{v1};
    REQUIRE(isApproxEqual(v4, Vector<float>{4.3, -4.2, 3.1, 0}));

    // copy assignment operator
    Vector<float> v5;
    v5 = v1;
    REQUIRE(isApproxEqual(v5, Vector<float>{4.3, -4.2, 3.1, 0}));
  }

  SECTION("Equality") {
    REQUIRE(isApproxEqual(v1, Vector<double>{4.3, -4.2, 3.1, 0}));
    REQUIRE(isApproxEqual(v2, Vector<double>{4.3, -4.2, 3.1, 1}));

    REQUIRE(!isApproxEqual(v1, Vector<double>{4.3, -4.2, 3.2, 0}));
  }

  SECTION("Check Point or Direction") {
    REQUIRE(v1.isDirection());
    REQUIRE(!v1.isPoint());
    REQUIRE(!v2.isDirection());
    REQUIRE(v2.isPoint());
  }

  SECTION("Component") {
    REQUIRE(isApproxEqual(v1.x, 4.3));
    REQUIRE(isApproxEqual(v1.y, -4.2));
    REQUIRE(isApproxEqual(v1.z, 3.1));
    REQUIRE(isApproxEqual(v1.w, 0));

    REQUIRE(isApproxEqual(v2.x, 4.3));
    REQUIRE(isApproxEqual(v2.y, -4.2));
    REQUIRE(isApproxEqual(v2.z, 3.1));
    REQUIRE(isApproxEqual(v2.w, 1));
  }

  SECTION("Addition") {
    Vector<double> a1{3, -2, 5, 1};
    Vector<double> a2{-2, 3, 1, 0};
    auto sum = a1 + a2;
    REQUIRE(isApproxEqual(sum, Vector<double>{1, 1, 6, 1}));
  }

  SECTION("Subtraction") {
    Vector<double> a1{3, 2, 1, 4};
    Vector<double> a2{5, 6, 7, 8};
    auto diff = a1 - a2;
    REQUIRE(isApproxEqual(diff, Vector<double>{-2, -4, -6, -4}));
  }

  SECTION("Unary minus") {
    Vector<double> a1{1, -2, 3, -4};
    auto neg = -a1;
    REQUIRE(isApproxEqual(neg, Vector<double>{-1, 2, -3, 4}));
  }

  SECTION("Scalar multiplication") {
    Vector<double> a1{1, -2, 3, -4};
    auto prod = a1 * 3.5;
    REQUIRE(isApproxEqual(prod, Vector<double>{3.5, -7, 10.5, -14}));
  }

  SECTION("Scalar division") {
    Vector<double> a1{1, -2, 3, -4};
    auto quot = a1 / 2;
    REQUIRE(isApproxEqual(quot, Vector<double>{0.5, -1, 1.5, -2}));
  }
}

TEST_CASE("Point") {
  auto p1 = point(4.0, -4.0, 3.0);
  auto p2 = point(1.0, 2.0, 3.0);

  REQUIRE(isApproxEqual(p1, Vector<double>{4.0, -4.0, 3.0, 1.0}));
  REQUIRE(p1.isPoint());
  REQUIRE(!p1.isDirection());

  SECTION("Subtraction") {
    auto diff = p1 - p2;
    REQUIRE(isApproxEqual(diff, direction(3.0, -6.0, 0.0)));
    REQUIRE(diff.isDirection());
  }
}

TEST_CASE("Direction") {
  auto d1 = direction(3.0, 2.0, 1.0);
  auto d2 = direction(5.0, 6.0, 7.0);

  SECTION("Equality") {
    REQUIRE(isApproxEqual(d1, direction(3.0, 2.0, 1.0)));
    REQUIRE(isApproxEqual(d1, Vector<double>{3.0, 2.0, 1.0, 0.0}));
  }

  REQUIRE(!d1.isPoint());
  REQUIRE(d1.isDirection());

  SECTION("Addition") {
    auto sum = d1 + d2;
    REQUIRE(isApproxEqual(sum, Vector<double>{8.0, 8.0, 8.0, 0.0}));
    REQUIRE(isApproxEqual(sum, direction(8.0, 8.0, 8.0)));
    REQUIRE(sum.isDirection());
  }

  SECTION("Subtraction") {
    auto diff = d1 - d2;
    REQUIRE(isApproxEqual(diff, Vector<double>{-2.0, -4.0, -6.0, 0.0}));
    REQUIRE(isApproxEqual(diff, direction(-2.0, -4.0, -6.0)));
    REQUIRE(diff.isDirection());
  }

  SECTION("Length") {
    auto d0 = direction(0.0, 0.0, 0.0);
    REQUIRE(isApproxEqual(d0.length(), 0.0));

    auto d3 = direction(1.0, 0.0, 0.0);
    REQUIRE(isApproxEqual(d3.length(), 1.0));

    d0 = direction(0.0, 1.0, 0.0);
    REQUIRE(isApproxEqual(d0.length(), 1.0));

    d1 = direction(0.0, 0.0, 1.0);
    REQUIRE(isApproxEqual(d1.length(), 1.0));

    d2 = direction(1.0, 2.0, 3.0);
    REQUIRE(isApproxEqual(d2.length(), sqrt(14)));

    d3 = direction(-1.0, -2.0, -3.0);
    REQUIRE(isApproxEqual(d3.length(), sqrt(14)));
  }

  SECTION("Normalise") {
    d1 = direction(4.0, 0.0, 0.0);
    REQUIRE(isApproxEqual(d1.normalise(), direction(1.0, 0.0, 0.0)));

    d1 = direction(1.0, 2.0, 3.0);
    REQUIRE(isApproxEqual(
        d1.normalise(),
        direction(1.0 / sqrt(14), 2.0 / sqrt(14), 3.0 / sqrt(14))));
  }

  SECTION("Length of a normalised vector") {
    d1 = direction(1.0, 2.0, 3.0);
    REQUIRE(isApproxEqual(d1.normalise().length(), 1.0));
  }

  SECTION("Dot product") {
    d1 = direction(1.0, 2.0, 3.0);
    d2 = direction(2.0, 3.0, 4.0);
    REQUIRE(isApproxEqual(dot(d1, d2), 20.0));
  }

  SECTION("Cross product") {
    d1 = direction(1.0, 2.0, 3.0);
    d2 = direction(2.0, 3.0, 4.0);
    REQUIRE(isApproxEqual(cross(d1, d2), direction(-1.0, 2.0, -1.0)));
    REQUIRE(isApproxEqual(cross(d2, d1), direction(1.0, -2.0, 1.0)));
  }
}

TEST_CASE("Subtracting a direction from a point") {
  auto p = point(3.0, 2.0, 1.0);
  auto d = direction(5.0, 6.0, 7.0);
  auto diff = p - d;
  REQUIRE(isApproxEqual(diff, point(-2.0, -4.0, -6.0)));
  REQUIRE(diff.isPoint());
}