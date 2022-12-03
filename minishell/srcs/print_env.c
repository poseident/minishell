#include "../include/minishell.h"

char *ft_print_pwd2(char *str)
{
    int i;
    char *pwd;
    int j;

    j = 0;
    i = 0;
    pwd = malloc(sizeof(char) * (ft_strlen(str) - 3));
    while (str[i] != '/')
        i++;
    while (str[i])
    {
        pwd[j] = str[i];
        i++;
        j++;
    }
    pwd[j] = '\0';
    return (pwd);
}

char  *ft_print_pwd(t_arg *arg)
{
    int i;
    int j;
    char *pwd;

    i = 0;
    while (arg->g_envv[i])
    {
        j = 0;
        if (arg->g_envv[i][j] == 'P')
        {
            j++;
            if (arg->g_envv[i][j] == 'W')
            {
                j++;
                if (arg->g_envv[i][j] == 'D')
                {
                    pwd = ft_print_pwd2(arg->g_envv[i]);
                }
            }
        }
        i++;
    }
    return (pwd);    
}

void ft_print_env(t_shell *shell)
{
    int i;
    int j;

    i = 0;
    while (shell->arg->g_envv[i])
    {
        j = 0;
        while (shell->arg->g_envv[i][j])
        {
            write(1, &shell->arg->g_envv[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
    printf("size of = %d\n", shell->arg->g_envv_size);
}