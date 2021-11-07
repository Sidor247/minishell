/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:11:40 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 13:46:21 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir)
	{
		ft_putendl_fd(dir, STDOUT_FILENO);
		free(dir);
	}
	else
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	g_data.exit_code = 0;
	return (EXIT_SUCCESS);
}
