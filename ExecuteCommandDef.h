#ifndef EXECUTECOMMANDDEF_H_INCLUDED
#define EXECUTECOMMANDDEF_H_INCLUDED

void system_execute(char * command, char *arg[]);
bool cd_command(char *arg);
bool pwd_command();
bool ls_command(char * command, char *arg[]);

#endif // EXECUTECOMMAND_H_INCLUDED
