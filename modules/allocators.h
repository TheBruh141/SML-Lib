#ifndef SML_ALLOCATORS_H
#define SML_ALLOCATORS_H

#include <stdlib.h>

// Note: __attribute_malloc__ is a GCC/Clang extension that tells the compiler
// that the function returns a pointer to newly allocated memory that is
// not aliased by any other pointer. This helps with optimizations.

/**
 * @brief Allocates `how_much` elements, each of `sizeof_mem` bytes.
 *
 * This function acts as a wrapper for `sml_calloc` in DEBUG mode
 * (if DEBUG is defined during compilation, e.g., -DDEBUG)
 * and `sml_malloc` otherwise. This ensures zero-initialization during debug
 * for easier bug detection, without a performance penalty in release builds.
 *
 * @param how_much The number of elements to allocate. Must not cause an overflow when multiplied by `sizeof_mem`.
 * @param sizeof_mem The size of each element in bytes. Must be greater than 0.
 * @return A pointer to the newly allocated memory, or NULL if allocation fails or parameters are invalid.
 * On failure, an error message is printed to stderr.
 *
 * @how_to
 * // Allocate space for 10 integers
 * int *my_ints = (int*)sml_alloc(10, sizeof(int));
 * if (my_ints == NULL) {
 * // Handle allocation error
 * fprintf(stderr, "Failed to allocate memory for 10 integers.\n");
 * }
 *
 * // Allocate space for a single struct
 * typedef struct { int x, y; } MyStruct;
 * MyStruct *my_struct = (MyStruct*)sml_alloc(1, sizeof(MyStruct));
 * if (my_struct == NULL) {
 * // Handle allocation error
 * }
 */
void *sml_alloc(unsigned long long how_much, unsigned long long sizeof_mem);

/**
 * @brief Allocates `size` bytes of uninitialized memory.
 *
 * This is a direct wrapper around the standard `malloc`.
 * In specific test configurations (by defining SML_ALLOC_FAILURE or SML_MALLOC_FAILURE),
 * this function can be made to simulate allocation failure for robust testing.
 *
 * @param size The number of bytes to allocate. Must be greater than 0.
 * @return A pointer to the newly allocated memory, or NULL if allocation fails or `size` is 0.
 * On failure, an error message is printed to stderr.
 *
 * @how_to
 * // Allocate 100 bytes directly
 * char *buffer = (char*)sml_malloc(100);
 * if (buffer == NULL) {
 * // Handle allocation error
 * fprintf(stderr, "Failed to allocate 100 bytes.\n");
 * }
 */
void *__attribute_malloc__ sml_malloc(unsigned long long size);

/**
 * @brief Allocates memory for `how_much` elements of `sizeof_mem` bytes each,
 * and initializes all allocated bytes to zero.
 *
 * This is a direct wrapper around the standard `calloc`.
 * In specific test configurations (by defining SML_ALLOC_FAILURE or SML_CALLOC_FAILURE),
 * this function can be made to simulate allocation failure for robust testing.
 *
 * @param how_much The number of elements to allocate. Must not cause an overflow.
 * @param sizeof_mem The size of each element in bytes. Must be greater than 0.
 * @return A pointer to the newly allocated and zero-initialized memory, or NULL if allocation fails or parameters are invalid.
 * On failure, an error message is printed to stderr.
 *
 * @how_to
 * // Allocate space for 5 floats and initialize to zero
 * float *my_floats = (float*)sml_calloc(5, sizeof(float));
 * if (my_floats == NULL) {
 * // Handle allocation error
 * }
 */
void *__attribute_malloc__ sml_calloc(unsigned long long how_much, unsigned long long sizeof_mem);

/**
 * @brief Attempts to resize the memory block pointed to by `ptr` to `new_requested_size` bytes.
 *
 * This function uses the standard `realloc` internally. It will try to resize the block
 * in place, or move it to a new location if necessary. It includes a basic retry mechanism.
 *
 * @param ptr A pointer to the memory block previously allocated by `sml_malloc`, `sml_calloc`, or `sml_alloc`.
 * If NULL, the call is equivalent to `sml_malloc(new_requested_size)`.
 * @param new_requested_size The new total size in bytes of the memory block.
 * If 0, the call is equivalent to `free(ptr)` and returns NULL.
 * @param retry The number of times to retry allocation on failure. A value of 0 means no retries.
 * @return A pointer to the reallocated memory block. This may be the same as `ptr` or a new address.
 * Returns NULL if the request cannot be satisfied after all retries, and the original block remains valid.
 * On failure, an error message is printed to stderr.
 *
 * @note This function might return the same pointer if the reallocation is in-place.
 * Forcing a new memory location requires `sml_realloc_change_place_bytes` or
 * `sml_realloc_change_place_elements`.
 *
 * @how_to
 * // Initial allocation
 * int *numbers = (int*)sml_alloc(5, sizeof(int));
 * // ... populate numbers ...
 *
 * // Resize to hold 10 integers (from 5*sizeof(int) to 10*sizeof(int) bytes)
 * // Try up to 2 retries if the first realloc fails.
 * int *new_numbers = (int*)sml_realloc(numbers, 10 * sizeof(int), 2);
 * if (new_numbers == NULL) {
 * // Reallocation failed, original 'numbers' pointer is still valid and not freed.
 * fprintf(stderr, "Failed to reallocate 'numbers' array.\n");
 * } else {
 * numbers = new_numbers; // Update pointer to new location (could be same or different)
 * }
 */
