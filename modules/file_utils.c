//
// Created by bruhpc on 10/18/23.
//

#include "file_utils.h"
#include "errors_and_logging.h"
#include "common_bindings.h"

sml_error_config *sml_internal_errors_and_logging_config() {
    sml_error_config *cfg = sml_errors_and_logging_init("SML_LIB_ERRORS_AND_LOGGING", false, NULL);
    return cfg;
}

sml_size sml_get_file_size(FILE *f) {
    if (f == stderr || f == stdout)
        sml_throw_error(sml_internal_errors_and_logging_config(), ERROR_FILE_READ, LOG_SEVERITY_ERROR,
                        "Idk if we can do this boss...\n Don't try to use this on Stdin or Stdout.");

    if (fseek(f, 0, SEEK_END) < 0) {
        fclose(f);
        return -1;
    }

    long size = ftell(f);
    // release the resources when not required
    return size;
}

// reads a file.
// NOTE: this function does not open or close the FILE*
// if you don't want to use the config, just put NULL;
char *sml_file_read(FILE *f, sml_error_config *err_cfg) {
    sml_error_config *err_config;
    if (err_cfg == NULL) {
        err_config = sml_internal_errors_and_logging_config();
    } else {
        err_config = err_cfg;
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = calloc(size + 1, sizeof(char));
    if (buffer == NULL) {
        sml_throw_error(err_config, ERROR_MEMORY_ALLOCATION, LOG_SEVERITY_ERROR, "Calloc failed in %s\nline : ",
                        __PRETTY_FUNCTION__, __LINE__);
        return NULL;
    }

    fread(buffer, sizeof(char), size, f);
    buffer[size] = '\0';

    return buffer;
}

// concatenates 2 files.
// NOTE: concat_file_identifier is the path of the object. i.e.: "Hello_world.txt", "../../"settings.toml"
// NOTE: if there is no error config, you can just put NULL and the library will handle it for your :D
FILE *sml_file_concat(FILE *f1, FILE *f2, char *concat_file_identifier, sml_error_config *error_config) {
    sml_size s1 = sml_get_file_size(f1);
    sml_size s2 = sml_get_file_size(f2);
    sml_size s_final = s1 + s2;
    char *contents = malloc(sizeof(char) * s_final);
    if (NULL == error_config) {
        error_config = sml_internal_errors_and_logging_config();
    }
    char *c1 = sml_file_read(f1, error_config);
    char *c2 = sml_file_read(f2, error_config);

    sml_size i = -1;
    while (s1 - i++) {
        contents[i] = c1[i];
    }
    contents[s1] = ' ';

    i = -1;
    while (s2 - i++) {
        contents[s1 - 1 + i] = c2[i];
    }

    printf("%s", contents);
    FILE *concat_file = fopen(concat_file_identifier, "w");
    fwrite(contents, sizeof(char), s_final, concat_file);
    rewind(concat_file);
    return concat_file;
}

