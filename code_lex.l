%{
#include <stdio.h>
#include <stdlib.h>

int code_argnum = 100;
char *code_arg[100];
int code_argcount = 0;

void add_code_arg(char * code_arg);

%}

%x		QUOTE
%x		SINGQUOTE

SPECIAL	[()><|&;!*=]

%%

{SPECIAL} {
	  add_code_arg(yytext);
	}

\n	return (int)code_arg;

[ \t]+

.			    ;

%%

char **get_code_arg(char * shell_code, int * code_arg_count) {
	yy_scan_string(shell_code);
	yylex();
	*code_arg_count = code_argcount;
  	return code_arg;
}

void add_code_arg(char * code_argument)
{
    if(code_argcount < code_argnum)
    {
        code_arg[code_argcount] = (char*)malloc(strlen(code_argument)+1);
        strcpy(code_arg[code_argcount], code_argument);
        code_argcount++;
        code_arg[code_argcount] = 0;
    }
    else
    {
        printf("ccShell :Too many argument!\n");
    }
}
