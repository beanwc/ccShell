#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "CommandParseDef.h"

using namespace std;

_COMMAND command_list[] = {
    {"cd", cd_command, "Change to Dir !"},
    {"pwd", pwd_command, "List files in current Dir !"},
    {"history", history_command, "List history command !"},
    {(char *) NULL, (rl_i_cp_cpp_func_t *) NULL, (char *) NULL}
};


void readline_init()
{
    rl_readline_name = "ccShell";
    rl_attempted_completion_function = command_complete;
}

char ** command_complete(const char * text, int start, int end)
{
    char ** matches;

    matches = (char **) NULL;
    if (0 == start)
    {
        matches = rl_completion_matches(text, command_produce);
    }

    return matches;
}

char * command_produce(const char * text, int state)
{
    static int list_index, len;
    char * command_name = (char *) malloc(100);

    memset(command_name, '\0', 100);

    if (!state)
    {
        list_index = 0;
        len = strlen(text);
    }

    while (NULL != command_list[list_index].commandName)
    {
        strcpy(command_name, command_list[list_index].commandName);
        list_index++;
        if (strncmp(command_name, text, len) == 0)
        {
            return command_name;
        }
    }

    return NULL;
}

void analyse_command(char * command_line)
{
    int i = 0, j = 0;
    bool command_flag = true;
    char * position = NULL;
    char * command = (char *) malloc(100);
    char * arg[100];
    _COMMAND * execute_result;

    memset(command, '\0', 100);

    for (; j < 100; j++)
    {
        arg[j] = NULL;
    }

    while( (position = strsep(&command_line," ")) != NULL)
    {
        if(command_flag)
        {
            strcpy(command, position);
            command_flag = false;
        }
        else
        {
            arg[i++] = position;
        }
    }

    execute_result = get_execute_handle(command, arg);

    if (NULL == execute_result)
    {
        cout<<"ccShell: "<<command<<": Command not found!"<<endl;
    }
    else
    {
        (*(execute_result->commandFunction))(command, arg);
    }
}

_COMMAND * get_execute_handle(char * command, char *arg[])
{
    int i;

    for (i = 0; command_list[i].commandName; i++)
	{
		if (strcmp(command, command_list[i].commandName) == 0)
			{
                return (&command_list[i]);
			}
    }

    return NULL;
}
