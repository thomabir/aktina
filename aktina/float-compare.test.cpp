#include "float-compare.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cmath>

TEST_CASE("Float comparison") {
  SECTION("Equality") {
    REQUIRE(isApproxEqual(1.0, 1.0));
    REQUIRE(isApproxEqual(1.0, 1.0 + RELTOL));
    REQUIRE(isApproxEqual(1.0, 1.0 - RELTOL));
    REQUIRE(isApproxEqual(1.0, 1.0 + ABSTOL));
    REQUIRE(isApproxEqual(1.0, 1.0 - ABSTOL));
  }

  SECTION("Inequality") {
    REQUIRE(!isApproxEqual(1.0, 1.0 + 2 * RELTOL));
    REQUIRE(!isApproxEqual(1.0, 1.0 - 2 * RELTOL));
    REQUIRE(!isApproxEqual(1.0, 1.0 + 2 * ABSTOL));
    REQUIRE(!isApproxEqual(1.0, 1.0 - 2 * ABSTOL));
  }
}