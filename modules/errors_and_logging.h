//
// Created by bruh on 10/6/23.
//
// Since this is for error reporting.
// This file cannot use internal libraries or functions.
#ifndef SML_LIB_ERRORS_AND_LOGGING_H
#define SML_LIB_ERRORS_AND_LOGGING_H

#define MAX_SML_NAME_LEN 128
#define PREDIFINED_LOG_FILE_PATH "./logs/"

#ifndef CHECK

#include <stdlib.h>

#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "\n[SML_COMMON_BINDINGS]\n\t->Check failed: %s\nline=%d\n", __PRETTY_FUNCTION__, __LINE__); \
            exit(-1); \
        } \
    } while (0)
#endif

#include <stdbool.h>

enum sml_error_codes {
    // No error occurred
    ERROR_OK = 0,

    // General errors
    ERROR_GENERIC = 1,        // A generic error
    ERROR_INVALID_INPUT = 2,  // Invalid input data
    ERROR_OUT_OF_MEMORY = 3,  // Memory allocation failed (generic)
    ERROR_IO_ERROR = 4,       // IO error (probably user error)
    ERROR_UNSUPPORTED = 5,    // Feature not supported
    ERROR_OVERFLOW = 6,       // if an overflow is detected
    ERROR_INVALID_STATE = 7,  // if an invalid state is detected

    // File-related errors
    ERROR_FILE_NOT_FOUND = 10,     // File not found
    ERROR_FILE_PERMISSION = 11,    // Permission denied
    ERROR_FILE_READ = 12,         // Error reading from a file
    ERROR_FILE_WRITE = 13,        // Error writing to a file

    // Network-related errors
    ERROR_NETWORK_DISCONNECTED = 20,  // Network connection lost
    ERROR_NETWORK_TIMEOUT = 21,       // Network operation timed out
    ERROR_NETWORK_INVALID_URL = 22,   // Invalid URL

    // Database-related errors
    ERROR_DATABASE_CONNECTION = 30,  // Database connection failed
    ERROR_DATABASE_QUERY = 31,      // Error executing a database query

    // Memory related errors
    ERROR_MEMORY_ALLOCATION = 40,  // Memory allocation failed
    ERROR_MEMORY_REALLOCATION = 41, // Memory reallocation failed
    ERROR_MEMORY_DE_ALLOCATION = 42, // Memory deallocation failed
    ERROR_MEMORY_OVERFLOW = 43,     // Memory overflow detected
    ERROR_MEMORY_UNDERFLOW = 44,    // Memory underflow detected
    ERROR_MEMORY_CANNOT_ACCESS = 45,       // Memory access error
    ERROR_MEMORY_INVALID = 46,      // Invalid memory access
    ERROR_MEMORY_CORRUPTION = 47,   // Memory corruption detected
    ERROR_MEMORY_INSUFFICIENT = 48, // Insufficient memory
    ERROR_MEMORY_NOT_ENOUGH = 49,   // Not enough memory

    // feature related errors
    ERROR_FEATURE_NOT_IMPLEMENTED = 51, // if a feature is not implemented
    ERROR_FEATURE_NOT_SUPPORTED = 52,  // if a feature is not supported
    ERROR_FEATURE_NOT_FOUND = 53,     // if a feature is not found

    LAST_ENUM // DO NOT USE THIS ENUM THIS IS A PLACEHOLDER FOR INTERNAL FUNCTIONS.
};

enum sml_log_severity {
    LOG_SEVERITY_DEBUG = 0,
    LOG_SEVERITY_INFO,
    LOG_SEVERITY_DEPRECATION,
    LOG_SEVERITY_WARNING,
    LOG_SEVERITY_ERROR,
};

typedef struct {
    bool has_log_file;
    bool has_set_log_file;
    // this is the __place__ where the log file will be
    // not the name if the file
    const char *log_file_location;
    const char *name;
} sml_error_config;

sml_error_config *
sml_errors_and_logging_init(const char *name, bool has_log_file, const char *log_file_location);

char *sml_log_severity_to_string(enum sml_log_severity severity);

char *sml_error_to_string(enum sml_error_codes err_code);



// general functions for throwing or generating errors or log messages
// this is also a custom wrapper around printf. you can use the message as how you would do it in a printf.

void
sml_throw_error(sml_error_config *cfg, enum sml_error_codes err_code, enum sml_log_severity severity, char *msg,
                ...);

// exactly the same as sml_throw_error, but it does not exit when encountering an error
void sml_throw_error_non_blocking(sml_error_config *cfg, enum sml_error_codes err_code, enum sml_log_severity severity,
                                  char *msg,
                                  ...);

void test_error_lib(void);

#endif //SML_LIB_ERRORS_AND_LOGGING_H