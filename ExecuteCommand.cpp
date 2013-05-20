#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#include "ExecuteCommandDef.h"

using namespace std;

extern _COMMAND command_list[];

int cd_command(int arg_count, char ** arg)
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
        cout<<"ccShell :cd "<<arg[0]<<":No such file or directory!"<<endl;
        return -1;
    }

    return 0;
}

int ccShell_command(int arg_count, char ** arg)
{
    int i = 0, j = 0, open_file_result = 0, read_file_result = 0;
    char * file_buffer = NULL;
    int code_arg_count;
    char ** code_arg;

//    cout<<"arg_count :"<<arg_count<<endl;
//    for(i = 0; i < arg_count; i++)
//    {
//        cout<<"arg["<<i<<"] :"<<arg[i]<<endl;
//    }
    for(i = 1; i < arg_count; i++)
    {
        open_file_result = open(arg[i], O_RDONLY);
        if(open_file_result != -1)
        {
            file_buffer = (char *)malloc(1024);
            memset(file_buffer, '\0', 1024);
            read_file_result = read(open_file_result, file_buffer, 1024);
            if(-1 == read_file_result)
            {
                cout<<"ccShell :File read failed--"<<arg[i]<<"!"<<endl;
            }
            else if(0 == read_file_result)
            {
                cout<<"ccShell :File is empty--"<<arg[i]<<"!"<<endl;
            }
            else
            {
//                code_arg = get_code_arg(file_buffer, &code_arg_count);
//                for(j = 0; j < code_arg_count; j++)
//                {
//                    cout<<"code_arg["<<j<<"] :"<<code_arg[j]<<endl;
//                }
                cout<<file_buffer<<endl;
            }
            if(-1 == close(open_file_result))
            {
                cout<<"ccShell :File close failed--"<<arg[i]<<"!"<<endl;
            }
        }
        else
        {
            cout<<"ccShell :File open failed--"<<arg[i]<<"!"<<endl;
        }
    }
    return 0;
}

int pwd_command(int arg_count, char ** arg)
{
	char * path = (char *) malloc(1024);

	memset(path, '\0', 1024);

	if(getcwd(path,1024) == NULL)
	{
        cout<<"ccShell :pwd :Get path failed!"<<endl;
        return -1;
	}
	else
	{
        cout<<path<<endl;
        return 0;
	}
}

int echo_command(int arg_count, char ** arg)
{
    int i = 1;
    while(arg[i])
    {
        cout<<arg[i];
        i++;
    }
    cout<<endl;
    return 0;
}

int unset_command(int arg_count, char ** arg)
{
    int i = 0;
    char * variable_tmp;

    variable_tmp = (char *)malloc(sizeof(arg[1]));
    memset(variable_tmp, '\0', sizeof(arg[1]));

    if(arg[1][0] !='$' && !arg[1][1])
    {
        cout<<"ccShell :unset :Invalid variable name!"<<endl;
        return -1;
    }
    else
    {
        for(i = 1; arg[1][i] != 0; i++)
        {
            variable_tmp[i-1] = arg[1][i];
        }

        for(i = 0; i < variable_count; i++)
        {
            if(0 == strcmp(variable[i].variable_name, variable_tmp))
            {
                free(variable[i].variable_name);
                free(variable[i].variable_value);
                variable[i].variable_name = NULL;
                variable[i].variable_value = NULL;
                variable_count--;
                return 0;
            }
        }
    }
    return 0;
}

int help_command(int arg_count, char ** arg)
{
    int i = 0;
    cout<<"----------------------The Builtin Command Help Information----------------------"<<endl;
    cout<<"   Command                             Document    "<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    while(command_list[i].commandName)
    {
        cout<<"     "<<command_list[i].commandName<<"                    "<<command_list[i].commandDoc<<"     "<<endl;
        i++;
    }
    return 0;
}

int history_command(int arg_count, char ** arg)
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

bool assignment(char ** arg)
{
    int i = 0, j = 0;

    while(arg[i])
    {
        if((0 == strcmp(arg[i], "=")) && arg[i-1] && arg[i+1])
        {
            for(j = 0; j < variable_count; j++)
            {
                if(0 == strcmp(variable[j].variable_name, arg[i-1]))
                {
                    delete variable[j].variable_value;
                    variable[j].variable_value = (char *)malloc(sizeof(arg[i+1]));
                    strcpy(variable[j].variable_value, arg[i+1]);
                    return 1;
                }

            }
            if(variable_count < MAX_VAR_NUM)
            {
                variable[variable_count].variable_name = (char *)malloc(sizeof(arg[i-1]));
                variable[variable_count].variable_value = (char *)malloc(sizeof(arg[i+1]));
                strcpy(variable[variable_count].variable_name, arg[i-1]);
                strcpy(variable[variable_count].variable_value, arg[i+1]);
                variable_count++;
            }
            else
            {
                cout<<"ccShell :Too many variable,please reset some variable with unset command!"<<endl;
            }
            return 1;
        }
        i++;
    }
    return 0;
}

char * get_variable_value(char * variable_name)
{
    int i = 0;

    for(i = 0; i < variable_count; i++)
    {
        if(0 == strcmp(variable[i].variable_name, variable_name))
        {
            return variable[i].variable_value;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
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
