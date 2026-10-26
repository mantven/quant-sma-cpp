#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>
#include "quant/moving_average.hpp"

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

int main() {
    for (std::size_t count : {1'000U, 10'000U, 100'000U}) {
        std::vector<double> prices(count);
        for (std::size_t i = 0; i < count; ++i) {
            prices[i] = 100.0 + std::sin(static_cast<double>(i) * 0.01);
        }
        ankerl::nanobench::Bench()
            .title("SMA, window=20 (validation and allocation included)")
            .unit("price")
            .batch(static_cast<std::uint64_t>(count))
            .warmup(20)
            .minEpochIterations(10)
            .run("N=" + std::to_string(count), [&] {
                const auto result = quant::simple_moving_average(prices, 20);
                ankerl::nanobench::doNotOptimizeAway(result.data());
                ankerl::nanobench::doNotOptimizeAway(result.back());
            });
    }
}
