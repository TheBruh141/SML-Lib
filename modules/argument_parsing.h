// arg_parse.h
#ifndef SML_LIB_ARG_PARSE_H
#define SML_LIB_ARG_PARSE_H

#include <stdbool.h>

// Structure to hold information about each argument
typedef struct {
    char short_name;
    const char *long_name;
    bool has_value;
    const char *help;
    const char *value;
} sml_arg_parser_args;

// Structure to hold the parsed arguments
typedef struct {
    int argc;
    char **argv;
    sml_arg_parser_args *args;
    int num_args;
} ArgParser;

// Initialize the argument parser with command line arguments and argument definitions
void sml_arg_parser_init(ArgParser *parser, int argc, char **argv, sml_arg_parser_args *args, int num_args);

// Parse the command line arguments
void sml_arg_parser_parse(ArgParser *parser);

// Print help information
void sml_arg_parser_print_help(ArgParser *parser, const char *program_name);

#endif // SML_LIB_ARG_PARSE_H
