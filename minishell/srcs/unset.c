#include "../include/minishell.h"

char **ft_change_env_unset(int j, t_shell *shell)
{
    char **tmp;
    int i;
    int d;

    d = 0;
    i = 0;
    tmp = malloc(sizeof(char *) * shell->arg->g_envv_size);
    while (shell->arg->g_envv[i])
    {
        if (i == j)
            i++;
        else
        {
            tmp[d] = ft_strdup(shell->arg->g_envv[i]);
            i++;
            d++;
        }
    }
    tmp[d] = NULL;
    shell->arg->g_envv_size = ft_g_envv_size(shell);
    i = 0;
    return (tmp);
}

int ft_exec_unset(t_shell *shell)
{
    int i;
    int j;
    int g;

    i = 1;
    g = 0;
    while (shell->split_input[i])
    {
        j = 0;
        while (shell->arg->g_env_var[j])
        {
            if (ft_strchr(shell->split_input[i], shell->arg->g_env_var[j]) == 1)
            {
                shell->arg->g_envv = ft_change_env_unset(j, shell);
                shell->arg->g_envv_size = ft_g_envv_size(shell);
                shell->arg->g_env_var = ft_g_envv_variable_name(shell);
            }
            if (j < shell->arg->g_envv_size)
                j++;
        }
        i++;
    }
    i = 0;
    return (0);
}