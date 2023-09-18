#include "vector.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vec4") {
  Vec4<float> v1(4.3, -4.2, 3.1, 1.0);
  Vec4<float> v2(4.3, -4.2, 3.1, 0.0);

  SECTION("Equality") {
    REQUIRE(isApproxEqual(v1, Vec4<double>(4.3, -4.2, 3.1, 1.0)));
    REQUIRE(isApproxEqual(v2, Vec4<double>(4.3, -4.2, 3.1, 0.0)));
  }

  SECTION("Component") {
    REQUIRE(isApproxEqual(v1.x, 4.3));
    REQUIRE(isApproxEqual(v1.y, -4.2));
    REQUIRE(isApproxEqual(v1.z, 3.1));
    REQUIRE(isApproxEqual(v1.w, 1.0));

    REQUIRE(isApproxEqual(v2.x, 4.3));
    REQUIRE(isApproxEqual(v2.y, -4.2));
    REQUIRE(isApproxEqual(v2.z, 3.1));
    REQUIRE(isApproxEqual(v2.w, 0.0));
  }

  SECTION("isPoint") {
    REQUIRE(v1.isPoint());
    REQUIRE_FALSE(v2.isPoint());
  }

  SECTION("isDirection") {
    REQUIRE_FALSE(v1.isDirection());
    REQUIRE(v2.isDirection());
  }

  SECTION("Addition") {
    Vec4<double> a1(3, -2, 5, 1);
    Vec4<double> a2(-2, 3, 1, 0);
    auto sum = a1 + a2;
    REQUIRE(isApproxEqual(sum, Vec4<double>(1, 1, 6, 1)));
    REQUIRE(sum.isPoint());
  }

  SECTION("Unary minus") {
    Vec4<double> a1(1, -2, 3, -4);
    auto neg = -a1;
    REQUIRE(isApproxEqual(neg, Vec4<double>(-1, 2, -3, 4)));
  }

  SECTION("Scalar multiplication") {
    Vec4<double> a1(1, -2, 3, -4);
    auto prod = a1 * 3.5;
    REQUIRE(isApproxEqual(prod, Vec4<double>(3.5, -7, 10.5, -14)));
  }

  SECTION("Scalar division") {
    Vec4<double> a1(1, -2, 3, -4);
    auto quot = a1 / 2;
    REQUIRE(isApproxEqual(quot, Vec4<double>(0.5, -1, 1.5, -2)));
  }
}

TEST_CASE("Point") {
  Point<float> p1(4, -4, 3);

  SECTION("Equality") { REQUIRE(isApproxEqual(p1, Point<double>(4, -4, 3))); }

  SECTION("Component") {
    REQUIRE(isApproxEqual(p1.x, 4.0));
    REQUIRE(isApproxEqual(p1.y, -4.0));
    REQUIRE(isApproxEqual(p1.z, 3.0));
    REQUIRE(isApproxEqual(p1.w, 1.0));
  }

  SECTION("isPoint") { REQUIRE(p1.isPoint()); }

  SECTION("isDirection") { REQUIRE_FALSE(p1.isDirection()); }

  SECTION("Subtraction") {
    Point<double> p1(3, 2, 1);
    Point<double> p2(5, 6, 7);
    auto diff = p1 - p2;
    REQUIRE(isApproxEqual(diff, Direction<double>(-2, -4, -6)));
    REQUIRE(diff.isDirection());
  }
}

TEST_CASE("Direction") {
  Direction<float> v1(4, -4, 3);

  SECTION("Equality") {
    REQUIRE(isApproxEqual(v1, Direction<double>(4, -4, 3)));
  }

  SECTION("Component") {
    REQUIRE(isApproxEqual(v1.x, 4.0));
    REQUIRE(isApproxEqual(v1.y, -4.0));
    REQUIRE(isApproxEqual(v1.z, 3.0));
    REQUIRE(isApproxEqual(v1.w, 0.0));
  }

  SECTION("isPoint") { REQUIRE_FALSE(v1.isPoint()); }

  SECTION("isDirection") { REQUIRE(v1.isDirection()); }

  SECTION("Subtraction") {
    Direction<double> v1(3, 2, 1);
    Direction<double> v2(5, 6, 7);
    auto diff = v1 - v2;
    REQUIRE(isApproxEqual(diff, Direction<double>(-2, -4, -6)));
    REQUIRE(diff.isDirection());
  }

  SECTION("Subtracting direction from zero-vector") {
    Direction<double> v1(1, -2, 3);
    auto diff = Direction<double>() - v1;
    REQUIRE(isApproxEqual(diff, Direction<double>(-1, 2, -3)));
    REQUIRE(diff.isDirection());
  }

  SECTION("Length") {
    Direction<double> v1(1, 0, 0);
    REQUIRE(isApproxEqual(v1.length(), 1.0));

    Direction<double> v2(0, 1, 0);
    REQUIRE(isApproxEqual(v2.length(), 1.0));

    Direction<double> v3(0, 0, 1);
    REQUIRE(isApproxEqual(v3.length(), 1.0));

    Direction<double> v4(1, 2, 3);
    REQUIRE(isApproxEqual(v4.length(), sqrt(14)));

    Direction<double> v5(-1, -2, -3);
    REQUIRE(isApproxEqual(v5.length(), sqrt(14)));
  }

  SECTION("Normalise") {
    Direction<double> v1(4, 0, 0);
    REQUIRE(isApproxEqual(v1.normalise(), Direction<double>(1, 0, 0)));

    Direction<double> v2(1, 2, 3);
    REQUIRE(isApproxEqual(
        v2.normalise(),
        Direction<double>(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14))));
  }

  SECTION("Magnitude of a normalised vector") {
    Direction<double> v1(1, 2, 3);
    REQUIRE(isApproxEqual(v1.normalise().length(), 1.0));
  }

  SECTION("Dot product") {
    Direction<double> v1(1, 2, 3);
    Direction<double> v2(2, 3, 4);
    REQUIRE(isApproxEqual(dot(v1, v2), 20));
  }

  SECTION("Cross product") {
    Direction<double> v1(1, 2, 3);
    Direction<double> v2(2, 3, 4);
    REQUIRE(isApproxEqual(cross(v1, v2), Direction<double>(-1, 2, -1)));
    REQUIRE(isApproxEqual(cross(v2, v1), Direction<double>(1, -2, 1)));
  }
}

TEST_CASE("Subtract direction from point") {
  Point<double> p1(3, 2, 1);
  Direction<double> v1(5, 6, 7);
  auto diff = p1 - v1;
  REQUIRE(isApproxEqual(diff, Point<double>(-2, -4, -6)));
}