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
# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

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
    add_subdirectory(tests)
endif(ENABLE_TESTING)
