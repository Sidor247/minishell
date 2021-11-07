/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:47:14 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/21 14:49:04 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_string(char *s)
{
	char	*new;
	char	*name;
	char	*eq;

	eq = special_strchr(s, '=', NULL);
	new = NULL;
	append_str(&new, "declare -x ");
	name = safe_malloc((eq - s + 2) * sizeof(char));
	ft_strlcpy(name, s, eq - s + 1);
	append_str(&new, name);
	free(name);
	append_str(&new, "=\"");
	if (*eq)
		append_str(&new, eq + 1);
	append_str(&new, "\"");
	return (new);
}

int	ft_env(int flag)
{
	t_list	*tmp;
	char	*s;

	tmp = g_data.envp;
	while (tmp)
	{
		if (flag)
		{
			s = export_string(tmp->content);
			ft_putendl_fd(s, STDOUT_FILENO);
			free(s);
		}
		else
			ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
