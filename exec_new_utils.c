/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:16:59 by xzulema           #+#    #+#             */
/*   Updated: 2021/09/20 20:48:38 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cycle_heredoc_utils(t_read_files *tmpfd)
{
	int	byte;
	int	num;

	num = tmpfd->byte;
	while (1)
	{
		byte = read(STDERR_FILENO, tmpfd->buf + num, 1024);
		if (tmpfd->buf[num + byte - 1] == '\n')
			break ;
		num += byte;
	}
	tmpfd->buf[num + byte] = 0;
}

void	cycle_heredoc(char *file, t_read_files *tmpfd, char *next)
{
	signal(SIGINT, ft_child_heredoc);
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		tmpfd->byte = read(STDERR_FILENO, tmpfd->buf, 1024);
		tmpfd->buf[tmpfd->byte] = 0;
		if (tmpfd->byte == 0)
			break ;
		if (tmpfd->buf[tmpfd->byte - 1] != '\n')
			cycle_heredoc_utils(tmpfd);
		if (tmpfd->byte != 1)
		{
			if (!ft_strncmp(tmpfd->buf, file, tmpfd->byte - 1))
				break ;
		}
		if (!next)
			append_str(&tmpfd->tail, tmpfd->buf);
	}	
}

int	heredoc(char *file, t_read_files *tmpfd, char *next)
{
	int		fdpipe[2];
	int		status;

	status = 0;
	pipe(fdpipe);
	g_data.pid = fork();
	if (g_data.pid == 0)
	{
		cycle_heredoc(file, tmpfd, next);
		ft_putstr_fd(tmpfd->tail, fdpipe[1]);
		exit (status);
	}
	signal(SIGINT, ft_heredoc);
	waitpid(g_data.pid, &status, 0);
	close(fdpipe[1]);
	return (fdpipe[0]);
}

int	new_great_part(char *file, char *red, t_read_files *tmpfd, char *next)
{
	int	tfd;
	int	flag;

	flag = 0;
	tfd = 0;
	if (!ft_strcmp(red, "<<"))
		tfd = heredoc(file, tmpfd, next);
	else if (!ft_strcmp(red, "<"))
	{
		tfd = open(file, O_RDONLY);
		if (tfd == -1)
			return (tfd);
		if (next)
			close(tfd);
	}
	return (tfd);
}

int	fd_open(t_token *arr, t_fds *fd)
{
	int				i;
	int				tfd;
	t_read_files	tmpfd;

	i = -1;
	tmpfd.tail = ft_strdup("");
	fd->status_heredoc = 0;
	while (arr->in_files[++i])
	{
		tfd = new_great_part(arr->in_files[i], arr->in_red[i],
				&tmpfd, arr->in_files[i + 1]);
		if (tfd == -1)
		{
			ft_putstr_fd("mshl: ", STDERR_FILENO);
			ft_putstr_fd(arr->in_files[i], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			g_data.exit_code = 1;
			fd->status_err = 1;
		}
	}
	free(tmpfd.tail);
	return (tfd);
}
