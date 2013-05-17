#ifndef SHELLINITDEF_INCLUDED
#define SHELLINITDEF_INCLUDED

#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "GlobalVarDef.h"

#define MAX_HISTORY 100
#define HISTORY_FILE ".ccShell_history"

extern "C"
{
    extern void init_arg();
}

char * get_userhome();

char * get_history_file_path();

char * get_userinfo();

char * get_command();

void replace_username();

char * rm_space(char * str);

void last_dir_init();

void variable_init();

void history_init();

void history_finish();

void readline_init();

void environment_init();

#endif // SHELLINIT_INCLUDED
