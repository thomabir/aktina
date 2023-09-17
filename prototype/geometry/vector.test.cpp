#include "vector.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tup4") {
  Tup4<float> t1(4.3, -4.2, 3.1, 1.0);
  Tup4<float> t2(4.3, -4.2, 3.1, 0.0);

  SECTION("Equality") {
    REQUIRE(isApproxEqual(t1, Tup4<double>(4.3, -4.2, 3.1, 1.0)));
    REQUIRE(isApproxEqual(t2, Tup4<double>(4.3, -4.2, 3.1, 0.0)));
  }

  SECTION("Component") {
    REQUIRE(isApproxEqual(t1.x, 4.3));
    REQUIRE(isApproxEqual(t1.y, -4.2));
    REQUIRE(isApproxEqual(t1.z, 3.1));
    REQUIRE(isApproxEqual(t1.w, 1.0));

    REQUIRE(isApproxEqual(t2.x, 4.3));
    REQUIRE(isApproxEqual(t2.y, -4.2));
    REQUIRE(isApproxEqual(t2.z, 3.1));
    REQUIRE(isApproxEqual(t2.w, 0.0));
  }

  SECTION("isPoint") {
    REQUIRE(t1.isPoint());
    REQUIRE_FALSE(t2.isPoint());
  }

  SECTION("isVector") {
    REQUIRE_FALSE(t1.isVector());
    REQUIRE(t2.isVector());
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

  SECTION("isVector") { REQUIRE_FALSE(p1.isVector()); }
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

  SECTION("isVector") { REQUIRE(v1.isVector()); }
}