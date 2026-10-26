#pragma once

#include <cstddef>
#include <vector>

/** @file moving_average.hpp
 *  @brief Расчёт простой скользящей средней.
 */

/** @namespace quant
 *  @brief Функции для работы с ценами.
 */
namespace quant {

/** @brief Считает среднюю для каждого полного окна цен.
 *  @param prices Цены по порядку, без NaN и бесконечностей.
 *  @param window Количество цен в одном окне, от 1 до размера массива.
 *  @return N - window + 1 средних. Элемент i относится к окну prices[i..i+window).
 *  @throws std::invalid_argument При неверном размере окна или нечисловых ценах.
 *  @throws std::overflow_error При переполнении промежуточной суммы.
 *  @details Время работы O(N), память под результат O(N - window + 1).
 *  Неполные окна пропускаются. Отрицательные цены допускаются.
 */
std::vector<double> simple_moving_average(const std::vector<double>& prices,
                                          std::size_t window);

} // namespace quant
