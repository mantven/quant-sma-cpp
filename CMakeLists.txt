cmake_minimum_required(VERSION 3.20)
project(quant_sma_cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(quant src/moving_average.cpp)
target_include_directories(quant PUBLIC include)
if(MSVC)
  target_compile_options(quant PRIVATE /W4 /WX)
else()
  target_compile_options(quant PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(quant_demo src/main.cpp)
target_link_libraries(quant_demo PRIVATE quant)

include(CTest)
if(BUILD_TESTING)
  add_executable(quant_tests tests/test_moving_average.cpp)
  target_include_directories(quant_tests SYSTEM PRIVATE third_party/doctest)
  target_link_libraries(quant_tests PRIVATE quant)
  add_test(NAME moving_average COMMAND quant_tests)
endif()

add_executable(quant_benchmark benchmarks/benchmark_moving_average.cpp)
target_include_directories(quant_benchmark SYSTEM PRIVATE third_party/nanobench)
target_link_libraries(quant_benchmark PRIVATE quant)

find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(docs
    COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Generating Doxygen documentation" VERBATIM)
endif()
