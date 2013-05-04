#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ExecuteCommandDef.h"

using namespace std;

void system_execute(char * command, char *arg[])
{
    int i = 0;
    char * sys_command = new char[2048];

    memset(sys_command, '\0', 2048);

    strcpy(sys_command, command);
    while(arg[i])
    {
        strcat(sys_command, " ");
        strcat(sys_command, arg[i]);
        i++;
    }
    system(sys_command);
    delete sys_command;
}


bool cd_command(char *arg)
{
    if( chdir(arg))
    {
        cout<<"ccShell: cd "<<arg<<": No such file or directory !"<<endl;
        return false;
    }
    return true;
}
