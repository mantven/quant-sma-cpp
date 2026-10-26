#pragma once

#include <cstddef>
#include <vector>

/** @file moving_average.hpp
 *  @brief Simple moving average for financial time series.
 */

/** @namespace quant
 *  @brief Small quantitative analysis utilities.
 */
namespace quant {

/** @brief Calculate a simple moving average (SMA) using a sliding window.
 *  @param prices Finite observations in chronological order.
 *  @param window Number of observations in each complete window.
 *  @return N - window + 1 means; result[i] corresponds to prices[i..i+window).
 *  @throws std::invalid_argument If window is zero, exceeds the input size,
 *          or an observation is not finite.
 *  @throws std::overflow_error If an intermediate sum is not finite.
 *  @details Runs in O(N) time and uses O(N - window + 1) output memory.
 *  Partial windows are omitted. Negative prices are accepted.
 */
std::vector<double> simple_moving_average(const std::vector<double>& prices,
                                          std::size_t window);

} // namespace quant
