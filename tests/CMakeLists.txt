cmake_minimum_required(VERSION 3.15)

set(MODULE_NAME playground-test)
project(${MODULE_NAME} LANGUAGES C CXX)

add_executable(${MODULE_NAME})

# for unit tests using the google test frmawork
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.0
)
FetchContent_MakeAvailable(googletest)

target_sources(${MODULE_NAME}
    PRIVATE
    ${PROJECT_SOURCE_ROOT}/BashCommand/BashCommand-test.cpp
    ${PROJECT_SOURCE_ROOT}/PropertyBag/PropertyBag-test.cpp
    ${PROJECT_SOURCE_ROOT}/ValueRange/ValueRange-test.cpp
    ${PROJECT_SOURCE_ROOT}/VlanId/VlanId-test.cpp
)

target_link_libraries(${MODULE_NAME}
    PRIVATE
    GTest::gtest_main
    playground-lib::playground-lib

    project::compile_warnings
    project::compile_options
)
