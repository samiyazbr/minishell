/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:57 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 16:13:22 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# include "tokens.h"
# include <sys/stat.h>
# include <limits.h>
# include <stdbool.h>

# define FALSE 0
# define TRUE 1
# define BUFFER_SIZE 42

extern int		g_dupstdin;

typedef struct s_shell
{
	t_list	*step;
	t_list	*tokens;
	t_list	*steps_to_free;
	char	**args;
	char	**env;
	char	**declared_env;
	int		last_exit_code;
	char	*line;
	int		*fd;
	char	*current_line;
	t_list	*heredoc_contents;
	int		exp;
	int		flag;
	bool	sin;
	bool	doub;
	size_t	start;
	size_t	end;
	int		special_flag;
}	t_shell;

typedef struct s_execflags
{
	bool	exit;
	bool	valid_redirection;
	int		w_status;
	bool	first_flag;
	int		action;
	int		step_num_start;
	int		step_num;
}	t_execflags;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	char			*limiter;
}t_redir;

typedef struct s_cmd
{
	t_list	*args;
	char	**arg_arr;
	int		pid;
	t_list	*redirs;
}t_cmd;

typedef struct s_exec
{
	t_cmd	*cmd;		
	char	*subexpr_line;
	int		exit_code;
	int		pipe_next;
	int		num_total_pipes;
}t_exec;

typedef struct s_env_s
{
	int		env_size;
	char	**envp;
	char	**key;
	char	**value;
}t_env_s;

void	print_data_ex(t_list *steps);

/*Shell Utils functions*/
t_shell	*init_shell(char **envp, int *error);
char	**copy_env(char **envp);

/*Parsing and free*/

int		is_pipe(t_token *token);
int		redir(t_token *token);
int		errors_in_tkn(t_list *tokens);
t_list	*ft_get_steps(t_list *tokens, int *error);
void	convert_str_to_arr(void *step_ptr);
t_exec	*create_exec(t_list *start, t_list *end, t_token **t_content,
			t_list *tokens);
	/*Errors and free*/

void	ft_free(char *str);
void	ft_free2(void *str);
void	ft_free_array(char **array);
void	free_token(void *token);
void	ft_free_shell(t_shell *shell);
void	free_steps(t_list **step_lists);
void	free_exec_step(void *exec_step_ptr);
void	free_redir(void *redir_ptr);
int		ft_is_token_error(t_shell *minishell, char *line, int *error);
int		handle_get_steps_error(t_shell	*shell, int *error, char *line);
void	*free_parseerror(t_token *token, int num);
//utils

char	**arr_dup(char **arr);
char	*print_prompt(t_shell *shell);
int		add_to_history(char *line);
char	*get_env(const t_shell *shell, const char *name);
void	set_quotes(const char ch, char *quote, int *in_quote);
t_list	*tokenize_inside_envvar(const char *line, size_t *idx);
long	ft_atox(const char *str, int *check);
void	ft_close(int *fd);
int		is_env_var(const char *str, size_t *i);

//gnl

char	*get_next_line(int fd);
char	*read_buffer(int fd, char *left_str);
char	*ft_get_line(char *left_str);
char	*remain(char *left_str);
char	*ft_gnl_strjoin(char *s1, char *s2);

//builtins utils

void	move_to_home(t_shell *shell, t_exec *command_block,
			char **env, char *home);
size_t	env_len(char **env);
void	export_error(char *arg);
char	**resize_str_arr(char **old, size_t new_size);
bool	assign_val_to_env(t_shell *shell, char *to_look,
			char *key, char *key_val);
void	print_the_export_env(char **val, char **key);
void	run_export_with_args(char **args, t_shell *shell, bool *error);
void	remove_env_var(t_shell *shell, char **env_copy, char *to_look);
void	remove_declared_env_var(t_shell *shell, char **env_copy, char *to_look);

//builtins

