#ifndef SHELLINITDEF_INCLUDED
#define SHELLINITDEF_INCLUDED

#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_HISTORY 100
#define HISTORY_FILE "/tmp/ccShell_history"

void replace_username();

char * get_userinfo();

char * get_command();

void history_init();

void history_finish();

#endif // SHELLINIT_INCLUDED
