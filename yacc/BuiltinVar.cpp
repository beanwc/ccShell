#include <math.h>
#include <iostream>

#include "DataStruct.h"
#include "code_yacc.h"

using namespace std;

extern double Log(double variable);
extern double Exp(double variable);
extern double Sqrt(double variable);

struct _CONST
{
    char * name;
    double vaule;
};

struct _MATH
{
    char * name;
    double (*math_function)();
};

_CONST const_var[] =
    {
        {"PI",  3.14159265358979323846},
        {"E",   2.71828182845904523536},
        {"DEG", 57.29577951308232087680},
        {(char *)NULL, 0}
    };

_MATH builtin_math[] =
    {
        {"sin",     sin},
        {"cos",     cos},
        {"log",     Log},
        {"exp",     Exp},
        {"sqrt",    Sqrt},
        {"abs",     fabs},
        {(char *)NULL, 0}
    };

void math_init()
{
    int i = 0;
    symbol * symbol_var;

    for(i = 0; const_var[i].name; i++)
    {
        new symbol(const_var[i].name, VAR, const_var[i].vaule);
    }

    for(i = 0; builtin_math[i].name; i++)
    {
        symbol_var = new symbol(builtin_math[i].name, BLTIN, 0.0);
        symbol_var->value.ptr = builtin_math[i].math_function;
    }
}
