%{
    #include <stdlib.h>
    #include "code_yacc.tab.c"

    extern union yylval;

    void yyerror(char *);
    void add_code_arg(char *);

%}

%%

[0-9]*\.[0-9]+      { yylval.value = atoi(yytext); add_code_arg(yytext); return NUMBER;  }
[a-z]+              { yylval.identifier = *yytext - 'a'; add_code_arg(yytext);  return VAR; }
[\+\-\*\/\%]        { yylval.identifier = *yytext; add_code_arg(yytext); return *yytext; }
[\n]                { code_arg_x++;code_arg_y = 0; return *yytext; }
[\t]                ;
.                   yyerror("Invalid identifier!");

%%

void add_code_arg(char * arg)
{
    code_arg[code_arg_x][code_arg_y] = *arg;
    code_arg_y++;
}

void get_code_arg(char * code_buffer)
{
    yy_scan_string(code_buffer);
	yylex();
}
