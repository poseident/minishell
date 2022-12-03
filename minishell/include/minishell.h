#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>

typedef struct s_varble
{
    char *var_name;
    char *var_data;
    struct s_varble *next;
}           t_varble;

typedef struct s_arg
{
    char **g_envv;
    int g_envv_size;
    char **g_env_var;
    char **g_argv;
    char **command;
    char **env_variable;
}       t_arg;

typedef struct s_shell
{
    t_arg *arg;
    t_varble *variable;
    char *input;
    int index;
    int input_size;
    char **cleaned_variable;
    int var_idx;
    char **split_input;
    int split_input_size;
    int count;
}           t_shell;
//unset.c
char **ft_change_env_unset(int j, t_shell *shell);
int ft_exec_unset(t_shell *shell);

//export.c
char *ft_strdup_modified(char *s);
char *ft_var_name(char *s);
int ft_exec_export(t_shell *shell);
char **ft_change_env(char *s, int j, t_shell *shell);

//exec.c
int builtin_exec(t_shell *shell);
void ft_exec_command(t_shell *shell);

//lexer.c
char	*ft_lexer_simplify_count(char *str);
char	*ft_lexer_simplify_count2(char *str);
int	ft_count_words(char const *str, char c);
char	*ft_putword(char *word, char const *s, int i, int word_len);
char	**ft_split_words(char const *s, char c, char **s2, int num_words, char *s3);
char *ft_cp(char *s);
char	**ft_split_input(char *s);

//varibale.c
void ft_first_node(t_shell *shell);
char *ft_fill_cleaned_variable(char *input);
void ft_clean_variable(t_shell *shell);
void ft_fill_variable(t_shell *shell);
char *ft_fill_variable_name(char *s);
char *ft_fill_variable_data(char *s);

//builtin_checker.c
int ft_variable_check_2(char *s);
int ft_variable_checker(t_shell *shell);
int ft_builtin_checker(t_shell *shell);
int ft_builtin_check(char *input, char *s);

//checker.c
int	ft_checker(char *input);
int quote_check(char *input);
int nothing_check(char *input);

//main.c
int ft_minishell(char *input, t_shell *shell);

//parsing.c
void ft_parsing(t_shell *shell);
char *ft_input_shell(char *input);
int ft_last_caractere(char *input);
char *first_clear(char *input);
int tmp_cleaned(char *tmp);
int input_size(char *input);

//prompt.c
char *to_prompt(char *s1, char *s2);
char *print_prompt();
char *ft_pwd(void);
char *ft_user(void);

//utility.c
char *ft_strdup(char *tmp);
char *ft_variable_name_without_dollar(char *s);
int ft_variable_len(char *input);
int ft_strchr(char *input, char *s);
void	ft_putstr(char *s);
int ft_strlen(char *str);

//init.c
char **ft_g_envv_variable_name(t_shell *shell);
int ft_g_envv_size(t_shell *shell);
char *ft_fill_tmp_env(char *s);
//char **ft_fill_g_env_var(t_shell *shell);
int	ft_input_size(t_shell *shell);
int envv_len(char *str);
void init_arg(t_shell *shell, char **envv);
char **ft_argv(void);

//print.c
char *ft_print_pwd2(char *str);
char  *ft_print_pwd(t_arg *arg);
void ft_print_env(t_shell *shell);

//echo.c
void ft_echo(char **input, t_shell *shell);
void ft_convert(char *s, t_shell *shell);
int ft_flag_n(char *str);
int ft_print_variable(char *s, t_shell *shell);

#endif
