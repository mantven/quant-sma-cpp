# quant-sma-cpp

Расчёт простой скользящей средней (SMA) для ряда цен на C++17.
Проект выполнен в рамках курса «Программная инженерия и C++ для
количественного анализа и алгоритмической торговли».

Совместный проект Матвея Затравина и Роберта Юсупова.

[Документация](https://mantven.github.io/quant-sma-cpp/)
· [GitHub Actions](https://github.com/mantven/quant-sma-cpp/actions/workflows/ci.yml)

## Расчёт SMA

Функция `quant::simple_moving_average(prices, window)` возвращает средние
значения по всем окнам размера `window` с шагом 1. Для ряда из `N` цен
результат содержит `N - window + 1` значений. При сдвиге окна сумма обновляется
за одну операцию вычитания и одну операцию сложения; время расчёта — `O(N)`.

Пример `quant_demo` использует цены `100, 102, 101, 105, 107` и окно из трёх
значений:

```text
SMA(3): 101.00 102.67 104.33
```

Пустой ряд, окно вне диапазона `[1, N]`, NaN и бесконечные значения приводят
к `std::invalid_argument`. При переполнении промежуточной суммы выбрасывается
`std::overflow_error`.

## Сборка и запуск

Для сборки в Linux нужны CMake 3.20 или новее, GCC или Clang с поддержкой C++17
и Make.

doctest и nanobench включены в `third_party/` и не требуют отдельной установки.
Команды выполняются из корня репозитория и совпадают с командами CI.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
./build/quant_demo
```

## Тесты и бенчмарк

Тесты на doctest проверяют расчёт средней, граничные размеры окна,
некорректные входные данные и совпадение результата с прямым расчётом средней.

```sh
ctest --test-dir build --output-on-failure
```

Бенчмарк на nanobench измеряет обработку 1 000, 10 000 и 100 000 цен с окном
размера 20. В замер входит весь вызов функции, включая проверку данных
и выделение памяти под результат. В отчёте указаны время обработки одной цены
и количество цен в секунду.

```sh
./build/quant_benchmark
```

## Документация

Doxygen собирает документацию из README и комментариев в `include/quant/`.
Для локальной сборки установите Doxygen и повторно настройте CMake:

```sh
cmake -S . -B build
cmake --build build --target docs
```

Результат доступен в `build/docs/html/index.html`.

## CI

При push и при создании или обновлении pull request GitHub Actions собирает
проект в Release, запускает тесты, пример, бенчмарк и Doxygen. Результаты
бенчмарка доступны в журнале шага `Benchmark`, в сводке запуска и в артефакте
`benchmark-results`.

При push в `main` после успешного прохождения проверок документация
публикуется на GitHub Pages.

## Структура проекта

```text
quant-sma-cpp/
├── .github/
│   └── workflows/
│       └── ci.yml                     # проверки и публикация документации
├── benchmarks/
│   └── benchmark_moving_average.cpp   # бенчмарк на nanobench
├── include/
│   └── quant/
│       └── moving_average.hpp         # интерфейс и комментарии для Doxygen
├── src/
│   ├── main.cpp                       # пример запуска
│   └── moving_average.cpp             # реализация SMA
├── tests/
│   └── test_moving_average.cpp        # тесты на doctest
├── third_party/
│   ├── doctest/
│   │   ├── doctest.h
│   │   └── LICENSE.txt
│   ├── nanobench/
│   │   ├── nanobench.h
│   │   └── LICENSE
│   └── README.md
├── .gitignore
├── AGENTS.md                          # правила работы ИИ-агента
├── CLAUDE.md                          # подключение AGENTS.md для Claude Code
├── CMakeLists.txt
├── Doxyfile.in
└── README.md
```
