//
// Created by bruh on 10/6/23.
//

#ifndef SML_DIALECT_ALLOCATORS_H
#define SML_DIALECT_ALLOCATORS_H

void *sml_mem_alloc(unsigned long long how_much, unsigned long long sizeof_mem);

void *sml_mem_malloc(unsigned long long size);

void *sml_mem_calloc(unsigned long long how_much, unsigned long long sizeof_mem);

void *sml_mem_realloc(void *ptr, unsigned long long new_requested_size, short unsigned retry);

// a derivative of sml_mem_realloc.
// rather than relying on realloc,
// it tries to allocate a different memory on failure
void *sml_mem_realloc_change_place(void *ptr, unsigned long long new_requested_size);



#endif //SML_DIALECT_ALLOCATORS_H
