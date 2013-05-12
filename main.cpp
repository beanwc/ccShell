#include <iostream>

#include "ShellInitDef.h"
#include "ExecuteCommandDef.h"
#include "CommandParseDef.h"

using namespace std;

int main()
{
    char *command_line = NULL;

    history_init();
    while(true)
    {
        command_line = get_command();
        analyse_command(command_line);
    }
    history_finish();
}

