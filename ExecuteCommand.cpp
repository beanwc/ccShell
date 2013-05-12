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

bool pwd_command()
{
	char * path = new char[1024];

	memset(path, '\0', 1024);

	if(getcwd(path,1024) == NULL)
	{
        cout<<"Get path failed !"<<endl;
        return false;
	}
	else
	{
        cout<<path<<endl;
        return true;
	}
}

bool ls_command(char * command, char *arg[])
{
//    int i = 0;
    char * command_arg = new char[100];

    memset(command_arg, '\0', 100);

//    strcpy(sys_command, command);
//    while(arg[i])
//    {
//        strcat(command_arg, " ");
//        strcat(command_arg, arg[i]);
//        i++;
//    }
//    execve(command, "a", "l");
    delete command_arg;
    return true;
}
