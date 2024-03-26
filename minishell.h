/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:44:35 by thole             #+#    #+#             */
/*   Updated: 2024/02/04 12:44:37 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# define SUCCESS -3
# define ERR_MALLOC -2
# define TK_SKIP 0
# define TK_ARG 1
# define TK_PRIO 2
# define TK_WILD 3
# define TK_SINGLE 4
# define TK_DOUBLE 5
# define TK_INPUT 6
# define TK_OUTPUT 7
# define TK_DLMTR 8
# define TK_APPEND 9
# define TK_PIPES 10
# define TK_EXPAND 11
# define TK_AND 12
# define TK_OR 13
# define TK_ENV_VAR 14
# define BUILTIN 16
# define NOTHING 17
# define EXIT 777
# define TK_END_PRIO 18
# define TK_END 19
# define ERR_PARS -18
# define ERR_LEFT_ANGLE -100
# define ERR_RIGHT_ANGLE -99
# define ERR_PIPE -98
# define ERR_AND -97
# define ERR_SINGLE -56
# define ERR_DOUBLE -55
# define TEMP_AND 20
# define SIZE 16384
# define IS_TTY 21
# define FAILURE -1000000
# define WINNING 1000000
# define ERR_FORK -200
# define QUIT -3000
# define CONTINUE 700
# define BREAK -700
# define NORMAL 888
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURP "\033[1;95m"
# define PURP2 "\033[1;35m"
# define ORANGE "\033[1;91m"
# define LIGHTB "\033[1;36m"
# define BLUE "\033[1;94m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"
# define PROMPT "\001\033[1;96m\002Minishell$ \001\033[0m\002"
# define PROMPT_HD "\001\033[38;5;220m\002mini_doc> \001\033[0m\002"
# define ERR_PTSES "\033[1;31mMinishell: error: unclosed parenthesis\n\033[0m"
# define ERR_QUOTES "\033[1;31mMinishell: error: unclosed quotes\n\033[0m"
# define ERR_X1 "\033[1;95mMinishell: exit: "
# define ERR_X2 ": numeric argument required\n\033[0m"
# define ERR_MINI_DOC "\033[0;32mMinishell: warning: "
# define ERR_MINI_DOC2 "mini_doc delimited by end-of-file (wanted `"
# define ERR_CD "getcwd: cannot access parent directories: "
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <malloc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_sig;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_parse_list
{
	char				c;
	int					token;
	struct s_parse_list	*next;
	struct s_parse_list	*prev;
}						t_parse_list;

typedef struct s_tokens
{
	char				*str;
	int					token;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}						t_tokens;

typedef struct s_file
{
	char				**files;
	char				*here_doc_file;
	int					*modes;
	int					*token;
}						t_file;

typedef struct s_tree
{
	t_file				*file;
	char				**cmd_tab;
	char				*infile;
	char				*outfile;
	int					err_code;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

typedef struct s_struct
{
	char				*str;
	char				**tab;
	char				*infile;
	char				*outfile;
	int					mode_in;
	int					mode_out;
	int					token_in;
	int					token_out;
	int					exit;
	char				*here_doc_file;
	char				*delim;
	char				**env;
	int					pipe[2];
	int					is_pipe;
	int					here_doc[2];
	pid_t				pid;
	t_parse_list		*p_lst;
	t_tokens			*l_lst;
	t_tokens			*head_ll;
	t_parse_list		*head_parse;
	t_tokens			*temp;
	char				**dup_env;
	int					end;
	int					fd_in;
	int					fd_out;
	int					here_doc_open;
	int					is_first;
	int					is_last;
	int					last_fd;
	int					count_pipes;
	int					counter;
	int					exit_val;
	t_file				*file;
	long long int		exit_arg;
	int					num_err_exit;
	char				*string_error;
	int					bad_exit;
	int					size_env;
	int					exported;
	int					unsetted;
	int					error_cd;
	int					x_i;
	int					x_j;
	int					save_in;
	int					save_out;
	int					was_in;
	int					was_out;
	int					i_n_quotes;
	int					nl;
}						t_struct;

void					sig_int(int code);
void					sig_quit(int code);
void					sig_init(t_struct *s);

int						ft_prototype_list(t_struct *s);
void					ft_free_parse_list(t_parse_list *list);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_change_list(t_struct *parse);
void					ft_free_changed_list(t_tokens *list);
int						open_heredoc(t_tokens **list, char *lim);
char					*ft_gnl_strjoin(char *s1, char *s2, size_t len);
int						parse_heredoc(t_struct *s);
int						quote_checker(char *str);
void					ft_free_changed_list(t_tokens *list);
int						execute(t_struct *s, t_tokens *list, int depth,
							int pipe);
void					ft_print_list2(t_tokens *lst);
t_tokens				*new_list(void);
int						go_to_next_stop(t_tokens **list);
char					*get_path(char *cmd, char **env, int *flag);
int						exec(t_struct *s, t_file *file);
void					ft_echo(t_struct *s);
void					ft_pwd(t_struct *s);
void					ft_cd(t_struct *s);
void					ft_export(t_struct *s, char **env);
int						ft_export_notchild(t_struct *s, char **env);
void					ft_unset(t_struct *s, char **env);
void					ft_env(t_struct *s, char **env, int fake_env);
void					ft_exit(t_struct *s);
int						do_files(t_file *f, t_struct *s);
void					free_tab(char **tab);
void					free_array(char **array);
int						token_redirection(int token, int mode);
int						open_output(char *s, int token, t_struct *st);
int						open_append(char *s, int token, t_struct *st);
int						open_input(char *s, int token, t_struct *st);
int						open_dlmtr(char *s, int token, t_struct *st);
char					*takeoff_quotes(char *str);
void					count_pipes(t_struct *s);
char					*ft_strnjoin(char *s1, char *s2, size_t size_s1,
							int start);
void					free_env(char **env);
void					free_all(t_struct *s, int ex);
char					*expand(char *str, char **env, t_struct *s);
int						epur_files(t_file *f, t_struct **s, int i);
void					flush_files(t_file *file, t_struct *s);
void					sig_child(void);
int						is_alnum_undescore(int c);
char					**dup_array(char **tab);
int						check_if_is_in_env2(char *env_line, char *var);
int						check_list(t_tokens *list);
void					set_val(t_struct *s, int i);
void					ctr_d_exit(t_struct *s);
void					init_args(t_struct *s);
void					init_heads_free(t_struct *s);
int						change_paths(t_struct *s, char *oldpwd, int check);
int						print_error_cd(t_struct *s);
void					perror_cd(char *s);
int						free_error_cd(t_struct *s, char *home);
int						free_cd(t_struct *s, char *home);
int						err_home(t_struct *s, char *home);
char					*find_home_in_env(char **env, char *to_find);
int						is_only_num(char *s);
int						ft_strlen_ps(char *s, int i, int j);
int						longlonglen(long long int n);
int						export_check_value(t_struct *s, int i);
int						new_value(t_struct *s, int i, int j);
int						export_value(t_struct *s, int i, int j);
int						printf_and_exit_export(t_struct *s, int i);
int						sort_and_print_env(char **env, int i, int j);
void					handle_errno(t_struct *s, char *path);
void					exec_buildin(t_struct *s, char **env, int i, char *cmd);
int						ft_is_buildin(char *s);
void					exit_error(char *str);
void					exit_error_array(char *str, t_struct *s, char *s1,
							int index);
int						check_parenthesis(char *str);
int						parser_args(t_struct *s);
void					init_minishell(t_struct *s);
void					reset_signal(t_struct *s);
int						init_env(t_struct *s, char **env);
int						wait_pid(t_struct *s);
void					free_when_exit(t_struct *s);
void					ctr_d_exit(t_struct *s);
int						is_token(int token);
int						end_heredoc(t_tokens **list, char *buf, char *str);
int						print_error(char *str);
int						check_str(char **str);
int						ret_n_print(char *lim, char *buf, char *str,
							t_tokens **list);
int						add_to_buffer(char **buf, char *str);
int						ft_strcmp2(char *s1, char *s2);
char					*not_found(char *cmd, char **all_path, char *path,
							int *flag);
char					*return_cmd(char *path, char **all_path, char *str);
int						print_error2(char *str);
int						is_forbidden(int token);
int						create(t_tokens **list, int *size);
int						create_till_next_arg(t_struct **parse, t_tokens **list,
							int *size);
int						step(t_tokens **list);
t_tokens				*new_list(void);
t_tokens				*new_node(int size);
t_parse_list			*skip_first(t_parse_list *copy);
int						next_stop_token(int token);
int						check_argument(int token);
int						check_if_arg(t_struct *parse);
int						check_which_argument(t_struct **parse, t_tokens **list,
							t_parse_list **copy, int *size);
int						do_quotes(t_struct **parse, t_tokens **list,
							t_parse_list **copy, int *size);
int						do_next_stop_token(t_struct **parse, t_tokens **list);
int						recursive_line_size(t_struct **parse, int *type,
							int *size);
int						get_token(t_struct **parse, t_tokens **list);
void					size_until_nothing_or_special_char(t_struct **parse,
							int *type, int *size);
int						quote_line_fill(t_struct **parse, t_tokens **list,
							int type, int *size);
int						get_size(t_struct **parse, t_tokens **list, int *size);
int						is_quotes(int c);
char					*find_in_path(char *needle, char **env, int len,
							t_struct *s);
int						is_alnum_undescore(int c);
void					delete_strings(char *s1, char *s2);
void					get_len_variable(char *str, int *len, t_struct *s);
void					get_indexes(int *i, int *j, t_struct *s, int try);
void					add_to_buff(char *string, char *str, int *i, int *j);
void					flush_array(char **tab);
int						epur_files(t_file *f, t_struct **s, int i);
int						epur_commands(t_struct **s, t_file *f, int i);
void					flush_files(t_file *file, t_struct *s);
void					set_files(t_file *file);
int						epur_str(char *s1, t_struct **s, int *i);
int						is_arg(int token);
int						create_new_file(t_file *f, char *file, int type,
							int token);
int						execute_buildin_normal(t_struct *s, t_file *file);
int						check_buildin(t_struct *s);
int						recursive_filler(t_struct **s, t_tokens **list,
							t_file *file);
int						open_files(t_file *f, t_struct *s);
void					try_redirections(t_file *f, t_struct *s);
void					try_dups(t_file *f, t_struct *s);
int						fill_cmd_tab(t_tokens **list, t_struct **s);
int						open_struct_file(char *s, int mode, t_struct *st);
int						go_home(t_struct *s);
int						parser(t_struct *s);
int						parser_part_two(t_tokens *temp);
void					dup_fds(t_struct *s);
void					close_dup_fds(t_struct *s);
int						val_wait(t_struct *s, int *ret);
void					path_not_found(t_struct *s, char *cmd);
void					set_new_indexes(int *i, int *j, t_struct *s);
char					*expand_heredoc(char *str, char **env, t_struct *s);

#endif
