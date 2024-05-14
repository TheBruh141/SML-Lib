//
// Created by bruh on 10/6/23.
//

// NOTE : these are just common macros/bindings.
// This can be used as a headless file

#ifndef SML_DIALECT_COMMON_BINDINGS_H
#define SML_DIALECT_COMMON_BINDINGS_H
/// CHANGE THIS TO YOUR DESIRES ///
#define DEBUG
/// UNDEF THIS IF YOU WANT TO RELEASE !! //


#include <stdlib.h>
#include <stdio.h>

// Check if the compiler is mainstream i.e.: Clang, Gcc, cc...
// NOTE: msvc may be mainstream, but it is microsoft and is non-free software.
//       If you are on Windows, please use another compiler...
// REFERENCE: installing clang on windows :: https://scoop.sh/#/apps?q=clang&id=430a8bf29e6c4cbf98cb9e150aa76e663133c6ed
// REFERENCE: installing gcc on windows :: https://scoop.sh/#/apps?q=gcc&id=fd50c09a38b69bd72e3483de086df59b976dcfbd
// REFERENCE: how to install scoop :: https://scoop.sh/

// To make it more compiler agnostic, if a pretty function is not defined, we define it
#if !(__clang__ || __gnu_linux__)  // NOLINT(*-reserved-identifier)

#define __PRETTY_FUNCTION__ __func__ // NOLINT(*-reserved-identifier)

#elif defined (MSC_VER)
#ifndef SML_SUPPRESS_MSVC_WARNING
#warning "[SML_COMMON_BINDINGS] : SML_LIB is being licensed under the BSD 3-clause license. This permits the usage of all compilers, but please note that MSVC is: "
#warning "1. Not free software. "
#warning "2. May not work seamlessly with other systems. (This may not restrict the abilities of SML_LIB but it can impact the capabilities of **YOUR** code in other operating systems). "
#warning "To suppress this message, add the following line at the top of your main file: "
#warning "#define SML_SUPPRESS_MSVC_WARNING "
#endif //SML_SUPPRESS_MSVC_WARNING
#endif //MSC_VER

// this is here for ONLY debug purposes. nearly every compiler will do dead code optimizations so if DEBUG is not defined CHECK statement will not be executed (im %90 sure)
#if (defined DEBUG)
#define CHECK(condition)        \
        do {                    \
            if (!(condition)) { \
                fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->Check failed: %s\nline=%d\n", __PRETTY_FUNCTION__, __LINE__); \
                exit(-1);       \
            }                   \
        } while (0);

#else
#define CHECK(condition)
#endif // (defined DEBUG)

// some quick macros for internal use. they are completely fit for outside use too :d
#define CHECK_MEM(mem_ptr) CHECK(mem_ptr != NULL)

#define EXIT_WITH_INFO (fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->exiting here : %s\nfile=%s\nline=%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__))
#define SML_FUNCTION_INFO(stream)\
do {                           \
fprintf(stream, "[SML_COMMON_BINDINGS] -> file : %s, function : %s ,line : %d",__FILE__, __PRETTY_FUNCTION__, __LINE__ );\
} while(0)

#define SML_LOG_INFO(stream, name, ...) \
do {                           \
fprintf(stream, "[%s] :: INFO ->  %s, file : %s, function : %s ,line : %d", name, __VA_ARGS__, __FILE__, __PRETTY_FUNCTION__, __LINE__ );\
} while(0)

#define sml_byte_t unsigned char

// void* but *-*fancy*-* :D
// tbh it is used for clarify if you are actually pointing to a datastructures or an array.
// i.e.:
//     sml_pointer a = &var;
//     void* a = another_var;
// in the end both are interchangeable with another :D
#define sml_pointer void*

#define sml_size unsigned long long
// signed version of sml_size_t
#define sml_size_s long long

// returns the number of elements in an array
#define sizeof_arr(x) (sizeof(x) / sizeof(x[0]))

// returns the number of elements in __VA_ARGS__
#define sizeof_va(...) (sizeof(__VA_ARGS__) / sizeof(__VA_ARGS__[0]))


// basic error reporting for libraries. we don't want to depend on errors_and_logging.c
typedef enum {
    Sml_Fail = 0,
    Sml_Success = 1,
    Sml_Improper_Function_Use = 2,
} __attribute__((__packed__)) sml_common_error;



#endif //SML_DIALECT_COMMON_BINDINGS_H
