/*
    http://ryan1987.blogbus.com/logs/65118686.html
    http://hi.baidu.com/seraphsky/item/4cf6d51ec2cd2148e75e069a
*/
%{
    #include "code_yacc.h"
%}

%union
    {
        double val;
        int index;
    }

%token  <val>    NUMBER
%token  <index>  VAR
%type   <val>    expr

%right  '='
%left   '+' '-'
%left   '*' '/'
%left   UNARYMINUS

%%

list:
    | list  '\n'
    | list  expr    '\n'    {printf("\t%.8g\n", $2);}
    | list  error   '\n'    {yyerrok;}
    ;

expr:   VAR
    |VAR '=' expr

expr:   NUMBER
    |VAR            {$$ = var_memory[$1];}
    |VAR '=' expr   {$$ = var_memory[$1] = $3;}
    |expr '+' expr  {$$ = $1 + $3;}
    |expr '-' expr  {$$ = $1 - $3;}
    |expr '*' expr  {$$ = $1 * $3;}
    |expr '/' expr
            {
                if(0.0 == $3)
                {
                    execerror("Division by zero!", "");
                }
                $$ = $1 / $3;
            }
    |'('expr')'     {$$ = $2;}
    |'-' expr %prec UNARYMINUS  {$$ = -$2;}
    ;

%%

int yylex()
{
    int c;

    while(' ' == (c = getchar()) || '\t' == c)
    {
        ;
    }

    if(EOF == c)
    {
        return 0;
    }
    if('.' == c || isdigit(c))
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }
    if(islower(c))
    {
        yylval.index = c -'a';
        return VAR;
    }
    if('\n' == c)
    {
        lineno++;
    }
    return c;
}

void warning(char * s, char * t)
{
    fprintf(stderr, "%s: %s", progname, s);
    if(t)
    {
        fprintf(stderr, " %s",t);
    }
    fprintf(stderr, " near line %d\n", lineno);
}

void yyerror(char * s)
{
    warning(s, (char *)0);
}

int fpecatch()
{
    execerror("Floating point exception", (char *)0);
}

void execerror(char * s, char * t)
{
    warning(s, (char *)0);
    longjmp(begin, 0);
}

void main(int agc, char * argv[])
{
    progname = argv[0];

    math_init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    yyparse();
}
