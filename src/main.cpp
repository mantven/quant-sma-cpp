#include "quant/moving_average.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const std::vector<double> prices{100.0, 102.0, 101.0, 105.0, 107.0};
    const auto averages = quant::simple_moving_average(prices, 3);
    std::cout << "SMA(3):" << std::fixed << std::setprecision(2);
    for (double average : averages) {
        std::cout << ' ' << average;
    }
    std::cout << '\n';
}
