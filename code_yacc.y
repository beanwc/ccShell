%{
    #include "code_yacc.h"
%}

%union
    {
        double value;
        int identifier;
    }

%token  <value>             NUMBER
%token  <identifier>        VAR
%type   <value>             expr

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
/*
int yylex()
{
    int i = 0, j = 0, arg_count = 0;
    char ** result_arg = NULL;
//    char ** code_tmp = NULL;
    char ** code_arg = NULL;

    result_arg = get_code_arg(&arg_count);
    code_arg = replace_enter(result_arg, &arg_count);
//    code_arg = division_operator(code_tmp, &arg_count);

//    for(; i < arg_count; i++)
//    {
//        printf("%s%d%s%s\n", "code_arg[", i, "] = ", code_arg[i]);
//    }

    i = 0;
    while(i < arg_count)
    {
        if(EOF == code_arg[i][0])
        {
            return 0;
        }
        if('.' == code_arg[i][0] || isdigit(code_arg[i][0]))
        {
            yylval.val = atof(code_arg[i]);
            printf("NUMBER_code_arg[%d] = %f\n", i, yylval.val);
            return NUMBER;
        }
        if(islower(code_arg[i][0]))
        {
            yylval.index = code_arg[i][0] - 'a';
            printf("VAR_code_arg[%d] = %d\n", i, yylval.index);
            return VAR;
        }
        if('\n' == code_arg[i][0])
        {
            lineno++;

        }
        i++;
    }


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
    return 0;
}

char ** replace_enter(char ** arg, int * arg_count)
{
    int i = 2, j = 0 , k = 0, p = 0;
    char * code_arg[1024];

    for(; i < *arg_count;)
    {
        if(35 == arg[i][0])
        {
            code_arg[j] = (char *)malloc(1);
            code_arg[j][0] = '\n';
            j++;
            code_arg[j] = (char *)malloc(sizeof(arg[i]));
            memset(code_arg[j], '\0', sizeof(arg[i]));
            k = 0;
            p = 0;
            while(35 == arg[i][p])
            {
                p++;
            }
            while(arg[i][k])
            {
                code_arg[j][k] = arg[i][p];
                k++;
                p++;
            }
            i++;
            j++;
            continue;
        }
        code_arg[j] = (char *)malloc(sizeof(arg[i]));
        memset(code_arg[j], '\0', sizeof(arg[i]));
        strcpy(code_arg[j], arg[i]);
        i++;
        j++;
    }
    *arg_count = j - 1;
    return code_arg;
}

char ** division_operator(char ** arg, int * arg_count)
{
    char ** code_arg = NULL;
    int i = 0, j = 0;

    return code_arg;
}
*/
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
    return 0;
}

void execerror(char * s, char * t)
{
    warning(s, (char *)0);
    longjmp(begin, 0);
}

void code_init()
{
//    progname = argv[0];
//    math_init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    yyparse();
}
