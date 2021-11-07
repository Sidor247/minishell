/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:14:44 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 13:46:09 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_check2(char *s)
{
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (EXIT_FAILURE);
		s++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(char **args)
{
	if (!*args)
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (*args)
	{
		if (!arg_check2(*args))
			ft_unsetenv(*args);
		else
		{
			ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
