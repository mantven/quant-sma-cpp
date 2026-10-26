#include "quant/moving_average.hpp"

#include <cmath>
#include <stdexcept>

namespace quant {

std::vector<double> simple_moving_average(const std::vector<double>& prices,
                                          std::size_t window) {
    if (window == 0 || window > prices.size()) {
        throw std::invalid_argument("window must be between 1 and prices.size()");
    }
    for (double price : prices) {
        if (!std::isfinite(price)) {
            throw std::invalid_argument("prices must contain only finite values");
        }
    }

    std::vector<double> result;
    result.reserve(prices.size() - window + 1);
    long double sum = 0.0L;
    for (std::size_t i = 0; i < prices.size(); ++i) {
        if (i >= window) {
            sum -= static_cast<long double>(prices[i - window]);
        }
        sum += static_cast<long double>(prices[i]);
        if (!std::isfinite(sum)) {
            throw std::overflow_error("moving average sum overflow");
        }
        if (i >= window - 1) {
            result.push_back(static_cast<double>(sum / static_cast<long double>(window)));
        }
    }
    return result;
}

} // namespace quant
