cmake_minimum_required(VERSION 3.26)
project(SML_lib C)

set(CMAKE_C_STANDARD 23)
# Define the source files for the library
add_library(SML_lib
        modules/literal_array.c
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
        demo.c
        modules/loading_bars.c
        modules/loading_bars.h
        modules/terminal_colors.h
)


# Define the header files for the library (if needed)
target_include_directories(SML_lib PUBLIC
        modules)

# Define the source files for the executable
add_executable(demo
        demo.c)

# Link the library to the executable
target_link_libraries(demo PRIVATE SML_lib)
if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif ()