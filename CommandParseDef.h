#ifndef COMMANDPARSEDEF_H_INCLUDED
#define COMMANDPARSEDEF_H_INCLUDED

#include "ExecuteCommandDef.h"

typedef int rl_i_cp_cpp_func_t(char * command, char ** arg);

struct _COMMAND
{
    const char * commandName;             // Command name
    rl_i_cp_cpp_func_t * commandFunction;       // Function to call to do the command
    const char * commandDoc;              // Documentation for command
};

extern "C"
{
    extern char ** get_command_arg(char * command_line);
}

char ** command_complete(const char * text, int start, int end);

char * command_produce(const char *text, int state);

_COMMAND * get_execute_handle(char * command);

void analyse_command(char * command_line);

void analyse_pipe_command(char * command, char ** arg);

int analyse_redirect_command(char * command, char ** arg, int * redirect_arg);

int execute_command(char * command, char ** arg, int prefd[], int postfd[]);

#endif // COMMANDPARSEDEF_H_INCLUDED
