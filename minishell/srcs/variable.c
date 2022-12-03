#include "../include/minishell.h"

char *ft_fill_cleaned_variable(char *input)
{
    char *tmp;
    int i;
    int j;

    j = 0;
    i = 0;
    tmp = NULL;
    tmp = malloc(sizeof(char) * (ft_variable_len(input) + 1));
    while (input[i] != '=')
    {
        tmp[j] = input[i];
        i++;
        j++;
    }
    tmp[j] = '=';
    i++;
    j++;
    while (input[i])
    {
        if (input[i] == 34)
        {
            i++;
            while (input[i] != 34 && input[i])
            {
                tmp[j] = input[i];
                j++;
                i++;
            }
            if (input[i] == 34)
                i++;
        }
        else if (input[i] == 39)
        {
            i++;
            while (input[i] != 39 && input[i])
            {
                tmp[j] = input[i];
                j++;
                i++;
            }
            if (input[i] == 39)
                i++;
        }
        else
        {
            tmp[j] = input[i];
            j++;
            i++;
        }
    }
    tmp[j] = '\0';
    return (tmp);
}

void ft_clean_variable(t_shell *shell)
{
    int i;

    i = 0;
    shell->cleaned_variable = malloc(sizeof(char *) * (shell->input_size + 1));
    while (shell->split_input[i])
    {
        shell->cleaned_variable[i] = ft_fill_cleaned_variable(shell->split_input[i]);
        i++;
    }
}

char *ft_fill_variable_name(char *s)
{
    int i;
    char *tmp;

    i = 0;
    while (s[i] != '=' && s[i])
        i++;
    tmp = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (s[i] != '=' && s[i])
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char *ft_fill_variable_data(char *s)
{
    int i;
    char *tmp;
    int j;

    j = 0;
    i = 0;
    while (s[i] != '=')
        i++;
    tmp = malloc(sizeof(char) * (ft_strlen(s) - i));
    i++;
    while (s[i])
    {
        tmp[j] = s[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return (tmp);
}

void ft_print_list(t_shell *shell)
{
    t_varble *start;
    start = shell->variable;
    while (start)
    {
        printf("Data : %s \n", start->var_data);
        printf("name : %s\n", start->var_name);
        start = start->next;
    }
}

void    ft_fill_variable(t_shell *shell)
{
    int i;

    i = 0;
    struct s_varble *temp;
    if (shell->count == 0)
         ft_first_node(shell);
    else
    {
        temp = shell->variable;
        while (temp->next != NULL)
            temp = temp->next;
        struct s_varble *newNode;
        while (shell->split_input[i])
        {
            newNode = (struct s_varble *)malloc(sizeof(struct s_varble));
            newNode->var_data = ft_fill_variable_data(shell->cleaned_variable[i]);
            newNode->var_name = ft_fill_variable_name(shell->cleaned_variable[i]);
            newNode->next = NULL; 
            shell->var_idx++;
            temp->next = newNode;
            temp = temp->next;   
            i++;
        }
    }
    ft_print_list(shell);
}

void    ft_first_node(t_shell *shell)
{
    int i;
    i = 0;
    struct s_varble *temp;
    struct s_varble *newNode;
    shell->variable->var_data = ft_fill_variable_data(shell->cleaned_variable[shell->var_idx]);
    shell->variable->var_name = ft_fill_variable_name(shell->cleaned_variable[shell->var_idx]);
    shell->variable->next = NULL;
    shell->var_idx++;
    shell->count++;
    temp = shell->variable;
    while (shell->split_input[i + 1])
    {
        newNode = (struct s_varble *)malloc(sizeof(struct s_varble));
        newNode->var_data = ft_fill_variable_data(shell->cleaned_variable[i + 1]);
        newNode->var_name = ft_fill_variable_name(shell->cleaned_variable[i + 1]);
        newNode->next = NULL; 
        shell->var_idx++;
        temp->next = newNode;
        temp = temp->next;   
        i++;
    }
    return ;
}