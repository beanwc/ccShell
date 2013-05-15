#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

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

_COMMAND * get_execute_handle(char * command)
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

void analyse_command(char * command_line)
{
    char ** arg;

    arg = get_command_arg(command_line);

    analyse_pipe_command(arg[0], arg);
}

void analyse_pipe_command(char * command, char ** arg)
{
    int i = 0, j = 0;
	int prefd[2];
	int postfd[2];
	bool prepipe = false;
	char * strtmp;

	while(arg[i])
	{
		if(strcmp(arg[i], "|") == 0)
		{
			strtmp = arg[i];
			arg[i] = 0;

			pipe(postfd);

			if(prepipe)
            {
                execute_command((arg+j)[0], arg+j, prefd, postfd);
            }
			else
			{
            	execute_command((arg+j)[0], arg+j, 0, postfd);
			}
			arg[i] = strtmp;
			prepipe = true;
			prefd[0] = postfd[0];
			prefd[1] = postfd[1];
			j = ++i;
		}
		else
		{
            i++;
		}
	}
	if(prepipe)
	{
        execute_command((arg+j)[0], arg+j, prefd, 0);
	}
	else
    {
        execute_command((arg+j)[0], arg+j, 0, 0);
    }
}

int analyse_redirect_command(char * command, char ** arg, int * redirect_arg)
{
    int i;
	int redirect = 0;
	for(i = 1; NULL != arg[i]; i++)
	{
		if(strcmp(arg[i], "<") == 0)
		{
			redirect = 1;
			arg[i] = 0;
			break;
		}
        else if(strcmp(arg[i], ">") == 0)
		{
			redirect = 2;
			arg[i] = 0;
			break;
		}
	}
	if(redirect)
    {
		if(arg[i+1])
		{
			int fd;
			if(redirect == 2)
			{
				if((fd = open(arg[i+1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1)
				{
					cout<<"ccShell :Open out "<<arg[i+1]<<" failed"<<endl;
					return 1;
				}
				dup2(fd, STDOUT_FILENO);
			}
			else
			{
				if((fd = open(arg[i+1], O_RDONLY, S_IRUSR|S_IWUSR)) == -1)
				{
					cout<<"ccShell :Open in "<<arg[i+1]<<" failed"<<endl;
					return 1;
				}
				dup2(fd, STDIN_FILENO);
			}
		}
		else
		{
			cout<<"ccShell :Bad redirect, need more arg"<<endl;
			return 1;
		}
	}
	if(redirect)
	{
		*redirect_arg = redirect;
	}
	return 0;
}

int execute_command(char * command, char ** arg, int prefd[], int postfd[])
{
    char * command_file_path = NULL;
    int pid = 0;
    int status;
	_COMMAND * execute_result;

	command_file_path = (char *)malloc(1024);
    memset(command_file_path, '\0', 1024);

	if(arg == 0)
		return 0;

	if(prefd == 0 && postfd == 0)
	{
		if((execute_result = get_execute_handle(command)))
		{
			(*(execute_result->commandFunction))(command, arg);
			return 0;
		}
	}

	if((pid = fork()) == 0) {
		int redirect = 0;
		signal(SIGINT, SIG_DFL);

		if(analyse_redirect_command(command, arg, &redirect))
			exit(1);

		if(redirect != 1 && prefd)
		{
			close(prefd[1]);
			if(prefd[0] != STDIN_FILENO) {
				dup2(prefd[0], STDIN_FILENO);
				close(prefd[0]);
			}
		}
		if(redirect != 2 && postfd)
		{
			close(postfd[0]);
			if(postfd[1] != STDOUT_FILENO)
			{
				dup2(postfd[1], STDOUT_FILENO);
				close(postfd[1]);
			}
		}

		if((execute_result = get_execute_handle(command)))
		{
			(*(execute_result->commandFunction))(command, arg);
			return 0;
		}

		if(search_command_file_path(command, command_file_path))
        {
            execv(command_file_path, arg);
        }
		else
        {
			cout<<"ccShell: "<<command<<": Command not found!"<<endl;
            exit(0);
		}
	}
	waitpid(pid, &status, 0);
	if(postfd)
	{
		close(postfd[1]);
	}
	return 0;
}
