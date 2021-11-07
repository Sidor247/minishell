/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:47:34 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/20 21:14:20 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_error(char *s)
{
	ft_putstr_fd("mshl: exit: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_exit(char **args)
{
	int	i;

	if (*args && *(args + 1))
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (*args)
	{
		if (!ft_strchr("+-", **args) && !ft_isdigit(**args))
			return (exit_error(*args));
		i = 0;
		while (*(*args + ++i))
			if (!ft_isdigit(*(*args + i)))
				return (exit_error(*args));
		if (i > 8)
			return (exit_error(*args));
		exit(ft_atoi(*args));
	}
	else
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
