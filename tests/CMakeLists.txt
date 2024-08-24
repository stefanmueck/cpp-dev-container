cmake_minimum_required(VERSION 3.15)

set(MODULE_NAME playground-test)
project(${MODULE_NAME} LANGUAGES C CXX)

add_executable(${MODULE_NAME})

option(TESTING_USE_GTEST "Use googletest as testing framework" ON)
option(TESTING_USE_CATCH "Use Catch2 with trompeloeil as testing framework" OFF)

# for unit tests using the google test frmawork
if(TESTING_USE_GTEST)
    message(STATUS "Testing: Using google test.")
    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.0)
    FetchContent_MakeAvailable(googletest)

    target_sources(${MODULE_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/square-test-gtest.cpp
    )

    target_link_libraries(${MODULE_NAME}
        PRIVATE
        GTest::gtest_main
        playground-lib::playground-lib

        project::compile_warnings
        project::compile_options
    )
endif(TESTING_USE_GTEST)    
  
# for unit tests using the catch2 with the trompeloeil framwork
if(TESTING_USE_CATCH)
    message(STATUS "Testing: Using Catch2 with trompeloeil.")
    find_package(Catch2 REQUIRED)
    find_package(trompeloeil REQUIRED)  
          
    target_sources(${MODULE_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/square-test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/unittest-main.cpp
    )    

    target_link_libraries(${MODULE_NAME}
        PRIVATE
        Catch2::Catch2
        trompeloeil::trompeloeil
        playground-lib::playground-lib

        project::compile_warnings
        project::compile_options
    )
endif(TESTING_USE_CATCH)
