/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:23:04 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 20:23:06 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <dirent.h>
# include <signal.h>
# include "libft.h"
# include "defines.h"
# include "structs.h"

//FOR READLINE:
# include <readline/readline.h>
# include <readline/history.h>
void		rl_clear_history(void);

typedef struct s_data
{
	int			argc;
	char		**argv;
	char		**envp;
	int			fds[3];
	char		**envpath;
	size_t		envsize;
	t_token		*token;
	t_command	*cmd;
	size_t		num_pipes;
	int			**pipes_fd;
	int			copy_fd[3];
	int			*pid;
	int			rss;
}			t_data;

int	g_status;

//GET_ENV:
int			found_key(char *key, char *str);
size_t		get_env(char *key, char **env, char **res);
char		*get_env_ptr(char *key, char **env);
void		get_envpathes(char ***envpath, char **envp);
void		add_new_env(t_data *data, char *str);
int			replace_env(char *str, t_data *data);
void		set_env(t_data *data, char *value, char *key);

//COMMON_UTILS:
void		*ft_malloc(size_t n);
size_t		sizeof_double_arr(void **arr, size_t type_size);
size_t		sizeof_str_arr(char **str);
int			skip_chars(char *str, char c);
char		**copy_double_arr_char(char **src);
void		copy_doublearr(char **src, char **copy, int size);
void		add_str(char **str1, char *str2, size_t size);
int			is_number(char *str);
long		ft_atol(char *str);
int			ret_error(t_data *data,
				t_command *command, char *err_msg, int err_num);
void		qsort_double_arr(char **arr, size_t size);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strnjoin(char *s1, char *s2, size_t n);
void		ft_put2str_fd(char *str1, char *str2, int fd);
void		ft_putstr_fd_nl(char *str, int fd);
size_t		count_words(char *str);
int			bad_env(char *str);
int			close_fds(t_command *cmd);

//TOKEN_UTILS:
t_token		*create_token(char *content, t_token *next, t_token *prev);
void		destroy_token(t_token *token);
t_token		*free_tokens(t_token *head);
int			is_operator(char *str, int len);
int			is_quot(char c);

//TOKEN_RECOGNITION:
void		delimit_token(char *str, int start, int end, t_token **token);
t_token		*token_recognition(char *input, t_data *data);

//EXPANSIONS:
int			remember_normal_chars(char *src, char **res);
int			expand_single_quot(char *src, char **res);
int			expand_double_quot(char *src, char **res, t_data *data);
size_t		expansion_length(char *str);
char		*get_expansion(char *str, char **env, size_t *len, t_data *data);
char		*expand_content(char *src, t_data *data);
void		expand_argv(char *src, t_data *data, t_command *cmd);
char		*expand_redirect_filename(char *src, t_data *data);
char		*try_expand_env(char *src, t_data *data, size_t *i, char **res);
char		*expand_env(char *src, t_data *data, size_t *position);

//PRINT_STRUCTS:
void		print_commands(int fd, t_command *head);
void		print_tokens(int fd, t_token *head);
void		print_double_arr_char(int fd,
				char **str, char delim, char last_char);

//PARSE_COMMANDS:
t_command	*create_command(void);
void		destroy_command(t_command *command);
void		remove_command(t_command *command);
t_command	*parse_command(t_token **token, t_data *data);
t_command	*parse_commands(t_token *token, t_data *data);
int			parse_redirection(t_command *command, t_token *token, t_data *data);
int			check_tokens(t_token *token, t_data *data);
void		add_argv(t_command *cmd, char *str);

//CLEANER:
void		clear_all(t_data *data);
void		free_commands(t_data *data);

//BUILTINS:
int			ft_echo(t_command *command);
int			ft_pwd(t_command *command);
int			ft_cd(t_command *command, t_data *data);
int			ft_export(t_command *command, t_data *data);
int			ft_env(t_data *data);
int			ft_exit(t_command *command, t_data *data, int status, int silent);
int			ft_unset(t_command *command, t_data *data);
int			is_builtin(char *cmd);
int			run_builtin(t_command *command, t_data *data);

//SIGNALS:
void		signal_init(void);
void		signal_control(int sig);

void		run_simple_command(t_data *data, t_command *cmd);

//from pipex:
int			get_next_line(int fd, char **line);
char		*ft_strchr(const char *s, int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr_indx(char *buf, char c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t n);
char		**ft_split(char const *str, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

void		init_data(t_data *data, int argc, char **argv, char **envp);
void		init_fds_pids(t_data *data);

int			ft_pipex(t_data *data);

int			here_doc(t_data *data, char *delimiter);
void		heredoc_sig(int sig);
int			kill_readline(void);

void		redir_input(int fd);
void		redir_output(int fd);
void		pipe_out(int pipe_fd[2]);
void		pipe_in(int pipe_fd[2]);

int			get_cmd_name(char **cmd, char **envpath);

void		close_pipe(int fd[2]);
char		**free_double_str(char **double_arr);
int			**free_double_int(int **double_arr);
int			check_outfile(char *file);
int			check_infile(char *file);
int			check_directory(char *dirname);

#endif
