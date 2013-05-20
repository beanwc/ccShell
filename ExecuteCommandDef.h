#ifndef EXECUTECOMMANDDEF_H_INCLUDED
#define EXECUTECOMMANDDEF_H_INCLUDED

#include "ShellInitDef.h"
#include "CommandParseDef.h"


int cd_command(int arg_count, char ** arg);

int ccShell_command(int arg_count, char ** arg);

int pwd_command(int arg_count, char ** arg);

int echo_command(int arg_count, char ** arg);

int help_command(int arg_count, char ** arg);

int unset_command(int arg_count, char ** arg);

int history_command(int arg_count, char ** arg);

bool assignment(char ** arg);

extern "C"
{
    char * get_variable_value(char * variable_name);
}

bool search_command_file_path(const char * command_name, char * command_file_path);

#endif // EXECUTECOMMAND_H_INCLUDED
