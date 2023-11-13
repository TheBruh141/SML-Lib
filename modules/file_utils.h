//
// Created by bruhpc on 10/18/23.
//

#ifndef SML_LIB_FILE_UTILS_H
#define SML_LIB_FILE_UTILS_H

#include <stdio.h>
#include "errors_and_logging.h"
#include "common_bindings.h"

static sml_error_config *sml_internal_errors_and_logging_config();

sml_size sml_get_file_size(FILE *f);

char *sml_file_read(FILE *f, sml_error_config *err_cfg);

FILE *sml_file_concat(FILE *f1, FILE *f2, char *concat_file_identifier, sml_error_config *error_config);

#endif //SML_LIB_FILE_UTILS_H