int		ft_strcmp(char *s1, char *s2);
bool	is_builtin(t_exec *step);
bool	parent_builtin(t_exec *step);
bool	run_builtin(t_exec *step, t_shell *shell, bool child);
void	update_pwd(char **env, t_shell *shell);
void	update_oldpwd(t_shell *shell, char **env, char *oldpwd);
void	cd_to_path(t_shell *shell, t_exec *step, char **env);
void	cd_to_home(t_shell *shell, t_exec *step, char **env, char *home);
void	ft_cd(t_exec *step, char **env, t_shell *shell);
bool	ft_check(char *s1);
void	write_echo_content(t_exec *step, int i);
void	ft_echo(t_exec *step, t_shell *shell);
void	ft_env(t_shell *shell, t_exec *step);
void	check_valid_args(t_shell *shell, t_exec *step, int i, int *j);
void	ft_exit(t_exec *step, t_shell *shell, int child);
void	update_env(t_shell *shell, const char *str);
bool	check_export_arg(const char *arg);
void	update_declared_env(t_shell *shell, char *str);
void	ft_export(t_shell *shell, t_exec *step);
char	*ft_getenv(t_shell *shell, const char *name);
int		ft_putenv(const char *string, t_shell *minishell);
void	ft_pwd(t_exec *step, t_shell *shell);
void	unset_var(t_shell *shell, const char *var);
void	unset_declared_var(t_shell *shell, const char *var);
void	ft_unset(t_shell *shell, t_exec *step);
char	*join_and_free(char *s1, char *s2, int flag);
int		*run_parent_builtin(t_exec *step, t_shell *shell, int *fd);
int		run_child_builtin(t_shell *shell, t_exec *step,
			int *fds, int *heredoc_fds);

//exec
void	minishell_exec(t_shell *shell, char *line);
void	exec_cmds(t_shell *shell, t_list *exec_steps,
			int step_number, char *current_line);
void	init_cmds(t_shell *shell, int *out_fd,
			t_execflags *flags, int step_number);
t_list	*begin_step(t_execflags *flags, t_list *exec_steps, t_exec **step);
t_list	*wait_and_get_exit(t_shell *shell, t_exec *step,
			t_list *exec_steps, t_execflags *flags);
t_list	*wait_cmds(t_list *steps, t_execflags *flags);
t_list	*reset_to_step(t_list *exec_steps, int step_number_start);
int		get_exit(t_list *exec_steps, t_exec *step, t_execflags *flags);
int		is_dir(const char *path);
t_exec	*run_exec_cmds(t_shell *shell, t_list **steps, int *out_fd,
			t_execflags *flags);
bool	exec_subexpr(t_shell *shell, t_exec *step, t_execflags *flags,
			t_list **steps);
void	set_cmd_path(t_shell *shell, t_exec *step);
void	check_command(t_shell *shell, t_list **steps, t_exec *step,
			t_execflags *flags);
bool	handle_invalid_path(t_shell *shell, t_exec *step,
			t_execflags *flags);
bool	handle_invalid_cmd(t_shell *shell, t_exec *step,
			t_execflags *flags);
int		*first_cmd(t_exec *step, int *fds, t_shell *shell, int out_fd);
int		*other_cmd(t_exec *step, int *fds, t_shell *shell, int out_fd);
int		parse_and_fork_subexpr(t_shell *shell, t_exec *step,
			t_list **sub_steps);
bool	cmd_not_found_check(t_exec *step, bool valid_redirs);
bool	file_not_found_check(t_exec *step, bool valid_redirs);
bool	permission_denied_check(t_exec *step, bool valid_redirs);
void	cmd_not_found(t_shell *shell, t_exec *step, bool *exit_flag);
void	cmd_is_dir(t_shell *shell, t_exec *step, bool *exit_flag);
void	file_not_found(t_shell *shell, t_exec *step, bool *exit_flag);
void	permission_denied(t_shell *shell, t_exec *step, bool *exit_flag);
void	dup_pipe_fds(t_redir *inredir, int *heredoc_fds, t_exec *step,
			int *fd);
void	dup_redir_fds(int in_fd, int out_fd);
int		*close_all(int *fds, int *in_fd, int *out_fd,
			int *heredoc_fds);
void	dup_heredoc_fds(t_redir *inredir, int *heredoc_fds, int *fdtmp);
void	dup_pipes_and_redirs(t_exec *step, int *fds, int in_fd,
			int out_fd);
