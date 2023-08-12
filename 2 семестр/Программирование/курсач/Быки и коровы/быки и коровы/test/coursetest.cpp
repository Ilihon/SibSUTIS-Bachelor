#include "../src/course.h"
#define CATCH_CONFIG_MAIN
#include "../thirdparty/catch/catch.hpp"

TEST_CASE("Test1")
{
    int A[4] = {4, 5, 7, 8};
    char B[4] = {'4', '5', '7', '8'};
    int bull, cow;
    int N = 4;
    int result = CountBullandCow(A, B, bull, cow, N);
    int expected = 4;
    REQUIRE(expected == result);
}

TEST_CASE("Test2")
{
    int A[6] = {4, 5, 7, 8, 1, 3};
    char B[6] = {'4', '5', '1', '8', '3', '7'};
    int bull, cow;
    int N = 6;
    int result = CountBullandCow(A, B, bull, cow, N);
    int expected = 3;
    REQUIRE(expected == result);
}