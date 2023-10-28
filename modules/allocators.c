//
// Created by bruh on 10/6/23.
//

#include "allocators.h"
#include "common_bindings.h"
#include <stdlib.h>
#include <stdio.h>


#define DEBUG 1


void *sml_mem_alloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    // check for overflow and underflow
    CHECK(how_much > 0 &&
          sizeof_mem > 0 &&
          how_much * sizeof_mem > how_much
    );

#if (DEBUG == 1)
    return sml_mem_calloc(how_much, sizeof_mem);
#else
    return sml_malloc(how_much* sizeof_mem);
#endif
}


void *__attribute_malloc__ sml_mem_malloc(unsigned long long size) {
    void *new_mem = malloc(size);
    CHECK(new_mem == NULL);
    return new_mem;
}

void *__attribute_malloc__ sml_mem_calloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    void *new_mem = calloc(how_much, sizeof_mem);
    return new_mem;
}

void *sml_mem_realloc(void *ptr, unsigned long long new_requested_size) {
    void *new_mem = realloc(ptr, new_requested_size);
    if (new_mem == NULL) {

#ifdef SML_LIB_ERRORS_AND_LOGGING_H
        sml_error_config config = init_sml_error("SMOL_REALLOC", false, NULL);
        sml_throw_error_non_blocking(&config, ERROR_MEMORY_REALLOCATION, LOG_SEVERITY_ERROR, "cannot realloc on %s\nline = %d",
                        __PRETTY_FUNCTION__, __LINE__);
#else
        printf("SMOL_REALLOC HAS FAILED. IF YOU WANT DETAILED ERROR LOGS PLEASE INCLUDE errors_and_logging.h IN YOUR FILE\n");
        printf("cannot realloc on %s \nline = %d\",\n", __PRETTY_FUNCTION__, __LINE__);
#endif
        free(ptr);
    }
    return new_mem;
}

void *sml_mem_realloc_s(void *ptr, unsigned long long new_requested_size) {
    void *new_mem = realloc(ptr, new_requested_size);
    if (new_mem == NULL) {

#ifdef SML_LIB_ERRORS_AND_LOGGING_H
        sml_error_config config = init_sml_error("SMOL_REALLOC_S", false, NULL);
                sml_throw_error_non_blocking(&config, ERROR_MEMORY_REALLOCATION, LOG_SEVERITY_ERROR, "cannot realloc on retrying %s\nline = %d",
                                __PRETTY_FUNCTION__, __LINE__);
#else
        printf("SMOL_REALLOC HAS FAILED. RETRYING . IF YOU WANT DETAILED ERROR LOGS PLEASE INCLUDE errors_and_logging.h IN YOUR FILE\n");
        printf("cannot realloc on %s \nline = %d\",\n", __PRETTY_FUNCTION__, __LINE__);
#endif
        free(new_mem);
        void *another_mem = sml_mem_alloc(new_requested_size, 1);
        return another_mem;
    }
    return new_mem;
}



// --- Typesets

