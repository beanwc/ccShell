#ifndef COMMANDPARSEDEF_H_INCLUDED
#define COMMANDPARSEDEF_H_INCLUDED

#include "ExecuteCommandDef.h"

typedef int rl_i_cp_cpp_func_t(int arg_count, char ** arg);

struct _COMMAND
{
    const char * commandName;             // Command name
    rl_i_cp_cpp_func_t * commandFunction;       // Function to call to do the command
    const char * commandDoc;              // Documentation for command
};

extern "C"
{
    extern char ** get_command_arg(char * command_line, int * arg_count);
    extern void reset_arg();
}

char ** command_complete(const char * text, int start, int end);

char * command_produce(const char *text, int state);

_COMMAND * get_execute_handle(char * command);

void analyse_command(char * command_line);

void analyse_pipe_command(int arg_count, char ** arg);

int analyse_redirect_command(int arg_count, char ** arg, int * redirect_arg);

int analyse_variable_command(int arg_count, char ** arg);

void replace_arg_variable(char * argument, char * buffer, int length);

int execute_command(int arg_count, char ** arg, int prefd[], int postfd[]);

#endif // COMMANDPARSEDEF_H_INCLUDED
