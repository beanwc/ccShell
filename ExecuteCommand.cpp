#include <iostream>

#include "ExecuteCommandDef.h"

using namespace std;

bool cd_command(char *arg)
{
        if( chdir(arg))
        {
            cout<<"ccShell: cd "<<arg<<": No such file or directory !"<<endl;
            return false;
        }
        return true;
}

bool pwd_command()
{
	char * path = new char[1024];
	if( getcwd(path,1024) == NULL)
	{
        cout<<"ccShell: pwd: Get path filed !"<<endl;
        return false;
	}
	cout<<path<<endl;
	delete [] path;
    return true;
}
