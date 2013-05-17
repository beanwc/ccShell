%{
#include <stdio.h>
#include <stdlib.h>

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
	  add_value(yytext);
	}

\n	return (int)_arg;

[ \t]+

.			    ;

%%

char **get_command_arg(char * command_line) {
	yy_scan_string(command_line);
	yylex();
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

void add_value(char * arg)
{
    int arg_length = 0;
    int i = 0, j = 0, k = 0;
    char buffer[100], arg_tmp[100];

    arg_length = strlen(arg);

	for(i = 0; i < arg_length; i++)
	{
		if(arg[i] == '$')
		{
            if(arg[i+1] == 0)                      //arg == "$"
			{
				buffer[k] = '$';
				k++;
				break;
            }
			else if(arg[i+1] == '$')               //arg == "$$"
			{
				int pid = getpid();
				sprintf(buffer+k, "%d", pid);
				k = strlen(buffer);
				i++;
			}
			else
			{
				for(j = i+1; j < arg_length; j++)
				{
					if(arg[j] == '$')
						break;
					arg_tmp[j-i-1] = arg[j];
				}
				arg_tmp[j-i-1] = 0;
				i = j-1;
				if((arg = getenv(arg_tmp)))
                {
					strcpy(buffer+k, arg);
					k += strlen(arg);
				}
				else if((arg = get_variable_value(arg_tmp)))
				{
					strcpy(buffer+k, arg);
					k += strlen(arg);
				}
			}
		}
		else
		{
			buffer[k] = arg[i];
			k++;
		}
	}
	buffer[k] = 0;
	if(k > 0)
		add_arg(buffer);
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
		_arg[_argcount] = 0;
	}
}
