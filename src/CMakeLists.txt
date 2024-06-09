cmake_minimum_required(VERSION 3.15)

set(MODULE_NAME playground-lib)
project(${MODULE_NAME} LANGUAGES C CXX)

################################################################
# artefact
add_library(${MODULE_NAME} STATIC)
add_library(${MODULE_NAME}::${MODULE_NAME} ALIAS ${MODULE_NAME})

################################################################
# sources
target_sources(${MODULE_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/square.h
  ${CMAKE_CURRENT_SOURCE_DIR}/square.cpp
)

################################################################
# includes
target_include_directories(${MODULE_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

################################################################
# link dependencies
target_link_libraries(${MODULE_NAME}
    PUBLIC
    project::compile_warnings
    project::compile_options
)

# allow for static analysis options
include(staticAnalyzers)
enable_static_analysis(${MODULE_NAME})