#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "quant/moving_average.hpp"

#include <limits>
#include <stdexcept>

TEST_CASE("SMA computes all complete windows") {
    const auto actual = quant::simple_moving_average({100, 102, 101, 105, 107}, 3);
    REQUIRE(actual.size() == 3);
    CHECK(actual[0] == doctest::Approx(101.0));
    CHECK(actual[1] == doctest::Approx(308.0 / 3.0));
    CHECK(actual[2] == doctest::Approx(313.0 / 3.0));
}

TEST_CASE("Boundary window sizes") {
    const std::vector<double> prices{-2.5, 0.0, 5.5};
    CHECK(quant::simple_moving_average(prices, 1) == prices);
    const auto average = quant::simple_moving_average(prices, prices.size());
    REQUIRE(average.size() == 1);
    CHECK(average[0] == doctest::Approx(1.0));
    CHECK(quant::simple_moving_average({42}, 1)[0] == 42);
}

TEST_CASE("Invalid windows and empty input are rejected") {
    CHECK_THROWS_AS(quant::simple_moving_average({1, 2}, 0), std::invalid_argument);
    CHECK_THROWS_AS(quant::simple_moving_average({1, 2}, 3), std::invalid_argument);
    CHECK_THROWS_AS(quant::simple_moving_average({}, 1), std::invalid_argument);
    CHECK_THROWS_AS(quant::simple_moving_average({}, 0), std::invalid_argument);
}

TEST_CASE("Non-finite observations are rejected even after the first window") {
    for (double bad : {std::numeric_limits<double>::infinity(),
                       -std::numeric_limits<double>::infinity(),
                       std::numeric_limits<double>::quiet_NaN()}) {
        CHECK_THROWS_AS(quant::simple_moving_average({1, 2, bad}, 2), std::invalid_argument);
    }
}

TEST_CASE("Sliding sums agree with a direct reference implementation") {
    std::vector<double> prices;
    for (int i = 0; i < 200; ++i) {
        prices.push_back(static_cast<double>((i * 37) % 101 - 50) / 8.0);
    }
    for (std::size_t window : {1U, 2U, 7U, 50U, 200U}) {
        const auto actual = quant::simple_moving_average(prices, window);
        REQUIRE(actual.size() == prices.size() - window + 1);
        for (std::size_t i = 0; i < actual.size(); ++i) {
            long double sum = 0;
            for (std::size_t j = i; j < i + window; ++j) {
                sum += prices[j];
            }
            CHECK(actual[i] == doctest::Approx(static_cast<double>(sum / window)));
        }
    }
}
