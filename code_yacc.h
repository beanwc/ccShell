#ifndef CODE_YACC_H_INCLUDED
#define CODE_YACC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

double var_memory[100];

char * progname;
int lineno = 1;
jmp_buf begin;
char code_arg[1024][20];
int code_arg_x;
int code_arg_y;

char ** replace_enter(char ** arg, int * arg_count);
char ** division_operator(char ** arg, int * arg_count);
//int yylex ();
void yyerror (char * s);
void warning(char * s, char * t);
int fpecatch();
void execerror(char * s, char * t);

#endif //CODE_YACC_H_INCLUDED
