cmake_minimum_required(VERSION 3.26)
project(SML_lib C)

set(CMAKE_C_STANDARD 23)
# Define the source files for the library
add_library(SML_lib
        modules/allocators.c
        modules/errors_and_logging.c
        modules/math.c
        modules/math.h
        modules/argument_parsing.c
        modules/argument_parsing.h
        modules/for_each.h
        modules/sml_str.c
        modules/sml_str.h
        modules/file_utils.c
        modules/file_utils.h
        modules/terminal_colors.h
        modules/sml_cstr.c
        modules/sml_cstr.h
        modules/internal_lib_utils.h
)


# Define the header files for the library (if needed)
target_include_directories(SML_lib PUBLIC
        modules)

# Define the source files for the executable
add_executable(demo
        demo.c
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
endif ()

# Link the library to the executable
target_link_libraries(demo PRIVATE SML_lib)
if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif ()