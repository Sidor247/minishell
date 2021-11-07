/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:39:25 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/20 22:06:14 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(int code)
{
	if (code == QUOTE_ERR)
		ft_putendl_fd("error: unclosed qoutes", STDERR_FILENO);
	else if (code == PIPE_ERR)
		ft_putendl_fd("error: bad pipes", STDERR_FILENO);
	else if (code == FILE_ERR)
		ft_putendl_fd("error: missing file name", STDERR_FILENO);
	else if (code == FILE_ERR)
		ft_putendl_fd("error: incorrect redirection", STDERR_FILENO);
	else if (code == SYNTAX_ERR)
		ft_putendl_fd("mshl: syntax error: unexpected end of file",
			STDERR_FILENO);
	else if (code == RED_ERR)
		ft_putendl_fd("mshl: syntax error near unexpected token",
			STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	fatal_error(void)
{
	perror("fatal error: ");
	exit(EXIT_FAILURE);
}
