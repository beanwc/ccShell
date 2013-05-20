#ifndef DATA_STRYCT_H_INCLUDED
#define DATA_STRYCT_H_INCLUDED

class symbol
{

    public:
        char * name;
        short type;
        symbol * next;
        union
        {
            double val;
            double (*ptr)();
        }value;

        symbol(char * symbol_name, int symbol_type, double symbol_value);
        symbol * search_symbol(char * symbol_name);
};

#endif //DATA_STRYCT_H_INCLUDED