void	child_builtin_cleanup(int *out_fd, int *in_fd, int *fdtmp,
			int exit_code);
void	close_fds(const t_exec *step, int *fds, int *fdtmp);
char	*get_full_path(char *bin, char **env);
int		run_child_builtin2(t_shell *shell, t_exec *step, int *fds,
			int *heredoc_fds);

//redec

bool	open_redirs(t_shell *shell, t_exec *step, bool *exit_flag, int *out_fd);
bool	check_valid_redir(t_exec *step);
t_redir	*last_inredir(t_list *in_redir);
int		count_heredocs(t_list *substeps);
void	skip_sub_heredocs(t_list *heredocs, int num_skipped);
bool	check_input_redir(t_redir	*redir_file);
bool	check_output_redir(t_redir	*redir_file);
bool	check_redir_file_exist(t_redir *redir_file, int *out_fd);
int		check_access_for_redir(t_redir *redir_file, t_list **redir);
void	run_heredocs(t_shell *shell);
void	cleanup_resources(char **limiter, char **line);
t_list	*run_here_docs(t_shell *shell, t_list *steps);
bool	create_redir_file(t_redir *redir_file, int *out_fd);

//signals

void	handle_ctrl_d(const char *line, t_shell *shell);
void	sigint(int sig);
void	sigquit(int sig);
void	heredoc_sig(int sig);
void	sigint_interactive(int sig);

/*Tokens*/

t_list	*tokenize_the_input(t_shell *minishell, char *line, int *error);
t_list	*token_a_single_quote(t_shell *minishell, char *line, size_t *i);
t_list	*token_a_double_quote(t_shell *minishell, char *line, size_t *i);
t_list	*token_operator(char *line, size_t *i);
t_list	*token_nested_expr(t_shell *minishell, char *line, size_t *i);
t_list	*token_an_env(t_shell *shell, char *line, size_t *idx);
t_list	*next_token(t_shell *shell, t_token *tkn, char *line);
t_token	*to_end_of_token(char *line, size_t *y, t_token *token);
int		ft_is_dollar_env(char *str);
int		clean_token_env(t_list **lst, t_list **tokens);
int		second_part(t_shell *minishell, char *line, size_t *i, t_list **tokens);
char	*expand_env_var_isalpha(t_shell *s, size_t *i, char *str);
char	*expand_env(t_shell	*shell, char *str);
void	new_expand(t_shell *shell, t_token *tkn, size_t i);
char	*remove_quotes(size_t *i, char *str);
char	*create_env_var_str(t_shell *shell, char *str,
			size_t	start, size_t end);
int		move_to_end(t_shell *shell, char *str, size_t *i);
int		check_to_end(char *str, size_t i, size_t start, size_t end);
char	*trim_str_dollar(char *str);
char	*trim_str_quotes(char *str);
char	*eat_quotes(char *str);
void	set_which_quotes(char *str, size_t i, bool *single, bool *doubles);
void	set_which_quotes2(t_shell *shell, char *str, size_t i);
char	*create_env_var_str2(t_shell *shell, char *str, size_t i);
char	*numeric_helper(char *str, size_t i, t_shell *s);
char	*last_loop_helper_env2(char *str, t_shell *s, size_t i,
			char *expansion);
char	*last_loop_alnum(char *str, char *after, char *expansion, char *before);
char	*ft_quotes_env(char *str, t_shell *s, size_t i);
char	*ft_free_and_return_loop(t_shell *s, char *str,
			char *expansion, char *before );
int		is_special_red(char *line, size_t i, t_shell *shell);
char	*expand_num_sq(t_token *tkn, size_t start);
void	break_after_space(t_token *tkn, size_t i);
char	*expand_env_original(t_shell	*s, char *str);
char	*expand_env_var_isalpha_basic(t_shell *s, size_t *i, char *str);
void	ft_initialize_expand(t_shell *shell, size_t *i);
int		plain_text_part(t_shell *shell, char *line,
			size_t *idx, t_list **tokens);
char	*ft_return_quotes_env(t_shell *s, char *str, size_t i);
char	*handle_dollar_space(t_shell *s, char *str, size_t i);
#endif
