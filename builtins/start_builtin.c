/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:02:06 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 14:34:44 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_start(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv + 1));
	else if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv + 1));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argv + 1));
	else if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv + 1));
	else if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv + 1));
	else if (!ft_strcmp(argv[0], "env"))
		return (ft_env(0));
	else if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argv + 1));
	return (-50);
}
