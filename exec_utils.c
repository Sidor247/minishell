/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:13:04 by xzulema           #+#    #+#             */
/*   Updated: 2021/09/20 21:49:41 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile(char **red)
{
	if (!*red)
		return (0);
	return (1);
}

int	outfile(char **red)
{
	if (!*red)
		return (0);
	return (1);
}

int	init_pid_files(t_fds *fd, t_token **arr, t_token *tmparr)
{
	int	ret;
	int	tmppipe[2];

	if (infile(arr[fd->i]->in_files))
		fd->fdin = fd_open(arr[fd->i], fd);
	else if (fd->i == 0)
		fd->fdin = dup(fd->tmpin);
	else if (outfile(arr[fd->i - 1]->out_red))
	{
		pipe(tmppipe);
		write(tmppipe[1], NULL, 0);
		close(tmppipe[1]);
		fd->fdin = tmppipe[0];
	}
	dup2(fd->fdin, 0);
	close(fd->fdin);
	ret = init_outfd(fd, arr[fd->i], tmparr);
	return (ret);
}

void	close_pid(t_fds *fd)
{
	dup2(fd->tmpin, 0);
	dup2(fd->tmpout, 1);
	close(fd->tmpin);
	close(fd->tmpout);
}

void	fd_close(t_token *arr, t_fds *fd)
{
	int		i;
	int		flags;

	i = -1;
	while (arr->out_files[++i])
	{
		if (!ft_strcmp(arr->out_red[i], ">>"))
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd->fdout = open(arr->out_files[i], flags, S_IRWXU);
		if (fd->fdout == -1)
		{
			perror("error");
			fd->status_err = 1;
			g_data.exit_code = 1;
		}
		dup2(fd->fdout, 1);
		close(fd->fdout);
	}
}
