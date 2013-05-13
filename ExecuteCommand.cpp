#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ExecuteCommandDef.h"
#include "ShellInitDef.h"

using namespace std;

void system_execute(char * command, char *arg[])
{
    int i = 0;
    char * sys_command = (char *) malloc(2048);

    memset(sys_command, '\0', 2048);

    strcpy(sys_command, command);
    while(arg[i])
    {
        strcat(sys_command, " ");
        strcat(sys_command, arg[i]);
        i++;
    }
    system(sys_command);
    free(sys_command);
}


int cd_command(char * command, char *arg[])
{
    struct group * groupdata;
    char * username = NULL;
    char * userhome = NULL;

    groupdata = getgrgid(getgid());
    username = groupdata->gr_name;
    userhome = (char *)malloc(strlen(username)+6);

    memset(userhome, '\0', strlen(username)+6);

    if(NULL == arg[0] || !strcmp(arg[0], "~"))
    {
        if(0 == strcmp(username, "root"))
        {
            strcpy(userhome, "/");
        }
        else
        {
            strcpy(userhome, "/home/");
        }
        strcat(userhome, username);
        arg[0] = userhome;
    }
    if(chdir(arg[0]))
    {
        cout<<"ccShell: cd "<<arg[0]<<": No such file or directory!"<<endl;
        return -1;
    }

    return 0;
}

int pwd_command(char * command, char *arg[])
{
	char * path = (char *) malloc(1024);

	memset(path, '\0', 1024);

	if(getcwd(path,1024) == NULL)
	{
        cout<<"ccShell: pwd :Get path failed!"<<endl;
        return -1;
	}
	else
	{
        cout<<path<<endl;
        return 0;
	}
}

int history_command(char * command, char *arg[])
{
    int i = 0;
    HIST_ENTRY** historylist = NULL;

    historylist = history_list();
    if(NULL != historylist)
    {
        i = 0;
        while(historylist[i])
        {
            cout<<i<<": "<<historylist[i]->line<<endl;
            i++;
        }
    }
    return 0;
}

int ls_command(char * command, char *arg[])
{
//    int i = 0;
    char * command_arg = (char *) malloc(100);

    memset(command_arg, '\0', 100);

//    strcpy(sys_command, command);
//    while(arg[i])
//    {
//        strcat(command_arg, " ");
//        strcat(command_arg, arg[i]);
//        i++;
//    }
//    execve(command, "a", "l");
    free(command_arg);
    return 0;
}
