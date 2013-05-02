#include <iostream>
#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

char * get_line();
char * get_userinfo();

int main()
{
    char *read_line = NULL;

    while(true)
    {
        read_line = get_line();
        cout<<read_line<<endl;
    }
}

char * get_userinfo()
{
    char * username = NULL;
    char host[100], path[1024], result[1200];
    struct group * groupdata;

    memset(host, '\0', 100);
    memset(path, '\0', 1024);
    memset(result, '\0', 1200);

    strcat(result, "[");

    groupdata = getgrgid(getgid());
    username=groupdata->gr_name;
    strcat(result, username);
    strcat(result, "@");

    if(gethostname(host, 100) == -1)
    {
        strcpy(host, "localhost");
    }
    strcat(result, host);
    strcat(result, ":");

    if( getcwd(path,1024) == NULL)
    {
        cout<<"路径获取失败！"<<endl;
    }
    strcat(result, path);
    strcat(result, "]");

    if(strcmp(username,"root") == 0)
    {
        strcat(result, "#");
    }
    else
    {
        strcat(result, "$");
    }

    return result;
}

char * get_line()
{
    char *read_line = (char *)NULL;
    char * userinfo = NULL;

    userinfo = get_userinfo();
    if(read_line)
    {
        delete read_line;
        read_line = (char *)NULL;
    }
    read_line = readline(userinfo);

    if(read_line && *read_line)
        add_history(read_line);

    delete userinfo;
    return(read_line);
}
