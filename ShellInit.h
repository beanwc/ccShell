#ifndef SHELLINIT_INCLUDED
#define SHELLINIT_INCLUDED

#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

void replace_username();
char * get_userinfo();
char * get_command();

#endif // SHELLINIT_INCLUDED
