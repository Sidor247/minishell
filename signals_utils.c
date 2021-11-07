/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzulema <xzulema@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:17:05 by xzulema           #+#    #+#             */
/*   Updated: 2021/09/20 19:45:19 by xzulema          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_poymal(int status)
{
	if (status == SIGINT)
		ft_putendl_fd("^C", STDERR_FILENO);
	else if (status == SIGQUIT)
		ft_putendl_fd("^\\Quit: 3", STDERR_FILENO);
	kill(g_data.pid, status);
}

void	ft_poymal_child(int status)
{
	exit (0);
}

void	ft_new_line(int status)
{
	int	tmpfd;

	tmpfd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	dup2(tmpfd, STDOUT_FILENO);
	signal(SIGINT, ft_new_line);
}

void	ft_heredoc(int status)
{
	ft_putendl_fd("", STDERR_FILENO);
	kill(g_data.pid, SIGINT);
	signal(SIGINT, ft_new_line);
}

void	ft_child_heredoc(int status)
{
	exit (0);
}
