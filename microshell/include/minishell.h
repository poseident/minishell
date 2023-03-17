/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:36:17 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:41:10 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_tmp
{
	int	double_quote;
	int	sq;
}	t_tmp;

typedef struct s_exec
{
	int	fd[2];
	int	fd_entry;
	int	out_gestion;
}	t_exec;

typedef struct s_pipe
{
	char			*redir;
	char			**redir_dest;
	char			**redir_source;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_varble
{
	char			*var_name;
	int				deleted;
	int				in_env;
	char			*entire_var;
	char			*var_data;
	struct s_varble	*next;
}	t_varble;

typedef struct s_shell
{
	t_varble	*variable;
	t_pipe		*str_pipe;
	char		**env;
	char		**bin;
	char		**first_cmd;
	int			open_check;
	int			sep_count;
	int			sucess_cmd;
	char		*input;
	int			input_size;
	char		**cleaned_variable;
	char		**split_ipt;
	char		**input_ls;
	char		**simple_av;
	int			split_input_size;
}	t_shell;
void	ft_exec_command(t_shell *shell);
int		builtin_exec(t_shell *shell);
void	ft_builtin_exec2(t_shell *shell);
int		check_path(t_shell *shell);
int		redir_array_or_not(char *str);
void	ft_init_struct(t_shell *shell);
void	init_struct_next(t_shell *shell, int redir);
char	**fill_source(char **input, int redir);
char	**fill_dest(char **input, int redir);
int		redir_index(char **input, int start);
int		sep_error(char **t);
int		redir_not2(char c);
int		redir_not(char c);
int		ft_redir_check2(char **t);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	input_redirection(t_pipe *redir, t_shell *shell, t_exec *exec);
int		exec_cmd(char **cmd, int fd_in, int fd_out, t_shell *shell);
int		gestion_heredoc(char *arg_stop);
int		ft_builtin_checker4(char *str);
int		exec_cmd2(char **cmd, int fd_in, int fd_out, t_shell *shell);
int		ft_interation_gestion(t_pipe *redir, t_shell *shell, t_exec *exec);
void	ft_child_fonc(char **cmd, int fd_in, int fd_out, t_shell *shell);
void	output_redirection(int *out_gestion, t_pipe *redir, int *fd_out);
void	ft_exec_built_in(t_pipe *redir, t_exec *exec, t_shell *shell);
void	built_in_env(t_shell *shell, int fd);
void	built_in_echo(char **message, int fd);
void	built_in_pwd(int fd);
void	ft_putchar_fd(char c, int fd);
void	exec_redirection(t_shell *shell);
int		ft_builtin_checker2(char *str);
int		get_source_len(char **input, int redir);
char	**source_redir(char **input, int redir);
int		get_dest_len(char **input, int redir);
void	exec_other(t_shell *shell);
int		redir_error(char **input);
void	ft_exec_bin2(t_shell *shell);
void	ft_export_add3(t_shell *shell, char **source);
char	*ft_lexer_simplify_count(char *str);
char	**fill_bin2(char **bin);
char	**fill_bin(void);
int		input_size(char *input);
int		ft_last_caractere(char *input);
char	*ft_lexer_simplify_count2(char *str);
int		tmp_cleaned2(char *tmp, int *i);
void	ft_heredoc(t_pipe *redir, t_exec *exec, t_shell *shell);
char	**new_env(t_shell *shell);
int		env_size(t_shell *shell);
int		ft_error_red(char **tab);
int		ft_error_red2(char **tab);
void	ft_convert_fd(char *s, t_shell *shell, int fd, int i);
int		ft_print_variable_2_fd(char *tmp, t_shell *shell, int fd);
int		ft_print_variable_fd(char *s, t_shell *shell, int fd);
void	ft_echo_fd(char **input, t_shell *shell, int fd);
void	ft_exec_cd2(t_shell *shell, char *path);
void	ft_builtincheck3(t_shell *shell);
void	builtin_exec5(t_shell *shell);
void	export_add4(t_varble *tmp, char **source, t_shell *shell, int i);
int		bin_check(t_shell *shell);
int		gestion_heredoc(char *arg_stop);
int		exec_cmd2(char **cmd, int fd_in, int fd_out, t_shell *shell);
void	ft_child_fonc(char **cmd, int fd_in, int fd_out, t_shell *shell);
int		redir_index(char **input, int start);
char	**new_env(t_shell *shell);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_exec_bin2(t_shell *shell);
void	ft_exec_export_redir(t_shell *shell, char **source);
int		redir_array_or_not(char *str);
int		redir_array_or_not(char *str);
int		ft_builtin_checker2(char *str);
//builtin_exec
void	ft_exec_cd(t_shell *shell, char *path);
void	ft_exec_exit(t_shell *shell);
void	ft_exec_bin(t_shell *shell);
char	*get_home(t_shell *shell);
char	*get_pwd(t_shell *shell);

//export2.c
char	**ft_change_split_input2(t_shell *shell, int i);
void	ft_export_change_var(t_shell *shell);
void	ft_change_data(t_varble *tmp, char *var);

//unset.c
void	ft_exec_unset(t_shell *shell);

//export.c
void	ft_export_add(t_shell *shell);
void	ft_export_add2(t_varble *tmp, char *var);
void	ft_exec_export(t_shell *shell);
char	*ft_strdup_modified(char *s);
char	*ft_var_name(char *s);

//exec.c
void	ft_builtin_exec2(t_shell *shell);
void	ft_builtin_exec3(t_shell *shell);
void	ft_exec_exit(t_shell *shell);
int		builtin_exec(t_shell *shell);
void	ft_exec_command(t_shell *shell);

//main.c
void	ft_init_sigal(void);
void	exec_other(t_shell *shell);
void	handle_signal(int signum);
int		ft_minishell(char *input, t_shell *shell);

//exec_ls.c
void	ft_exec_ls(t_shell *shell);
void	ft_get_path(t_shell *shell);

//exec_cd.c
void	change_path_and_old(char *path, t_shell *shell);
char	*ft_add_path(char *path, t_shell *shell, char *old);
void	change_back_cd(t_shell *shell);
void	cd_home_change(t_shell *shell);
char	*get_oldpwd(t_shell *shell);

//echo.c
void	ft_echo(char **input, t_shell *shell);
void	ft_convert(char *s, t_shell *shell, int i);
int		ft_flag_n(char *str);
int		ft_print_variable(char *s, t_shell *shell);

//replace.c
void	ft_replace_simple_sub(t_varble *temp, t_shell *shell, int i);
int		replace_simple_variable(t_shell *shell);

//builtin_checker.c
char	**ft_change_split_input(t_shell *shell, int index);
int		ft_variable_check_2(char *s, int i);
int		ft_variable_checker(t_shell *shell);
int		ft_builtin_checker(t_shell *shell);
int		ft_builtin_check(char *input, char *s);

//checker.c
int		quote_check(char *input);
int		no_pipe(char **split_input);
int		ft_checker(char *input);
int		nothing_check(char *input);

//utility4.c
int		cmd_after_pipe_error(char **input);
char	*del_one_path(t_shell *shell);
char	*ft_strjoin(char *str, char *temp);
int		cmp_char(char c1, char c2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//utility_2.c
int		ft_shell_len(char **envv);
char	**ft_copy_env(char **envv);
char	*ft_strdup(char *tmp);
void	ft_putstr(char *s);
int		ft_strlen(char const *str);

//utility.c
int		no_redir(char **split_input);
int		ft_strchr(char *s, char *d);
int		ft_flag_n(char *str);
int		ft_isalnumz(int c);
char	*ft_variable_name_without_dollar(char *s);

//utility3.c
int		ft_sep_count(char **input);
int		ft_strcmp(char *str, char *cmp);
char	*ft_get_var_data(char *s);
int		ft_isalnum(int c);
int		sep_or_not(char *str);

//prompt.c
char	*to_prompt(char *s1, char *s2);
char	*print_prompt(void);
char	*ft_pwd(void);
char	*ft_user(void);

//init.c
void	ft_init_simple_argv(t_shell *shell);
void	ft_init_chain(t_shell *shell, char **env);
void	ft_init_env2(t_shell *shell, char **env);
int		ft_input_size(t_shell *shell);

//sub_module.c
char	*ft_fill_cleaned_variable(char *input);
void	ft_sub_1(int *i, int *j, char *tmp, char *input);
void	ft_sub_2(int *i, int *j, char *tmp, char *input);
void	ft_sub_3(int *i, int *j, char *tmp, char *input);

//variable_len.c
void	ft_variable_len_sub1(char *input, int *i, int *count);
void	ft_variable_len_sub2(char *input, int *i, int *count);
void	ft_variable_len_sub3(char *input, int *i, int *count);
int		ft_variable_len(char *input);

//varibale.c
char	**ft_clean_variable(t_shell *shell);
char	*ft_fill_variable_name(char *s);
char	*ft_fill_variable_data(char *s);
void	ft_fill_variable(t_shell *shell);

//print.c
void	ft_print_env(t_shell *shell);
char	*ft_print_pwd(t_shell *shell);

//parsing.c
void	ft_parsing(t_shell *shell);
char	*ft_input_shell(char *input);
int		ft_last_caractere(char *input);
char	*first_clear(char *input);
int		tmp_cleaned(char *tmp);
int		input_size(char *input);

//lexer.c
char	*ft_lexer_simplify_count(char *str);
char	*ft_lexer_simplify_count2(char *str);
int		ft_count_words(char const *str, char c);
char	*ft_putword(char *word, char const *s, int i, int word_len);
char	**ft_split_words(char *s, char **s2, int num_words, char *s3);
char	*ft_cp(char *s);
char	**ft_split_input(char *s, t_shell *shell);

//echo_redir.c
int		ft_print_variable_2_fd(char *tmp, t_shell *shell, int fd);
int		ft_print_variable_fd(char *s, t_shell *shell, int fd);
void	ft_echo_fd(char **input, t_shell *shell, int fd);
#endif
