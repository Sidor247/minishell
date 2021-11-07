/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:26:46 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 13:49:15 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	n_check(char *s)
{
	if (!ft_strncmp(s, "-n", 2))
	{
		while (*(s + 2))
		{
			if (*(s + 2) != 'n')
				return (1);
			s++;
		}
		return (0);
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	n_flag;

	n_flag = 1;
	while (*args && !n_check(*args))
	{
		n_flag = 0;
		args++;
	}
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
	if (n_flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
