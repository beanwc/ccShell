#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ExecuteCommandDef.h"

using namespace std;

int cd_command(char * command, char *arg[])
{
    char * current_dir = (char *)malloc(1024);

    memset(current_dir, '\0', 1024);

    if(NULL == arg[0] || !strcmp(arg[0], "~"))
    {
        arg[0] = get_userhome();
    }
    if(!strcmp(arg[0], "-"))
    {
        strcpy(current_dir, last_dir);
        arg[0] = current_dir;
    }

    memset(last_dir, '\0', 1024);
    getcwd(last_dir,1024);

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
