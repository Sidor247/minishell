/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:15:23 by xzulema           #+#    #+#             */
/*   Updated: 2021/09/21 14:34:25 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell -> "
# define PIPE 1

# define QUOTE_ERR -1
# define PIPE_ERR -2
# define FILE_ERR -3
# define RED_ERR -4
# define LAST_HEREDOC -10
# define SYNTAX_ERR -24

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"
# include <termios.h>
# include <term.h>
# include "termcap.h"
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	t_list		*envp;
	int			exit_code;
	pid_t		pid;
}			t_data;

t_data		g_data;

typedef struct s_fds
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		i;
	int		status_heredoc;
	int		status_err;
}			t_fds;

typedef struct s_token
{
	char	**argv;
	char	**in_files;
	char	**in_red;
	char	**out_files;
	char	**out_red;
}			t_token;

typedef struct s_read_files
{
	int		i;
	int		tmppipe[2];
	int		tmpfd;
	int		byte;
	char	buf[1024];
	char	*tail;
}				t_read_files;

void		rl_replace_line(char *s, int n);

char		*get_input(void);
void		push_word(t_list **words, char *start, char *end);
char		**special_split(char *line, char separator, int *size);
char		*special_strchr(char *line, char c, int *flags);
void		parse_vars(char **word);
t_list		*split_word(char *word);
t_token		**parse_input(char *input);

int			exec(char *input);
int			check_redirections(t_list *red);
void		words_processing(t_list **list);
void		free_tokens(t_token **tokens);
void		find_path(char **command);

int			ft_echo(char **args);
int			ft_env(int flag);
int			ft_export(char **args);
int			ft_cd(char **args);
int			ft_pwd(char **args);
int			ft_unset(char **args);
int			ft_exit(char **args);

int			ft_strcmp(const char *s1, const char *s2);
void		none(void *ptr);
void		append_str(char **s1, char *s2);
void		*safe_malloc(size_t size);
void		free_arr(char **arr);

void		print_list(void *content);
void		safe_lstadd_back(t_list **lst, void *content);
t_list		*array_to_list(void **arr);
void		**list_to_array(t_list *list, int *arr_size);
void		lst_remove(t_list **node, t_list *element);

void		copy_envp(char **envp);
char		*ft_getenv(char *name);
void		ft_setenv(char *name, char *value);
void		ft_unsetenv(char *name);

int			parse_error(int code);
void		fatal_error(void);
void		ft_new_line(int status);
int			infile(char **red);
int			outfile(char **red);
int			init_pid_files(t_fds *fd, t_token **arr, t_token *tmparr);
void		fd_close(t_token *arr, t_fds *fd);
int			fd_open(t_token *arr, t_fds *fd);
void		close_pid(t_fds *fd);
int			do_child(char **argv, t_fds *fd);
int			fd_open_first_input(t_fds *fd, t_token *arr);
void		ft_poymal(int tmpin);
int			init_outfd(t_fds *fd, t_token *arr, t_token *tmparr);
void		read_part_first_input(t_fds *fd, t_token *arr, t_read_files *tmpfd);
void		fdin_for_first_input(t_token *arr, t_fds *fd);
void		update_value_fdin(t_token *arr, t_fds *fd);
void		update_value_fdin(t_token *arr, t_fds *fd);
int			check_heredoc(int flag, char **red);
void		ft_heredoc(int status);
int			check_great(int flag, char **red);
void		ft_child_heredoc(int status);
void		ft_pipe_line(int status);
void		cycle_heredoc_utils(t_read_files *tmpfd);
int			check_spaces(char *str);
int			builtins_start(char **argv);
void		lowercased(char *s);
void		ft_poymal_child(int status);

#endif