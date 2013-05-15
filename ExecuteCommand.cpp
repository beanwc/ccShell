#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#include "ExecuteCommandDef.h"

using namespace std;

int cd_command(char * command, char ** arg)
{
    char * current_dir = (char *)malloc(1024);

    memset(current_dir, '\0', 1024);

    if(NULL == arg[1] || !strcmp(arg[1], "~"))
    {
        arg[1] = get_userhome();
    }
    if(!strcmp(arg[1], "-"))
    {
        strcpy(current_dir, last_dir);
        arg[1] = current_dir;
    }

    memset(last_dir, '\0', 1024);
    getcwd(last_dir,1024);

    if(chdir(arg[1]))
    {
        cout<<"ccShell: cd "<<arg[0]<<": No such file or directory!"<<endl;
        return -1;
    }

    return 0;
}

int pwd_command(char * command, char ** arg)
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

int history_command(char * command, char ** arg)
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

bool search_command_file_path(const char * command_name, char * command_file_path)
{
	int i = 0;
	const char* position = NULL;

	position = getenv("PATH");
	while(*position != 0)
	{
		if(*position != ':')
		{
			command_file_path[i++] = *position;
		}
		else
		{
			command_file_path[i++] = '/';
			command_file_path[i] = '\0';
			strcat(command_file_path, command_name);
			if(access(command_file_path, F_OK) == 0)
			{
				return true;
			}
			i = 0;
		}
		position++;
	}
	return false;
}
