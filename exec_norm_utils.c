/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzulema <xzulema@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:26:15 by xzulema           #+#    #+#             */
/*   Updated: 2021/09/18 19:36:12 by xzulema          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_outfd(t_fds *fd, t_token *arr, t_token *tmparr)
{
	if (outfile(arr->out_red))
		fd_close(arr, fd);
	else if (!tmparr)
		fd->fdout = dup(fd->tmpout);
	else
		return (0);
	return (1);
}

int	check_heredoc(int flag, char **red)
{
	int	i;

	i = 0;
	if (!red)
		return (0);
	while (*red)
	{
		if (!ft_strcmp(*red, "<<"))
			i++;
		red++;
	}
	if (i == flag)
		return (1);
	return (0);
}

int	check_great(int flag, char **red)
{
	int	i;

	i = 0;
	if (!red)
		return (0);
	while (*red)
	{
		if (!ft_strcmp(*red, "<"))
			i++;
		red++;
	}
	if (i == flag)
		return (1);
	return (0);
}
