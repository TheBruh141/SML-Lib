//
// Created by bruh on 10/6/23.
//

// NOTE : these are just common macros/bindings.
// This can be used as a headless file

#ifndef SML_DIALECT_COMMON_BINDINGS_H
#define SML_DIALECT_COMMON_BINDINGS_H

#include <stdlib.h>

// Check if the compiler is mainstream ie.: Clang, Gcc, cc...
// NOTE: msvc may be mainstream but it is microsoft and is non-free software.
//       If you are on Windows, please use another compiler...
// REFERENCE: installing clang on windows :: https://scoop.sh/#/apps?q=clang&id=430a8bf29e6c4cbf98cb9e150aa76e663133c6ed
// REFERENCE: installing gcc on windows :: https://scoop.sh/#/apps?q=gcc&id=fd50c09a38b69bd72e3483de086df59b976dcfbd
// REFERENCE: how to install scoop :: https://scoop.sh/
// REFERENCE: why is windows non-free software :: http://web.archive.org/web/20231022185342/https://en.wikipedia.org/wiki/Proprietary_software

// To make it more compiler agnostic, if a pretty function is not defined, we define it
#if (__clang__ || __gnu_linux__)  // NOLINT(*-reserved-identifier)

#define __PRETTY_FUNCTION__ "__PRETTY_FUNCTION__ is not supported by your compiler. please use a compiler that supports it. this is directly a compiler problem."

#ifdef MSC_VER
#ifndef SML_SUPPRESS_MSVC_WARNING
#warning "[SML_COMMON_BINDINGS] : SML_LIB is being licensed under the BSD 3-clause license. This permits the usage of all compilers, but please note that MSVC is: "
#warning "1. Not free software. "
#warning "2. May not work seamlessly with other systems. (This may not restrict the abilities of SML_LIB but it can impact the capabilities of **YOUR** code in other operating systems). "
#warning "To suppress this message, add the following line at the top of your main file: "
#warning "#define SML_SUPPRESS_MSVC_WARNING "
#endif //SML_SUPPRESS_MSVC_WARNING
#endif //MSC_VER
#endif

#ifndef CHECK
#define CHECK(condition)    \
    do {                    \
        if (!(condition)) { \
            fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->Check failed: %s\nline=%d\n", __PRETTY_FUNCTION__, __LINE__); \
            exit(-1);       \
        }                  \
    } while (0)
#endif


#define CHECK_MEM(mem_ptr) CHECK(mem_ptr != NULL)

#define EXIT_WITH_INFO (fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->exiting here : %s\nfile=%s\nline=%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__))

#define each(item, array, length) \
(typeof(*(array)) *p = (array), (item) = *p; p < &((array)[length]); p++, (item) = *p)

#define sml_byte_t unsigned char
#define sml_byte4_t sml_byte_t[4]
#define sml_byte8_t sml_byte_t[8]

#define sml_size unsigned long long
// signed version of sml_size_t
#define sml_size_s long long


#endif //SML_DIALECT_COMMON_BINDINGS_H
