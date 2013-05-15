%{
int _numargs = 100;
char *_args[100];
int _argcount = 0;
%}

WORD    [a-zA-Z0-9\/\.\-\_]+
SPECIAL	[()><|&;!*]
WORD2   \"([ ,a-zA-Z0-9\/\.\-\_]+,)*[ a-zA-Z0-9\/\.\-\_]+\"

%%
	_argcount = 0;
	_args[0] = NULL;

{WORD2}|{WORD}|{SPECIAL} {
	  if(_argcount < _numargs-1) {
	    _args[_argcount++] = (char *)strdup(yytext);
	    _args[_argcount] = NULL;
	  }
	}

\n	return (int)_args;

[ \t]+

.

%%

char **get_command_arg(char * command_line) {
	yy_scan_string(command_line);
	yylex();
  	return _args;
}
