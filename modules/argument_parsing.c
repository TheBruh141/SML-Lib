// arg_parse.c
#include "argument_parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arg_parser_init(ArgParser* parser, int argc, char** argv, Arg* args, int num_args) {
    parser->argc = argc;
    parser->argv = argv;
    parser->args = args;
    parser->num_args = num_args;

    // Initialize values
    for (int i = 0; i < num_args; ++i) {
        args[i].value = NULL;
    }
}

void arg_parser_parse(ArgParser* parser) {
    for (int i = 1; i < parser->argc; ++i) {
        char* arg = parser->argv[i];

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                // Long option
                char* long_name = arg + 2;
                for (int j = 0; j < parser->num_args; ++j) {
                    if (strcmp(parser->args[j].long_name, long_name) == 0) {
                        if (parser->args[j].has_value) {
                            // Check for option value in the next argument
                            if (i + 1 < parser->argc) {
                                parser->args[j].value = parser->argv[++i];
                            } else {
                                fprintf(stderr, "Error: Value missing for option %s\n", long_name);
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            // Boolean option
                            parser->args[j].value = "true";
                        }
                        break;
                    }
                }
            } else {
                // Short option
                char short_name = arg[1];
                for (int j = 0; j < parser->num_args; ++j) {
                    if (parser->args[j].short_name == short_name) {
                        if (parser->args[j].has_value) {
                            // Check for option value in the same argument
                            if (arg[2] != '\0') {
                                parser->args[j].value = arg + 2;
                            } else if (i + 1 < parser->argc) {
                                parser->args[j].value = parser->argv[++i];
                            } else {
                                fprintf(stderr, "Error: Value missing for option %c\n", short_name);
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            // Boolean option
                            parser->args[j].value = "true";
                        }
                        break;
                    }
                }
            }
        }
    }
}

void arg_parser_print_help(ArgParser* parser, const char* program_name) {
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");

    for (int i = 0; i < parser->num_args; ++i) {
        if (parser->args[i].short_name != 0) {
            printf("  -%c, --%s", parser->args[i].short_name, parser->args[i].long_name);
        } else {
            printf("      --%s", parser->args[i].long_name);
        }

        if (parser->args[i].has_value) {
            printf(" <value>");
        }

        printf("\t%s\n", parser->args[i].help);
    }
}
