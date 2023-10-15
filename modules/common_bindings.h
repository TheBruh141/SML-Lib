//
// Created by bruh on 10/6/23.
//

// NOTE : these are just common macros/bindings.
// This can be used as a headless file

#ifndef SML_DIALECT_COMMON_BINDINGS_H
#define SML_DIALECT_COMMON_BINDINGS_H

#include <stdlib.h>

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

#define sml_size_t unsigned long long
// signed version of sml_size_t
#define sml_size_t_s long long


#endif //SML_DIALECT_COMMON_BINDINGS_H
