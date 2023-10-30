//
// Created by bruhpc on 10/23/23.
//

#include <stdio.h>
#include "common_bindings.h"
#include "allocators.h"

#define DEBUG

int main(void) {
    // generate tests for array.c
    sml_size *a = sml_mem_alloc(100, sizeof(sml_size));
    for (int i = 0; i < 100; i++) {
        a[i] = i;
        printf("%d - %llu\n",i, a[i]);
    }
    sml_size *b = sml_mem_realloc_change_place(a, 200);
    for (int i = 100; i < 200; i++) {
        b[i] = i;
        printf("%d - %llu\n",i, b[i]);
    }
    free(a);
    return 0;
}