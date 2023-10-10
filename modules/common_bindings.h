//
// Created by bruh on 10/6/23.
//

// NOTE : these are just common macros/bindings.
// This can be used as a headless file

#ifndef SML_DIALECT_COMMON_BINDINGS_H
#define SML_DIALECT_COMMON_BINDINGS_H

#include <stdlib.h>

#ifndef SML_LIB_ERRORS_AND_LOGGING_H
#define CHECK(condition)    \
    do {                    \
        if (!(condition)) { \
            fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->Check failed: %s\nline=%d\n", __PRETTY_FUNCTION__, __LINE__); \
            exit(-1);       \
        }                  \
    } while (0)
#endif // SML_LIB_ERRORS_AND_LOGGING_H


#define sml_byte_t unsigned char

#define sml_size_t unsigned long long
// signed version of sml_size_t
#define sml_size_t_s long long
#endif //SML_DIALECT_COMMON_BINDINGS_H
