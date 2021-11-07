/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 14:13:11 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/18 17:26:11 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (a < b)
		a = b;
	return (ft_strncmp(s1, s2, a));
}

void	none(void *ptr)
{
	return ;
}

void	append_str(char **s1, char *s2)
{
	char	*tmp;

	if (!*s1)
		*s1 = ft_strdup("");
	if (!*s1)
		fatal_error();
	tmp = ft_strjoin(*s1, s2);
	if (!tmp)
		fatal_error();
	free(*s1);
	*s1 = tmp;
}

void	*safe_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		fatal_error();
	return (p);
}

void	free_arr(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}
