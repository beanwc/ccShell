#ifndef COMMANDPARSEDEF_H_INCLUDED
#define COMMANDPARSEDEF_H_INCLUDED

#include "ExecuteCommandDef.h"

typedef int rl_icpfunc_t(char *);

struct _COMMAND
{
    const char * commandName;             // Command name
    rl_icpfunc_t * commandFunction;         // Function to call to do the command
    const char * commandDoc;              // Documentation for command
};

void readline_init();

char ** command_complete(const char * text, int start, int end);

char * command_produce(const char *text, int state);

void analyse_command(char * command_line);

void execute_command(char * command, char *arg[]);

#endif // COMMANDPARSEDEF_H_INCLUDED
