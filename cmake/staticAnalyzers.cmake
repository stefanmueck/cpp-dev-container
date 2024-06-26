find_program(CPPCHECK cppcheck)
if(CPPCHECK)
  option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
endif()

find_program(CLANGTIDY clang-tidy
  NAMES clang-tidy-11 clang-tidy-12 clang-tidy-13 clang-tidy-14)
if(CLANGTIDY)
  option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
endif()

find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
if(INCLUDE_WHAT_YOU_USE)
  option(ENABLE_INCLUDE_WHAT_YOU_USE
         "Enable static analysis with include-what-you-use" OFF)
endif()

function(enable_static_analysis project_name)

    if(ENABLE_CPPCHECK)
        list(
            APPEND CPPCHECK_PROPERTIES "${CPPCHECK}"
                "--enable=all"
                "--enable=style"
                "--enable=warning"
                "--enable=performance"
                "--std=c++20"
                "--inconclusive"
                "--report-progress"
                "--template=gcc"
                "--max-configs=12"
                "--suppress=unmatchedSuppression:*"
                "--suppress=unusedFunction:*"
                "--suppress=missingInclude:*"
                "--suppress=unknownMacro:*"
                "--suppress=toomanyconfigs:*"
                "--suppress=preprocessorErrorDirective:*"
                "--suppress=stlIfFind:*"
                "--suppress=*:*/*_autogen/*"
        )

        set_target_properties(${project_name} PROPERTIES
            CXX_CPPCHECK "${CPPCHECK_PROPERTIES}")

        message(STATUS
            "cppcheck static analysis enabled for ${project_name} (cppcheck: ${CPPCHECK})"
        )
    endif()

    if(ENABLE_CLANG_TIDY)
        # disable clang-tidy for all autogenerated files
        file(WRITE "${CMAKE_BINARY_DIR}/.clang-tidy" "
---
Checks: '-*,llvm-twine-local'
...
")

        list(
            APPEND CLANG_TIDY_PROPERTIES "${CLANGTIDY}" "-p=${PROJECT_BINARY_DIR}"
            "-quiet"
            "-extra-arg-before=-std=c++20"
            "-extra-arg=-Wno-unknown-warning-option"
            "-extra-arg=-Wno-gnu-zero-variadic-macro-arguments"
        )

        set_target_properties(${project_name} PROPERTIES CXX_CLANG_TIDY
            "${CLANG_TIDY_PROPERTIES}")

        message(STATUS
            "clang-tidy static analysis enabled for ${project_name} (clang-tidy: ${CLANGTIDY})"
        )
  endif()

  if(ENABLE_INCLUDE_WHAT_YOU_USE)
    set_target_properties(${project_name} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE
      "${INCLUDE_WHAT_YOU_USE}")
    message(
      STATUS "include-what-you-use static analysis enabled for ${project_name}")
  endif()

endfunction()