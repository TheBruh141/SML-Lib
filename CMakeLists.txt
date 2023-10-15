cmake_minimum_required(VERSION 3.26)
project(sml_dialect C)


set(CMAKE_C_STANDARD 23)
# Define the source files for the library
add_library(sml_dialect
        modules/literal_array.c
        modules/allocators.c
        modules/errors_and_logging.c
        modules/math.c
        modules/math.h
        modules/argument_parsing.c
        modules/argument_parsing.h
)

# Define the header files for the library (if needed)
target_include_directories(sml_dialect PUBLIC
        modules)

# Define the source files for the executable
add_executable(demo
        demo.c)

# Link the library to the executable
target_link_libraries(demo PRIVATE sml_dialect)