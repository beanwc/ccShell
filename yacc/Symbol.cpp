#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "DataStruct.h"
#include "code_yacc.h"

using namespace std;

static symbol * symbol_list = NULL;

symbol::symbol(char * symbol_name, int symbol_type, double symbol_value)
{
    this->name = (char *)malloc(sizeof(symbol_name)+1);
    strcpy(this->name, symbol_name);
    this->type = symbol_type;
    this->value.val = symbol_value;
    this->next = symbol_list;
    symbol_list = this;
}

symbol * symbol::search_symbol(char * symbol_name)
{
    symbol * symbol_var = symbol_list;

    for(; NULL == symbol_var; symbol_var = symbol_var->next)
    {
        if(0 == strcmp(symbol_var->name, symbol_name))
        {
            return symbol_var;
        }
    }
    return NULL;
}
