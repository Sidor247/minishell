/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:08:51 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 13:47:24 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	old_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(dir, STDOUT_FILENO);
	ft_setenv("OLDPWD", dir);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args)
{
	char	*dir;
	int		ret;

	if (*args && !ft_strcmp(*args, "-"))
		return (old_pwd());
	if (!*args)
		dir = ft_getenv("HOME");
	else
		dir = *args;
	if (!dir)
	{
		ft_putendl_fd("cd: can't find HOME variable", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = chdir(dir);
	if (ret)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	ft_setenv("PWD", dir);
	return (EXIT_SUCCESS);
}
