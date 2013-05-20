#include <math.h>
#include <errno.h>

#include "DataStruct.h"
#include "code_yacc.h"

extern int errno;

double errcheck();

double Log(double variable)
{
    return errcheck(log(variable), "log");
}

double Exp(double variable)
{
    return errcheck(exp(variable), "Exp");
}

double Sqrt(double variable)
{
    return errcheck(sqrt(variable), "Sqrt");
}

double Pow(double x, double y)
{
    return errcheck(Pow(x, y), "Exponentiation!");
}

double errcheck(double error_var, char * func_name)
{
    if(EDMO == errno)
    {
        errno = 0;
        execerror(func_name, "Argument out of domain!");
    }
    else if(ERANGE == errno)
    {
        errno = 0;
        execerror(func_name, "Result out of range!");
    }
    return error_var;
}
