cmake_minimum_required(VERSION 3.15)

################################################################
# main module
set(MODULE_NAME playground)
project(${MODULE_NAME} LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(cmake/standardProjectSettings.cmake)
include(cmake/preventInSourceBuilds.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE OFF CACHE STRING "" FORCE)
set(CMAKE_COLOR_MAKEFILE   OFF CACHE STRING "" FORCE)

enable_testing()

################################################################
# project warnings
add_library(project_warnings INTERFACE)
add_library(project::compile_warnings ALIAS project_warnings)
include(cmake/compilerWarnings.cmake)
set_project_warnings(project_warnings)

################################################################
# project options
add_library(project_options INTERFACE)
add_library(project::compile_options ALIAS project_options)
target_compile_features(project_options INTERFACE cxx_std_20)

################################################################
# enable cache system
include(cmake/cache.cmake)

################################################################
# disassembly
option(GENERATE_DISSASSEMBLY "Generate Dissassembly" OFF)
if(GENERATE_DISSASSEMBLY)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps -masm=intel")
endif(GENERATE_DISSASSEMBLY)

################################################################
# additional artefacts
add_subdirectory(src)

################################################################
# artefact
add_executable(${MODULE_NAME})

################################################################
# sources
target_sources(${MODULE_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

################################################################
# includes
target_include_directories(${MODULE_NAME}
  PRIVATE
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

################################################################
# link dependencies
target_link_libraries(${MODULE_NAME}
  PUBLIC
  playground-lib::playground-lib
  project::compile_warnings
  project::compile_options
)

################################################################
# allow for static analysis options
include(staticAnalyzers)
enable_static_analysis(${MODULE_NAME})

################################################################
# allow for sanitizers
include(sanitizers)
enable_sanitizers(${MODULE_NAME})

################################################################
# install
install(TARGETS ${MODULE_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

################################################################
# testing
option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)

  option(TESTING_USE_GTEST "Use googletest as testing framework" ON)
  option(TESTING_USE_CATCH "Use Catch2 with trompeloeil as testing framework" OFF)

  if(TESTING_USE_GTEST AND TESTING_USE_CATCH)
    message(FATAL_ERROR "Please enable only ONE testing framework.")
  endif()

  set(MODULE_TEST_NAME ${PROJECT_NAME}-test)
  add_executable(${MODULE_TEST_NAME})

  if(TESTING_USE_GTEST)
    message(STATUS "Testing: Using google test.")
    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.0)
    FetchContent_MakeAvailable(googletest)

    target_sources(${MODULE_TEST_NAME}
      PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/square-test-gtest.cpp
    )

    target_link_libraries(${MODULE_TEST_NAME}
      PRIVATE
      GTest::gtest_main
      playground-lib::playground-lib
    )
  elseif(TESTING_USE_CATCH)
    message(STATUS "Testing: Using Catch2 with trompeloeil.")
    find_package(Catch2 REQUIRED)
    find_package(trompeloeil REQUIRED)  
          
    target_sources(${MODULE_TEST_NAME}
      PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/square-test.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/unittest-main.cpp
    )    

    target_link_libraries(${MODULE_TEST_NAME}
      PRIVATE
      Catch2::Catch2
      trompeloeil::trompeloeil
      playground-lib::playground-lib
    )
  else()
    message(FATAL_ERROR "No testing framework specified.")
  endif(TESTING_USE_GTEST)

  target_compile_options(${MODULE_TEST_NAME}
    PRIVATE
    ${COMPILE_WARNING_AS_ERROR}
    -Wall
    -Wextra
  )
endif(ENABLE_TESTING)
