#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "assembly.h"

int main()
{
    FILE *commands_for_reading = fopen("original_commands.asm", "r");
    FILE *commands_for_record = fopen("byte_code.txt", "w");

    struct commands_for_change data_remember = 
    {
        .command = {0},
        .num_of_command = PUSH,
        .argument = 0,
        .num_of_strings = 1
    };

    while (!feof(commands_for_reading))
    {
        if (fscanf(commands_for_reading, "%s", data_remember.command) != 1)
        {
            printf("\033[31min commands.asm: line %zd: The command is not set.\033[0m\n", data_remember.num_of_strings);
            return 1;
        }

        else if (!identify_the_command(&data_remember))
        {
            printf("\033[31min commands.asm: line %zd: The command %s does not exist.\033[0m\n", data_remember.num_of_strings, data_remember.command);
            return 2;
        }

        fprintf(commands_for_record, "%d ", data_remember.num_of_command);

        if (data_remember.num_of_command == PUSH)
        {
            if (fscanf(commands_for_reading, "%d", &data_remember.argument) != 1)
            {
                printf("\033[31min commands.asm: line %zd: The PUSH command argument is missing.\033[0m\n", data_remember.num_of_strings);
                return 3;
            }
            fprintf(commands_for_record, "%d", data_remember.argument);
        }
        fprintf(commands_for_record, "\n");
        data_remember.num_of_strings++;
    }

    return 0;
}

bool identify_the_command(struct commands_for_change *data_remember)
{
    bool command_exist = false;

    if      (is_command(data_remember->command, "PUSH", &command_exist)) data_remember->num_of_command = PUSH;
    else if (is_command(data_remember->command, "ADD", &command_exist)) data_remember->num_of_command = ADD;
    else if (is_command(data_remember->command, "SUB", &command_exist)) data_remember->num_of_command = SUB;
    else if (is_command(data_remember->command, "MUL", &command_exist)) data_remember->num_of_command = MUL;
    else if (is_command(data_remember->command, "DIV", &command_exist)) data_remember->num_of_command = DIV;
    else if (is_command(data_remember->command, "SQRT", &command_exist)) data_remember->num_of_command = SQRT;
    else if (is_command(data_remember->command, "OUT", &command_exist)) data_remember->num_of_command = OUT;
    else if (is_command(data_remember->command, "HLT", &command_exist)) data_remember->num_of_command = HLT; 

    return command_exist;
}

bool is_command(const char *received_command, const char *existing_command, bool *command_exist)
{
    assert(received_command != NULL && existing_command != NULL);

    if (!strcmp(received_command, existing_command))
    {
        *command_exist = true;
        return true;
    }

    return false;
}