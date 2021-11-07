/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 12:03:24 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/20 20:49:53 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(char *input)
{
	char	*p;
	char	*trimmed;

	trimmed = ft_strtrim(input, " ");
	if (!trimmed)
		fatal_error();
	if (*trimmed == '|')
	{
		free(trimmed);
		return (EXIT_FAILURE);
	}
	p = special_strchr(trimmed, 0, NULL);
	if (*(p - 1) == '|')
	{
		free(trimmed);
		return (EXIT_FAILURE);
	}
	free(trimmed);
	return (EXIT_SUCCESS);
}

int	check_special_chars(char *input)
{
	int		flags;
	char	*last_pipe;

	flags = 0;
	if (check_pipes(input))
		return (PIPE_ERR);
	special_strchr(input, 0, &flags);
	if (flags)
		return (QUOTE_ERR);
	last_pipe = input;
	return (EXIT_SUCCESS);
}

char	*get_input(void)
{
	char	*input;
	int		code;
	int		tmpfd;

	tmpfd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	input = readline(PROMPT);
	dup2(tmpfd, STDOUT_FILENO);
	if (!input)
		exit(EXIT_SUCCESS);
	code = check_special_chars(input);
	if (code < 0)
	{
		g_data.exit_code = 1;
		parse_error(code);
		add_history(input);
		free(input);
		return (NULL);
	}
	return (input);
}
