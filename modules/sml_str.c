
#include "sml_str.h"
#include "allocators.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

sml_str *sml_str_new(const char *contents) {
    sml_str *new = calloc(1, sizeof(sml_str));
    if (!new) return NULL;

    if (!contents) return new;

    sml_size len = strlen(contents);
    new->capacity = len + 1;
    new->last_index = len;

    new->contents = malloc(new->capacity);
    if (!new->contents) {
        free(new);
        return NULL;
    }

    memcpy(new->contents, contents, len);
    new->contents[len] = '\0';
    return new;
}

void sml_str_free(sml_str *str) {
    if (!str) return;
    free(str->contents);
    free(str);
}

_Bool sml_str_double_capacity(sml_str *str) {
    sml_size new_cap = str->capacity * 2;
    char *temp = realloc(str->contents, new_cap);
    if (!temp) {
        str->capacity /= 2;
        return Sml_Fail;
    }
    str->contents = temp;
    str->capacity = new_cap;
    return Sml_Success;
}

_Bool sml_str_double_capacity_force(sml_str *str) {
    sml_size new_cap = str->capacity * 2;
    char *temp = malloc(new_cap);
    if (!temp) return Sml_Fail;

    memcpy(temp, str->contents, str->capacity);
    free(str->contents);
    str->contents = temp;
    str->capacity = new_cap;
    return Sml_Success;
}

_Bool sml_str_append(sml_str *str, const char *to_append) {
    if (!str || !to_append) return Sml_Fail;

    sml_size len = strlen(to_append);
    while (str->capacity <= str->last_index + len) {
        if (Sml_Fail == sml_str_double_capacity(str)) {
            if (Sml_Fail == sml_str_double_capacity_force(str)) {
                return Sml_Fail;
            }
        }
    }

    memcpy(str->contents + str->last_index, to_append, len);
    str->last_index += len;
    str->contents[str->last_index] = '\0';
    return Sml_Success;
}

char *sml_str_get_sub_str(const char *str, sml_size start, sml_size end) {
    if (!str || end <= start) return NULL;

    sml_size len = end - start;
    char *sub = malloc(len + 1);
    if (!sub) return NULL;

    memcpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}

void sml_str_help(void) {
    puts("[SML_STR] Defines available:");
    puts("\t- SML_STR_MAKE_GENERIC: typedefs `sml_str` as `str`.");
}
