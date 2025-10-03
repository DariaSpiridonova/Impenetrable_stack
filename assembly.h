#ifndef ASSEMBLY
#define ASSEMBLY

#include <stdio.h>

#define SIZE 10
enum CommandsNums
{
    PUSH,
    ADD,
    DIV,
    MUL,
    SUB,
    SQRT,
    OUT,
    HLT,
    NON_EXISTING_COMMAND
};

struct commands_for_change
{
    char command[SIZE];
    CommandsNums num_of_command;
    int argument;
    size_t num_of_strings;
};

bool identify_the_command(struct commands_for_change *data_remember);
bool is_command(const char *received_command, const char *existing_command, bool *command_exist);

#endif