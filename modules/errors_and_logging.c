//
// Created by bruh on 10/6/23.
//

#include "errors_and_logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define DEBUG 1


char *sml_error_to_string(enum sml_error_codes err_code) {

    switch (err_code) {
        case (ERROR_OK) :
            return "ERROR_OK";
        case (ERROR_GENERIC) :
            return "ERROR_GENERIC";
        case (ERROR_INVALID_INPUT) :
            return "ERROR_INVALID_INPUT";
        case (ERROR_OUT_OF_MEMORY) :
            return "ERROR_OUT_OF_MEMORY";
        case (ERROR_IO_ERROR) :
            return "ERROR_IO_ERROR";
        case (ERROR_UNSUPPORTED) :
            return "ERROR_UNSUPPORTED";
        case (ERROR_OVERFLOW) :
            return "ERROR_OVERFLOW";
        case (ERROR_INVALID_STATE) :
            return "ERROR_INVALID_STATE";
        case (ERROR_FILE_NOT_FOUND) :
            return "ERROR_FILE_NOT_FOUND";
        case (ERROR_FILE_PERMISSION) :
            return "ERROR_FILE_PERMISSION";
        case (ERROR_FILE_READ) :
            return "ERROR_FILE_READ";
        case (ERROR_FILE_WRITE) :
            return "ERROR_FILE_WRITE";
        case (ERROR_NETWORK_DISCONNECTED) :
            return "ERROR_NETWORK_DISCONNECTED";
        case (ERROR_NETWORK_TIMEOUT) :
            return "ERROR_NETWORK_TIMEOUT";
        case (ERROR_NETWORK_INVALID_URL) :
            return "ERROR_NETWORK_INVALID_URL";
        case (ERROR_DATABASE_CONNECTION) :
            return "ERROR_DATABASE_CONNECTION";
        case (ERROR_DATABASE_QUERY) :
            return "ERROR_DATABASE_QUERY";
        case (ERROR_FEATURE_NOT_IMPLEMENTED) :
            return "ERROR_FEATURE_NOT_IMPLEMENTED";
        case (ERROR_FEATURE_NOT_SUPPORTED) :
            return "ERROR_FEATURE_NOT_SUPPORTED";
        case (ERROR_FEATURE_NOT_FOUND) :
            return "ERROR_FEATURE_NOT_FOUND";
        case (ERROR_MEMORY_ALLOCATION):
            return "ERROR_MEMORY_ALLOCATION";
        case (ERROR_MEMORY_REALLOCATION):
            return "ERROR_MEMORY_REALLOCATION";
        case (ERROR_MEMORY_DE_ALLOCATION):
            return "ERROR_MEMORY_DE_ALLOCATION";
        case (ERROR_MEMORY_OVERFLOW):
            return "ERROR_MEMORY_OVERFLOW";
        case (ERROR_MEMORY_UNDERFLOW):
            return "ERROR_MEMORY_UNDERFLOW";
        case (ERROR_MEMORY_CANNOT_ACCESS):
            return "ERROR_MEMORY_CANNOT_ACCESS";
        case (ERROR_MEMORY_INVALID):
            return "ERROR_MEMORY_INVALID";
        case (ERROR_MEMORY_CORRUPTION):
            return "ERROR_MEMORY_CORRUPTION";
        case (ERROR_MEMORY_INSUFFICIENT):
            return "ERROR_MEMORY_INSUFFICIENT";
        case (ERROR_MEMORY_NOT_ENOUGH):
            return "ERROR_MEMORY_NOT_ENOUGH";

        case (LAST_ENUM):
            return "LAST_ENUM... if you are using this.. please don't";

        default:
            return "UNKNOWN ERROR.. \nif you encounter this well...\n RIP";
    }

}

