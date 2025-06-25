//
// Created by bruh on 10/6/23.
//

// NOTE : these are just common macros/bindings.
// This can be used as a headless file

#ifndef SML_COMMON_BINDINGS_H
#define SML_COMMON_BINDINGS_H

#include <stdio.h>
#include <stdlib.h>

// Check if the compiler is mainstream i.e.: Clang, Gcc, cc...
// NOTE: MSVC may be mainstream, but it is microsoft and is non-free software.
// REFERENCE: installing clang on windows :: https://scoop.sh/#/apps?q=clang&id=430a8bf29e6c4cbf98cb9e150aa76e663133c6ed
// REFERENCE: installing gcc on windows :: https://scoop.sh/#/apps?q=gcc&id=fd50c09a38b69bd72e3483de086df59b976dcfbd
// REFERENCE: how to install scoop :: https://scoop.sh/

// To make it more compiler agnostic, if a pretty function is not defined, we define it
#if (__clang__ || __gnu_linux__)  // NOLINT(*-reserved-identifier)

#define __PRETTY_FUNCTION__ __func__ // NOLINT(*-reserved-identifier)

#endif


// this is here for ONLY debug purposes. nearly every compiler will do dead code optimizations so if DEBUG is not defined CHECK statement will not be executed (im %90 sure)
#if (defined DEBUG && !defined CHECK)
#define CHECK(condition)        \
        do {                    \
            if (!(condition)) { \
                fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->Check failed: %s\nline=%d\n", __PRETTY_FUNCTION__, __LINE__); \
                exit(-1);       \
            }                   \
        } while (0);

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
#define sml_byte4_t sml_byte_t[4]
#define sml_byte8_t sml_byte_t[8]

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

// basic error reporting for libraries. we don't want to depend on errors_and_logging.c

typedef enum {
    Sml_Fail = 0,
    Sml_Success = 1,
    Sml_Imporper_Function_Use = 2,
} __attribute__((__packed__)) sml_common_error;

#endif //SML_COMMON_BINDINGS_H
