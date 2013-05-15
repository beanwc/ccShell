#ifndef EXECUTECOMMANDDEF_H_INCLUDED
#define EXECUTECOMMANDDEF_H_INCLUDED

#include "ShellInitDef.h"


int cd_command(char * command, char ** arg);

int pwd_command(char * command, char ** arg);

int history_command(char * command, char ** arg);

bool search_command_file_path(const char * command_name, char * command_file_path);

#endif // EXECUTECOMMAND_H_INCLUDED