char *sml_log_severity_to_string(enum sml_log_severity severity) {
    switch (severity) {
        case LOG_SEVERITY_DEBUG:
            return "DEBUG";
        case LOG_SEVERITY_INFO:
            return "INFO";
        case LOG_SEVERITY_DEPRECATION:
            return "DEPRECATION";
        case LOG_SEVERITY_WARNING:
            return "WARNING";
        case LOG_SEVERITY_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void
sml_throw_error(sml_error_config *cfg, enum sml_error_codes err_code, enum sml_log_severity severity, char *msg, ...) {

    // expected output is
    /*
     * (in err_stream)
     * [PROGRAM_NAME] -> SEVERITY
     * [ERROR_NAME | CODE] :: [id = ID]
     *          -> "message"
     */

    static unsigned long long id = 1;
    FILE *err_stream = NULL;
    if (!cfg->has_log_file) {
        if (severity == LOG_SEVERITY_DEBUG || severity == LOG_SEVERITY_INFO) {
            err_stream = stdout;
        } else if (severity == LOG_SEVERITY_WARNING || severity == LOG_SEVERITY_ERROR ||
                   severity == LOG_SEVERITY_DEPRECATION) {
            err_stream = stderr;
        }
    } else {
        time_t t = time(NULL);
        char log_file_name[MAX_SML_NAME_LEN];  // Allocate space for the log file name
        snprintf(log_file_name, sizeof(log_file_name), "%s%s.log", cfg->log_file_location, ctime(&t));
        err_stream = fopen(log_file_name, "a");
    }
    // if something goes wrong ie. unrestriceted memory access. this allows the code to gracefully fail
    if (err_stream == NULL) {
        printf("something went wrong in the %s\n%s\n", __FILE__, __PRETTY_FUNCTION__);
        printf("setting err_stream to stdout as fallback\n");
        err_stream = stdout;
    }
    fprintf(err_stream, "\n[%s] -> %s :: %llu\n", cfg->name, sml_log_severity_to_string(severity), id++);
    fprintf(err_stream, "[%s | %d]:\n", sml_error_to_string(err_code), err_code);

    // printf wrapper
    va_list args;
    va_start(args, msg);
    vfprintf(err_stream, "\t-> \"", args);
    vfprintf(err_stream, msg, args);
    fprintf(err_stream, "\"\n");
    va_end(args);

    // do not forget to close the file :D
    if (cfg->has_log_file) {
        fclose(err_stream);
    }

    if (severity > LOG_SEVERITY_WARNING) {
        exit(severity);
    }
}

void sml_throw_error_non_blocking(sml_error_config *cfg, enum sml_error_codes err_code, enum sml_log_severity severity,
                                  char *msg,
                                  ...) {
// expected output is
/*
 * (in err_stream)
 * [PROGRAM_NAME] -> SEVERITY
 * [ERROR_NAME | CODE] :: [id = ID]
 *          -> "message"
 */

    static unsigned long long id = 1;
    FILE *err_stream = NULL;
    if (!cfg->has_log_file) {
        if (severity == LOG_SEVERITY_DEBUG || severity == LOG_SEVERITY_INFO) {
            err_stream = stdout;
        } else if (severity == LOG_SEVERITY_WARNING || severity == LOG_SEVERITY_ERROR ||
                   severity == LOG_SEVERITY_DEPRECATION) {
            err_stream = stderr;
        }
    } else {
        time_t t = time(NULL);
        char log_file_name[MAX_SML_NAME_LEN];  // Allocate space for the log file name
        snprintf(log_file_name,
                 sizeof(log_file_name), "%s%s.log", cfg->log_file_location, ctime(&t));
        err_stream = fopen(log_file_name, "a");
    }
// if something goes wrong ie. unrestriceted memory access. this allows the code to gracefully fail
    if (err_stream == NULL) {
        printf("something went wrong in the %s\n%s\n", __FILE__, __PRETTY_FUNCTION__);
        printf("setting err_stream to stdout as fallback\n");
        err_stream = stdout;
    }
    fprintf(err_stream,
            "\n[%s] -> %s :: %llu\n", cfg->name,
            sml_log_severity_to_string(severity), id
                    ++);
    fprintf(err_stream,
            "[%s | %d]:\n",
            sml_error_to_string(err_code), err_code
    );

// printf wrapper
    va_list args;
    va_start(args, msg);
    vfprintf(err_stream,
             "\t-> \"", args);
    vfprintf(err_stream, msg, args
    );
    fprintf(err_stream,
            "\"\n");
    va_end(args);

// do not forget to close the file :D
    if (cfg->has_log_file) {
        fclose(err_stream);
    }
}

sml_error_config init_sml_error(char *name, bool has_log_file, char *log_file_location) {
    sml_error_config result;

    // Ensure name is not too long
    strncpy(result.name, name, sizeof(result.name) - 1);
    result.name[sizeof(result.name) - 1] = '\0';

    result.has_log_file = has_log_file;
    result.log_file_location = log_file_location;
    result.has_set_log_file = (has_log_file && log_file_location == NULL) ? PREDIFINED_LOG_FILE_PATH : false;

    return result;
}

#if (DEBUG == 1)

void test_error_lib(void) {

    sml_error_config cfg = init_sml_error("test_error_lib", false, NULL);
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_DEBUG, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_INFO, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_WARNING, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_ERROR, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_DEPRECATION, "test_error_lib");

    printf("changing cfg to file based\n");
    cfg = init_sml_error("test_error_lib", true, "test_error_lib.log");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_DEBUG, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_INFO, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_WARNING, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_ERROR, "test_error_lib");
    sml_throw_error(&cfg, ERROR_GENERIC, LOG_SEVERITY_DEPRECATION, "test_error_lib");
    printf("done\n");

}

#else
void test_error_lib(void) {
    printf("TO USE THIS FUNCTINO YOU NEED TO ENABLE DEBUG MODE ON IN THE HEADER FILE %s\n", __FILE__);
}
#endif