#ifndef EXECUTECOMMANDDEF_H_INCLUDED
#define EXECUTECOMMANDDEF_H_INCLUDED

void system_execute(char * command, char *arg[]);

int cd_command(char *arg);

int pwd_command(char *arg);

int history_command(char *arg);

int ls_command(char * command, char *arg[]);

#endif // EXECUTECOMMAND_H_INCLUDED
