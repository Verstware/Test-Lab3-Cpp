cmake_minimum_required(VERSION 3.14)
project(ShoppingCartCPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(--coverage -O0 -g)
add_link_options(--coverage)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(shopping_cart_test tests/test_shopping_cart.cpp)

target_include_directories(shopping_cart_test PRIVATE include)

target_link_libraries(shopping_cart_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(shopping_cart_test)