cmake_minimum_required(VERSION 3.26)
project(SML_lib C)

set(CMAKE_C_STANDARD 23)

include(FetchContent)

# Fetch Unity testing framework
FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG v2.5.2  # Stable version
)
FetchContent_MakeAvailable(unity)

# Common source files for the library
set(SML_LIB_SOURCES
        modules/allocators.c
        modules/errors_and_logging.c
        modules/argument_parsing.c
        modules/sml_str.c
        modules/file_utils.c
        modules/linalg.c
)

# Build main library
add_library(SML_lib ${SML_LIB_SOURCES})
target_include_directories(SML_lib PUBLIC modules)

# Demo executable
add_executable(demo demo.c)
target_link_libraries(demo PRIVATE SML_lib)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
#    when using clang diagnostic features and other compiler specific tomfoolery we are
#    we are hit in the face with `-Werror=unknown-pragmas` so we close it, it does not
#    compromise anything.
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-error=unknown-pragmas)
endif()

# Enable testing
enable_testing()

# Add Unity-based tests
if(EXISTS ${CMAKE_SOURCE_DIR}/tests)
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.c)

    foreach(TEST_SRC ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

        # Determine if this test requires custom malloc failure behavior
        if(TEST_NAME MATCHES ".*malloc_fail$")
            message(STATUS "Test '${TEST_NAME}' requires SML_ALLOC_FAILURE")

            # Create a dedicated lib variant with macro
            add_library(SML_lib_${TEST_NAME} ${SML_LIB_SOURCES})
            target_include_directories(SML_lib_${TEST_NAME} PUBLIC modules)
            target_compile_definitions(SML_lib_${TEST_NAME} PRIVATE SML_ALLOC_FAILURE)
            set(TEST_LIB SML_lib_${TEST_NAME})
        else()
            set(TEST_LIB SML_lib)
        endif()

        # Define the test executable
        add_executable(${TEST_NAME} ${TEST_SRC})
        target_link_libraries(${TEST_NAME} PRIVATE ${TEST_LIB} unity)
        target_include_directories(${TEST_NAME} PRIVATE ${unity_SOURCE_DIR}/src)

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()
