#include <iostream>
#include <string.h>

#include "ExecuteCommandDef.h"
#include "CommandParseDef.h"

using namespace std;

void analyse_command(char *command_line)
{
    int i = 0, j = 0;
    bool command_flag = true;
    char * position = NULL;
    char * command = new char[100];
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
    else
    {
        system_execute(command, arg);
    }
}
