#include "allocators.h" // Include your own header

#include <stdio.h>  // For fprintf
#include <string.h> // For memcpy
#include <stdlib.h> // For malloc, calloc, free, NULL
#include <limits.h> // For ULLONG_MAX

// Define DEBUG for internal testing/behavior if it's not defined by the build system
// #define DEBUG

// Define SML_ALLOC_FAILURE etc. for simulating failures for testing
// #define SML_ALLOC_FAILURE
// #define SML_MALLOC_FAILURE
// #define SML_CALLOC_FAILURE


// --- Core Allocators (Implementation) ---

void *sml_alloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    // Check for overflow before multiplication to prevent wrap-around.
    // This is a critical check for safety in high-reliability systems.
    if (how_much > 0 && sizeof_mem > 0 && (ULLONG_MAX / how_much < sizeof_mem)) {
        fprintf(stderr, "[SML | Allocators Error] Overflow detected during allocation request: %llu * %llu. Returning NULL.\n", how_much, sizeof_mem);
        return NULL;
    }
    // Handle cases where 0 bytes or 0 elements are requested.
    if (how_much == 0 || sizeof_mem == 0) {
        return NULL; // Consistent behavior for zero-size allocation
    }

#if defined(DEBUG)
    // In DEBUG mode, always use calloc for zero-initialization to help catch
    // uses of uninitialized memory.
    return sml_calloc(how_much, sizeof_mem);
#else
    // In release, use malloc directly for performance if zero-initialization
    // isn't strictly required by the user at this wrapper level.
    return sml_malloc(how_much * sizeof_mem);
#endif
}

void *__attribute_malloc__ sml_malloc(unsigned long long size) {
    if (size == 0) {
        return NULL; // malloc(0) behavior is implementation-defined; return NULL for safety.
    }

#if (defined SML_ALLOC_FAILURE || defined SML_MALLOC_FAILURE)
    // Simulate malloc failure for testing purposes.
    fprintf(stderr, "[SML | Allocators Debug] Simulating malloc failure for testing (size: %llu). Returning NULL.\n", size);
    return NULL;
#else
    void *new_mem = malloc(size);
    if (new_mem == NULL) {
        fprintf(stderr, "[SML | Allocators Error] Failed to allocate %llu bytes of memory. Returning NULL.\n", size);
    }
    return new_mem;
#endif
}

void *__attribute_malloc__ sml_calloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    if (how_much == 0 || sizeof_mem == 0) {
        return NULL; // calloc(0, X) or calloc(X, 0) behavior is implementation-defined; return NULL for safety.
    }
    // Check for overflow before multiplication (important for total size calculation).
    if (ULLONG_MAX / how_much < sizeof_mem) {
        fprintf(stderr, "[SML | Allocators Error] Overflow detected during calloc request: %llu * %llu. Returning NULL.\n", how_much, sizeof_mem);
        return NULL;
    }

#if (defined SML_ALLOC_FAILURE || defined SML_CALLOC_FAILURE)
    // Simulate calloc failure for testing purposes.
    fprintf(stderr, "[SML | Allocators Debug] Simulating calloc failure for testing (%llu * %llu). Returning NULL.\n", how_much, sizeof_mem);
    return NULL;
#else
    void *new_mem = calloc(how_much, sizeof_mem);
    if (new_mem == NULL) {
        fprintf(stderr, "[SML | Allocators Error] Failed to allocate %llu elements of %llu bytes each (calloc). Returning NULL.\n", how_much, sizeof_mem);
    }
    return new_mem;
#endif
}

