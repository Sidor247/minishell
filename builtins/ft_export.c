/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:58:49 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 14:35:06 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_check1(char *s)
{
	if (ft_isdigit(*s))
		return (EXIT_FAILURE);
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (EXIT_FAILURE);
		s++;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(char **args)
{
	char	*new;

	if (!*args)
		return (ft_env(1));
	while (*args)
	{
		if (!arg_check1(*args))
		{
			new = ft_strdup(*args);
			if (!new)
				fatal_error();
			safe_lstadd_back(&g_data.envp, new);
		}
		else
		{
			ft_putendl_fd("export: invalid variable name", STDERR_FILENO);
			g_data.exit_code = 1;
			return (EXIT_FAILURE);
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
