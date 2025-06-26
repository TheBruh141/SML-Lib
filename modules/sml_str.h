#ifndef SML_STR_H
#define SML_STR_H

#include "common_bindings.h"

typedef struct {
    char *contents;
    sml_size capacity;
    sml_size last_index;  // includes the null terminator index
} sml_str;

/**
 * @brief Allocates and initializes a new string container.
 *
 * @param contents Optional null-terminated input string. If NULL, initializes empty container.
 *
 * @return Pointer to a heap-allocated `sml_str` struct.
 *
 * @note Must be freed manually with `sml_str_free()`.
 */
sml_str *sml_str_new(const char *contents);

/**
 * @brief Frees memory used by an sml_str.
 *
 * @param str The `sml_str` to deallocate.
 */
void sml_str_free(sml_str *str);

/**
 * @brief Doubles the capacity of an existing `sml_str` using `realloc()`.
 *
 * @return `SML_STR_SUCCESS` or `SML_STR_FAIL` on allocation failure.
 */
_Bool sml_str_double_capacity(sml_str *str);

/**
 * @brief Same as `sml_str_double_capacity`, but uses `malloc` + `memcpy` instead.
 *
 * @note Slower, but may succeed when `realloc` fails.
 */
_Bool sml_str_double_capacity_force(sml_str *str);

/**
 * @brief Appends a null-terminated string to `str->contents`.
 *
 * @param str The destination `sml_str`
 * @param to_append Null-terminated string to add.
 *
 * @return Success or failure boolean.
 */
_Bool sml_str_append(sml_str *str, const char *to_append);

/**
 * @brief Creates a new heap string that is a substring of the input.
 *
 * @param str Original string (null-terminated)
 * @param start Start index (inclusive)
 * @param end End index (exclusive)
 *
 * @return Heap-allocated substring. Must be freed manually.
 */
char *sml_str_get_sub_str(const char *str, sml_size start, sml_size end);

/**
 * @brief Prints information about this module’s preprocessor defines.
 */
void sml_str_help(void);

#endif // SML_STR_H
