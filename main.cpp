#include <iostream>

#include "ShellInitDef.h"
#include "ExecuteCommandDef.h"

using namespace std;

int main()
{
    char *command_line = NULL;

    while(true)
    {
        command_line = get_command();
        cout<<"Input:"<<command_line<<endl;
    }
}

