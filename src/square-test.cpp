#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "square.h"

using trompeloeil::_;

SCENARIO("This is an example scenario", "[Square]")
{
    GIVEN("A number to be squared")
    {
        constexpr int to_be_squared(2);
        constexpr int expected(to_be_squared * to_be_squared);
        REQUIRE(square(to_be_squared) == expected);
    }
}