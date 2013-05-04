#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ExecuteCommandDef.h"

using namespace std;

bool pwd_command()
{
    char * path = new char[1024];

    memset(path, '\0', 1024);

    if( getcwd(path,1024) == NULL)
    {
        cout<<"ccShell: pwd: Get path filed !"<<endl;
        return false;
    }
    cout<<path<<endl;
    delete [] path;
    return true;
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

void ls_command(char *arg[])
{
    int i = 0;
    char * sys_command = new char[1024];

    memset(sys_command, '\0', 1024);

    strcpy(sys_command, "ls");
    while(arg[i])
    {
        strcat(sys_command, " ");
        strcat(sys_command, arg[i]);
        i++;
    }
    system(sys_command);
    delete sys_command;
}
