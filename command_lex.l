%{
#include <stdio.h>
#include <stdlib.h>

#define YY_DECL int yy_command_lex(void)

int _argnum = 100;
char *_arg[100];
int _argcount = 0;

void add_arg(char * arg);
void add_value(char * arg);
void init_arg();
void reset_arg();

extern char * get_variable_value(char * variable_name);
%}

%x		QUOTE
%x		SINGQUOTE

WORD    [a-zA-Z0-9\/\.\-\_]+
SPECIAL	[()><|&;!*=]
VALUE   [^ \t\n|<>;"&=]+

%%

{WORD}|{SPECIAL}|{VALUE} {
	  add_arg(yytext);
	}

\n	return (int)_arg;

[ \t]+

.			    ;

%%

char **get_command_arg(char * command_line, int * arg_count) {
	yy_scan_string(command_line);
	yy_command_lex();
	*arg_count = _argcount;
  	return _arg;
}

void add_arg(char * arg)
{
    if(_argcount < _argnum)
    {
        _arg[_argcount] = (char*)malloc(strlen(arg)+1);
        strcpy(_arg[_argcount], arg);
        _argcount++;
        _arg[_argcount] = 0;
    }
    else
    {
        printf("ccShell :Too many argument!\n");
    }
}

void init_arg()
{
    int i = 0 ;
    _argcount = 0;
    for(; i < _argnum; i++)
    {
        _arg[i] = NULL;
    }
}

void reset_arg()
{
	for(; _argcount > 0; _argcount--) {
		free(_arg[_argcount]);
		_arg[_argcount] = NULL;
	}
	_argcount = 0;
}
