//
// Created by bruh on 5/14/24.
//

// this file was created for ease of internal debugging and end user debugging.
// if this makes no sense to you just read the file and you'll get what I'm saying.
// happy coding :D
#ifndef SML_LIB_INTERNAL_LIB_UTILS_H
#define SML_LIB_INTERNAL_LIB_UTILS_H

#ifdef _STDLIB_H// if stdlib is being used
#define s_internal_throw_err(err_code, err_msg, should_halt) \
    do {                                                                  \
        fprintf(stderr, "\n[SML_INTERNAL_LIB_UTILS]\n\t->%s\n", err_msg); \
        if (should_halt) {                                                \
            exit(err_code);                                               \
        }                                                                 \
    } while (0)
#else

#define s_internal_throw_err(err_code, err_msg, should_halt)                                                                                                                                                                \
    do {                                                                                                                                                                                                                                 \
        fprintf(stderr, "\n[SML_INTERNAL_LIB_UTILS]\n\t->%s\n", err_msg);                                                                                                                                                                \
        if (should_halt) {                                                                                                                                                                                                               \
            fprintf(stderr, "\n\e[0;31m[SML_INTERNAL_LIB_UTILS]\n\t:: this should halt but since there is no stlib or exit function defined it is up to you (and the will of the computer) to do whats next... [%s]\e[0;37m", err_code); \
        }                                                                                                                                                                                                                                \
    } while (0)
#endif

#endif//SML_LIB_INTERNAL_LIB_UTILS_H
