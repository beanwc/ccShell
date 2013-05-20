#ifndef CODE_YACC_H_INCLUDED
#define CODE_YACC_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

double var_memory[100];

char * progname;
int lineno = 1;
jmp_buf begin;

int yylex ();
void yyerror (char * s);
void warning(char * s, char * t);
int fpecatch();
void execerror(char * s, char * t);

#endif //CODE_YACC_H_INCLUDED