void *sml_realloc(void *ptr, unsigned long long new_requested_size, short unsigned retry) {
    // Standard realloc behavior:
    // If ptr is NULL, it behaves like malloc(new_requested_size).
    // If new_requested_size is 0, and ptr is not NULL, it behaves like free(ptr) and returns NULL.

    if (new_requested_size == 0) {
        if (ptr != NULL) {
            free(ptr);
        }
        return NULL; // Reallocating to 0 bytes implies freeing
    }

    void *new_mem = NULL;
    unsigned short current_retry = 0;

    do {
        new_mem = realloc(ptr, new_requested_size);
        if (new_mem != NULL) {
            return new_mem; // Success
        }

        // Only log a warning if retries are configured and we are actually retrying.
        if (current_retry < retry) {
            fprintf(stderr, "[SML | Allocators Warning] Realloc attempt %hu/%hu failed for %llu bytes. Retrying...\n",
                    current_retry + 1, (unsigned short)(retry + 1), new_requested_size);
        }
        current_retry++;
    } while (current_retry <= retry); // Loop as long as current_retry is within allowed retries

    // If loop finishes, realloc failed after all retries.
    fprintf(stderr, "[SML | Allocators Error] Reallocation failed after %hu attempts for %llu bytes. Original pointer remains valid.\n",
            (unsigned short)(retry + 1), new_requested_size);
    return NULL; // Reallocation failed, original 'ptr' is still valid.
}


// --- New realloc_change_place implementations (Implementation) ---

void *sml_realloc_change_place_bytes(void *ptr, unsigned long long old_size_in_bytes, unsigned long long new_size_in_bytes) {
    if (new_size_in_bytes == 0) {
        // If the new size is 0, it means we want to free the old memory.
        if (ptr != NULL) {
            free(ptr);
        }
        return NULL;
    }

    // Allocate the new memory block.
    void *new_mem = sml_malloc(new_size_in_bytes);
    if (new_mem == NULL) {
        // If allocation fails, print an error and return NULL.
        // The original 'ptr' is still valid and not freed in this case.
        fprintf(stderr, "[SML | Allocators Error] Failed to allocate %llu bytes for new memory block in sml_realloc_change_place_bytes. Original pointer remains valid.\n",
                new_size_in_bytes);
        return NULL;
    }

    // If the original pointer is valid, copy its contents.
    if (ptr != NULL) {
        // Copy the minimum of the old size and the new size to prevent out-of-bounds reads.
        unsigned long long bytes_to_copy = (old_size_in_bytes < new_size_in_bytes) ? old_size_in_bytes : new_size_in_bytes;
        memcpy(new_mem, ptr, bytes_to_copy);

        // Free the original memory block after successful copy.
        free(ptr);
    }

    return new_mem;
}

void *sml_realloc_change_place_elements(void *ptr, unsigned long long old_num_elements, unsigned long long element_size, unsigned long long new_num_elements) {
    if (element_size == 0) {
        fprintf(stderr, "[SML | Allocators Error] Element size cannot be zero in sml_realloc_change_place_elements. Returning NULL.\n");
        return NULL;
    }

    if (new_num_elements == 0) {
        // If the new element count is 0, free the old memory.
        if (ptr != NULL) {
            free(ptr);
        }
        return NULL;
    }

    // Check for overflow before calculating total new size.
    if (ULLONG_MAX / new_num_elements < element_size) {
        fprintf(stderr, "[SML | Allocators Error] Overflow detected during new element allocation request: %llu * %llu. Returning NULL.\n", new_num_elements, element_size);
        return NULL;
    }

    // Allocate the new memory block, zero-initialized.
    void *new_mem = sml_calloc(new_num_elements, element_size);
    if (new_mem == NULL) {
        // If allocation fails, print an error and return NULL.
        fprintf(stderr, "[SML | Allocators Error] Failed to allocate %llu elements of size %llu in sml_realloc_change_place_elements. Original pointer remains valid.\n",
                new_num_elements, element_size);
        return NULL;
    }

    // If the original pointer is valid, copy its contents.
    if (ptr != NULL) {
        // Check for overflow before calculating old total size.
        if (ULLONG_MAX / old_num_elements < element_size) {
            fprintf(stderr, "[SML | Allocators Warning] Overflow detected when calculating old_total_bytes for memcpy. Potential data truncation in sml_realloc_change_place_elements.\n");
            // Proceed with copy, but warn, as this indicates a potentially invalid old_num_elements or element_size.
        }

        unsigned long long old_total_bytes = old_num_elements * element_size;
        unsigned long long new_total_bytes = new_num_elements * element_size;

        // Copy the minimum of the old total bytes and the new total bytes.
        unsigned long long bytes_to_copy = (old_total_bytes < new_total_bytes) ? old_total_bytes : new_total_bytes;
        memcpy(new_mem, ptr, bytes_to_copy);

        // Free the original memory block.
        free(ptr);
    }

    return new_mem;
}