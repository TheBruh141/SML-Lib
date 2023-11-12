// main.c
#include "argument_parsing.h"
#include <stdio.h>

#define DEBUG

int main(int argc, char** argv) {
    // Define your command line arguments
    Arg args[] = {
            {'a', "alpha", true, "Alpha parameter"},
            {'b', "beta", false, "Beta parameter"},
            {'c', "config", true, "Config file path"},
    };

    // Initialize the argument parser
    ArgParser parser;
    arg_parser_init(&parser, argc, argv, args, sizeof(args) / sizeof(args[0]));

    // Parse the command line arguments
    arg_parser_parse(&parser);

    // Access the parsed arguments
    for (int i = 0; i < parser.num_args; ++i) {
        printf("Argument: %s, Value: %s\n", parser.args[i].long_name, parser.args[i].value);
    }

    // Print help if needed
    if (argc < 2 || (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))) {
        arg_parser_print_help(&parser, argv[0]);
    }

    return 0;
}
