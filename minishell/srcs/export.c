#include "../include/minishell.h"

char **ft_add_env(char *var, t_shell *shell)
{
    char **tmp;
    int i;

    i = 0;
    tmp = malloc(sizeof(char *) * (shell->arg->g_envv_size + 2));
    while (shell->arg->g_envv[i])
    {
        tmp[i] = ft_strdup(shell->arg->g_envv[i]);
        i++;
    }
    tmp[i] = ft_strdup(var);
    tmp[++i] = NULL;
    return (tmp);
}

char *ft_strdup_modified(char *s)
{
    int i;
    char *tmp;

    i = 0;
    while (s[i] != '=')
        i++;
    tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
    i = 0;
    while (s[i])
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char **ft_change_env(char *s, int j, t_shell *shell)
{
    char **tmp;
    int i;

    i = 0;
    tmp = malloc(sizeof(char *) * (shell->arg->g_envv_size + 1));
    while (shell->arg->g_envv[i])
    {
        if (i == j)
            tmp[i] = ft_strdup_modified(s);
        else 
            tmp[i] = ft_strdup(shell->arg->g_envv[i]);
        i++;
    }
    tmp[i] = NULL;
    return (tmp);
}

int ft_exec_export(t_shell *shell)
{
    int i;
    int j;
    char *tmp;

    i = 1;
    while (shell->split_input[i] != NULL)
    {
        j = 0;
        if (ft_variable_check_2(shell->split_input[i]) == 1)
        {
            tmp = ft_var_name(shell->split_input[i]);
            while (shell->arg->g_env_var[j])
            {
                if (ft_strchr(tmp, shell->arg->g_env_var[j]) == 1)
                    shell->arg->g_envv = ft_change_env(shell->split_input[i],\
                    j, shell);
                j++;
            }
        }
        else
            printf("export: not an identifier: %s\n", shell->split_input[i]);
        i++;
    }
    ft_export_add(shell);
    return (0);
}

//shell->arg->g_envv = ft_add_env(shell->split_input[i], shell);
//shell->arg->g_envv_size = ft_g_envv_size(shell);
//shell->arg->g_env_var = ft_g_envv_variable_name(shell);

char *ft_var_name(char *s)
{
    int i;
    char *tmp;

    i = 0;
    while (s[i] != '=')
        i++;
    tmp = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (s[i] != '=')
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}