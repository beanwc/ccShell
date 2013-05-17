#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "ShellInitDef.h"

using namespace std;

char * get_userhome()
{
    struct group * group_data;
    char * user_name = NULL;
    char * user_home = NULL;

    group_data = getgrgid(getgid());
    user_name = group_data->gr_name;
    user_home = (char *)malloc(strlen(user_name)+6);

    memset(user_home, '\0', strlen(user_name)+6);

    if(0 == strcmp(user_name, "root"))
    {
        strcpy(user_home, "/");
    }
    else
    {
        strcpy(user_home, "/home/");
    }
    strcat(user_home, user_name);
    strcat(user_home, "/");

    return user_home;
}

char * get_history_file_path()
{
    char * history_file_path = NULL;
    char * user_home = NULL;

    history_file_path = (char *)malloc(100);

    memset(history_file_path, '\0', 100);

    user_home = get_userhome();
    strcpy(history_file_path, user_home);
    strcat(history_file_path, HISTORY_FILE);

    return history_file_path;
}

void replace_username(char path[], char * username)
{
    char * result = NULL;
    char * tmpstr = NULL;
    char * userhome = NULL;
    char * position = NULL;

    result = (char *)malloc(1024);
    tmpstr = (char *)malloc(1025);
    userhome = (char *)malloc(strlen(username) + 6);

    memset(result, '\0', 1024);
    memset(tmpstr, '\0', 1025);
    memset(userhome, '\0', strlen(username) + 6);

    if(0 == strcmp(username, "root"))
    {
        strcpy(userhome, "/");
    }
    else
    {
        strcpy(userhome, "/home/");
    }
    strcat(userhome, username);

    strcpy(tmpstr,path);
    position = strstr(path, userhome);
    if(NULL != position)
    {
        while(NULL != path && path != position)
        {
            path++;
        }
        path[0]='\0';
        strcat(path, "~");
        strcat(path, strstr(tmpstr,userhome) + strlen(userhome));
    }
}

char * get_userinfo()
{
    char * username = NULL;
    char * position = NULL;
    char * host = NULL;
    char * path = NULL;
    char * result = NULL;
    struct group * groupdata;

    host = (char *)malloc(100);
    path = (char *)malloc(1024);
    result = (char *)malloc(1200);

    memset(host, '\0', 100);
    memset(path, '\0', 1024);
    memset(result, '\0', 1200);

    groupdata = getgrgid(getgid());
    username = groupdata->gr_name;

    if(-1 == gethostname(host, 100))
    {
        strcpy(host, "localhost");
    }
    else
    {
        position = strchr(host, '.');
        if(position)
        {
            *position = '\0';
        }
    }

    if(NULL == getcwd(path,1024))
    {
        cout<<"路径获取失败！"<<endl;
    }
    replace_username(path, username);

    if(0 == strcmp(username,"root"))
    {
        sprintf(result, "[%s@%s %s]#", username, host, path);
    }
    else
    {
        sprintf(result, "[%s@%s %s]$", username, host, path);
    }

    return result;
}

char * get_command()
{
    char *command_line = (char *)NULL;
    char * userinfo = NULL;
    char * history_file_path = NULL;

    history_file_path = get_history_file_path();
    userinfo = get_userinfo();
    if(command_line)
    {
        free(command_line);
        command_line = (char *)NULL;
    }
    command_line = readline(userinfo);

    if(command_line && *command_line)
    {
        command_line = rm_space(command_line);
        add_history(command_line);
        write_history(history_file_path);
    }

    return command_line;
}

char * rm_space(char * str)
{
    char * str_tmp = NULL;
    char * position = NULL;

    for (str_tmp = str; isspace(*str_tmp); str_tmp++)
        ;

    if (*str_tmp == 0)
    {
        return (str_tmp);
    }

    position = str_tmp + strlen(str_tmp) - 1;

    while (position > str_tmp && isspace(*position))
    {
        position--;
    }

    *(++position) = 0;

    return str_tmp;
}

void history_init()
{
    char * history_file_path = NULL;

    history_file_path = get_history_file_path();

    using_history();
    stifle_history(MAX_HISTORY);
    read_history(history_file_path);
}

void history_finish()
{
    char * history_file_path = NULL;

    history_file_path = get_history_file_path();

    append_history(history_length, history_file_path);
    history_truncate_file(history_file_path, history_max_entries);
}


void last_dir_init()
{
    last_dir = (char *)malloc(1024);

    memset(last_dir, '\0', 1024);

    getcwd(last_dir, 1024);
}

void variable_init()
{
    int i = 0;

    for(; i < MAX_VAR_NUM; i++)
    {
        variable[i].variable_name = NULL;
        variable[i].variable_value = NULL;
    }
    variable_count = 0;
}

void environment_init()
{
    history_init();
    readline_init();
    last_dir_init();
    variable_init();
    init_arg();
}
