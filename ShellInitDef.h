#ifndef SHELLINITDEF_INCLUDED
#define SHELLINITDEF_INCLUDED

#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_HISTORY 100
#define HISTORY_FILE ".ccShell_history"

char * get_userhome();

char * get_history_file_path();

char * get_userinfo();

char * get_command();

void replace_username();

char * rm_space(char * str);

void history_init();

void history_finish();

#endif // SHELLINIT_INCLUDED
