# quant-sma-cpp

Учебный проект по программной инженерии и C++ для количественного анализа.
Вычисляет простую скользящую среднюю (SMA) финансового временного ряда.

[Документация Doxygen](https://mantven.github.io/quant-sma-cpp/)
| [Запуски CI](https://github.com/mantven/quant-sma-cpp/actions)

## Что делает программа

Для цен `100, 102, 101, 105, 107` и окна 3 демонстрационная программа печатает:

```text
SMA(3): 101.00 102.67 104.33
```

Библиотечная функция `quant::simple_moving_average(prices, window)` возвращает
средние по всем полным окнам. Результат содержит `N - window + 1` элементов.
Реализация обновляет сумму окна за O(1), общая сложность O(N).
Промежуточная сумма хранится в `long double`; как и в любом вычислении с
плавающей точкой, возможна погрешность округления.
Нулевое окно, окно больше входа, пустой вход, NaN и бесконечности отклоняются
исключением `std::invalid_argument`. Переполнение суммы даёт `std::overflow_error`.

## Сборка и запуск

Требования: CMake >= 3.20, компилятор C++17 (GCC, Clang или MSVC).
doctest и nanobench включены в `third_party`, скачивать зависимости не требуется.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
./build/quant_demo
ctest --test-dir build --output-on-failure
./build/quant_benchmark
```

Windows с MinGW и Ninja:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
.\build\quant_demo.exe
ctest --test-dir build --output-on-failure
.\build\quant_benchmark.exe
```

Для Visual Studio используйте `cmake -S . -B build`, затем
`cmake --build build --config Release`, `ctest --test-dir build -C Release
--output-on-failure` и бинарники из `build/Release/`.

## Тесты и измерение скорости

doctest проверяет известные средние, размеры окна 1 и N, отрицательные цены,
пустой вход, неверные окна и нечисловые данные. Отдельный тест сравнивает
результат с прямым расчётом для пяти размеров окна.

nanobench измеряет обработку 1 000, 10 000 и 100 000 цен с окном 20.
В замер входят валидация входа, выделение памяти и вычисление SMA.
Есть прогрев, повторные измерения и защита результата от удаления оптимизатором.
Таблица содержит время на цену и число цен в секунду. Результаты зависят от
машины и нагрузки; автоматического порога производительности нет.

## Документация

Установите Doxygen, затем повторите конфигурацию CMake и выполните:

```sh
cmake --build build --target docs
```

Откройте `build/docs/html/index.html`.
В CI Doxygen установлен автоматически; предупреждения считаются ошибками.

## Автоматизация

При каждом push и pull request GitHub Actions собирает Release, запускает
тесты, пример и бенчмарк, генерирует документацию. Измерения видны в журнале
шага Benchmark и в сводке запуска; отчёт и HTML доступны также как артефакты.
После успешных проверок push в `main` публикует документацию на GitHub Pages.

При первом размещении в GitHub в **Settings → Pages → Build and deployment**
нужно выбрать **Source: GitHub Actions**. Основная ветка должна называться `main`.
После этого выполните push или повторите workflow исходного push через Re-run
all jobs. При переносе в другой аккаунт обновите ссылки выше.

## Структура

```text
include/quant/    публичный интерфейс
src/             реализация и пример
tests/           unit-тесты doctest
benchmarks/      бенчмарк nanobench
third_party/     библиотеки и лицензии
.github/         GitHub Actions
Doxyfile.in      настройка Doxygen
AGENTS.md        правила работы ИИ-агента
CLAUDE.md        подключение правил для Claude Code
```
