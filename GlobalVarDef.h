#ifndef GLOBALVAR_H_INCLUDED
#define GLOBALVAR_H_INCLUDED

#define MAX_VAR_NUM 100

struct _Variable
{
    char * variable_name;                 // variable name
    char * variable_value;                // variable value
};

extern char * last_dir;
extern _Variable variable[MAX_VAR_NUM];
extern int variable_count;

#endif // GLOBALVAR_H_INCLUDED