void *sml_realloc(void *ptr, unsigned long long new_requested_size, short unsigned retry);


/**
 * @brief Reallocates memory to a new location, explicitly copying a specified
 * number of bytes from the original block to the new one.
 *
 * This function guarantees that a *new* memory block will be allocated if successful,
 * explicitly moving the data. It is crucial to provide `old_size_in_bytes` to prevent
 * reading past the end of the original buffer if `new_size_in_bytes` is larger than `old_size_in_bytes`.
 *
 * @param ptr A pointer to the memory block previously allocated. If NULL, acts like `sml_malloc`.
 * @param old_size_in_bytes The actual allocated size (in bytes) of the memory block pointed to by `ptr`.
 * This is critical for safe copying.
 * @param new_size_in_bytes The desired total size (in bytes) for the new memory block.
 * If 0, acts like `free(ptr)` and returns NULL.
 * @return A pointer to the newly allocated and copied memory block. Returns NULL on failure.
 * If successful, the original `ptr` is freed. On failure, an error message is printed to stderr.
 *
 * @warning It is absolutely critical that `old_size_in_bytes` accurately reflects the
 * size of the memory block pointed to by `ptr`. Passing an incorrect
 * `old_size_in_bytes` can lead to **undefined behavior**, including crashes,
 * memory corruption, or security vulnerabilities. The caller is responsible for
 * tracking the original allocated size.
 *
 * @how_to
 * // Scenario 1: Reallocating a raw byte buffer
 * char *buffer = (char*)sml_malloc(50); // Original size is 50 bytes
 * // ... fill buffer with data ...
 *
 * // Resize to 100 bytes, forcing a new location.
 * char *new_buffer = (char*)sml_realloc_change_place_bytes(buffer, 50, 100);
 * if (new_buffer == NULL) {
 * // Handle error. 'buffer' is still valid and was NOT freed if new allocation failed.
 * fprintf(stderr, "Failed to reallocate buffer to 100 bytes.\n");
 * } else {
 * buffer = new_buffer; // 'buffer' now points to the new memory block. Old one was freed.
 * }
 *
 * // Scenario 2: Shrinking a buffer
 * int *data = (int*)sml_alloc(10, sizeof(int)); // 10 elements, so 10 * sizeof(int) bytes
 * // ... populate data ...
 *
 * // Shrink to 5 integers (5 * sizeof(int) bytes)
 * int *smaller_data = (int*)sml_realloc_change_place_bytes(data, 10 * sizeof(int), 5 * sizeof(int));
 * if (smaller_data == NULL) { <handle error> }
 * else { data = smaller_data; }
 */
void *sml_realloc_change_place_bytes(void *ptr, unsigned long long old_size_in_bytes, unsigned long long new_size_in_bytes);

/**
 * @brief Reallocates an array to a new memory location, copying existing elements.
 *
 * This function is designed for reallocating arrays where you know both the original
 * number of elements and the size of each element. It guarantees a new memory block
 * will be allocated if successful and performs a safe copy. New elements beyond the
 * original size are zero-initialized.
 *
 * @param ptr A pointer to the beginning of the array's memory block. If NULL, acts like `sml_calloc`.
 * @param old_num_elements The original number of elements in the array pointed to by `ptr`.
 * This is critical for safe copying.
 * @param element_size The size (in bytes) of a single element in the array. Must be greater than 0.
 * @param new_num_elements The desired new number of elements for the array.
 * If 0, acts like `free(ptr)` and returns NULL.
 * @return A pointer to the newly allocated and copied memory block (zero-initialized beyond old data).
 * Returns NULL on failure. If successful, the original `ptr` is freed. On failure, an error message is printed to stderr.
 *
 * @warning It is absolutely critical that `old_num_elements` and `element_size` accurately
 * reflect the characteristics of the original array pointed to by `ptr`. Incorrect
 * values can lead to **undefined behavior**, including crashes, memory corruption,
 * or security vulnerabilities. The caller is responsible for tracking these original values.
 *
 * @how_to
 * // Allocate an array of 5 ints
 * int *my_array = (int*)sml_calloc(5, sizeof(int)); // 5 elements, all zeroed
 * my_array[0] = 10; my_array[1] = 20;
 *
 * // Resize to 10 ints, forcing a new location. New elements will be zero-initialized.
 * int *larger_array = (int*)sml_realloc_change_place_elements(my_array, 5, sizeof(int), 10);
 * if (larger_array == NULL) {
 * // Handle error. 'my_array' is still valid.
 * fprintf(stderr, "Failed to reallocate 'my_array'.\n");
 * } else {
 * my_array = larger_array; // Update pointer. Old array was freed.
 * }
 *
 * // Shrink an array
 * float *float_array = (float*)sml_alloc(20, sizeof(float)); // 20 floats
 * // ... populate float_array ...
 *
 * // Shrink to 15 floats
 * float *smaller_float_array = (float*)sml_realloc_change_place_elements(float_array, 20, sizeof(float), 15);
 * if (smaller_float_array == NULL) { <handle error> }
 * else { float_array = smaller_float_array; }
 */
void *sml_realloc_change_place_elements(void *ptr, unsigned long long old_num_elements, unsigned long long element_size, unsigned long long new_num_elements);


#endif //SML_ALLOCATORS_H