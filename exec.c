/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 23:40:34 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/20 21:47:01 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_flex(char **argv)
{
	char	**envp;
	int		status;

	signal(SIGINT, ft_poymal_child);
	signal(SIGQUIT, ft_poymal_child);
	envp = (char **)list_to_array(g_data.envp, NULL);
	status = execve(argv[0], argv, envp);
	ft_putstr_fd("mshl: command not found: ", STDERR_FILENO);
	ft_putendl_fd(argv[0], STDERR_FILENO);
	g_data.exit_code = status;
	exit(status);
}

int	do_child(char **argv, t_fds *fd)
{
	int		ret;
	int		status;

	if (!argv[0])
		return (0);
	lowercased(argv[0]);
	ret = builtins_start(argv);
	if (ret != -50)
		return (ret);
	if (!ft_strchr(argv[0], '/'))
		find_path(argv);
	g_data.pid = fork();
	if (g_data.pid == 0)
		child_flex(argv);
	signal(SIGINT, ft_poymal);
	signal(SIGQUIT, ft_poymal);
	waitpid(g_data.pid, &status, 0);
	signal(SIGINT, ft_new_line);
	signal(SIGQUIT, SIG_IGN);
	return (status);
}

void	execute(t_token **arr)
{
	t_fds	fd;
	int		ret;

	fd.tmpin = dup(0);
	fd.tmpout = dup(1);
	fd.i = -1;
	while (arr[++fd.i])
	{
		fd.status_err = 0;
		ret = init_pid_files(&fd, arr, arr[fd.i + 1]);
		if (!ret)
		{
			pipe(fd.fdpipe);
			fd.fdin = fd.fdpipe[0];
			fd.fdout = fd.fdpipe[1];
		}
		dup2(fd.fdout, 1);
		close(fd.fdout);
		if (fd.status_err)
			continue ;
		g_data.exit_code = do_child(arr[fd.i]->argv, &fd);
	}
	close_pid(&fd);
}

int	exec(char *input)
{
	t_token	**arr;

	arr = parse_input(input);
	if (!arr)
	{
		g_data.exit_code = 1;
		return (EXIT_FAILURE);
	}
	execute(arr);
	free_tokens(arr);
	return (EXIT_SUCCESS);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free_arr(tokens[i]->argv);
		free_arr(tokens[i]->in_files);
		free_arr(tokens[i]->in_red);
		free_arr(tokens[i]->out_files);
		free_arr(tokens[i]->out_red);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
