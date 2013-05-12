#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "CommandParseDef.h"
#include "ShellInitDef.h"

using namespace std;

_COMMAND command_list[] = {
    {"cd", cd_command, "Change to Dir !"},
    {"pwd", pwd_command, "List files in current Dir !"},
    {"history", history_command, "List history command !"},
    {(char *) NULL, (rl_icpfunc_t *) NULL, (char *) NULL}
};

void analyse_command(char *command_line)
{
    int i = 0, j = 0;
    bool command_flag = true;
    char * position = NULL;
    char * command = (char *) malloc(100);
    char * arg[100];

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

    execute(command, arg);
}

void execute(char * command, char *arg[])
{
    if(!strcmp(command, "cd"))
    {
        cd_command(arg[0]);
    }
    else if(!strcmp(command, "pwd"))
    {
        pwd_command(arg[0]);
    }
    else if(!strcmp(command, "history"))
    {
        history_command(arg[0]);
    }
    else if(!strcmp(command, "ls"))
    {
        ls_command(command, arg);
    }
}


void readline_init()
{
    rl_readline_name = "ccShell";
    rl_attempted_completion_function = shell_completion;
}

char ** shell_completion(const char* text, int start, int end)
{
    char **matches;

    matches = (char **) NULL;
    if (0 == start)
    {
        matches = rl_completion_matches(text, command_generator);
    }

    return matches;
}

char * command_generator(const char *text, int state)
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
            return (dupstr(command_name));
        }
    }

    return NULL;
}

char * dupstr(char* s)
{
    char *r;

    r = (char*)malloc(strlen(s) + 1);
    strcpy(r, s);
    return (r);
}
