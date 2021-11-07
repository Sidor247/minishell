/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:26:09 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/20 20:28:02 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lowercased(char *s)
{
	if (ft_strchr(s, '/'))
		return ;
	while (*s)
	{
		if (*s >= 'A' && *s <= 'Z')
			*s += 'a' - 'A';
		s++;
	}
}

char	*dir_search(char *dir_name, char *command)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*new_path;

	new_path = NULL;
	dir = opendir(dir_name);
	dirent = readdir(dir);
	while (dirent)
	{
		if (!ft_strcmp(dirent->d_name, command))
		{
			append_str(&new_path, dir_name);
			append_str(&new_path, "/");
			append_str(&new_path, command);
			break ;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (new_path);
}

void	find_path(char **command)
{
	char	**paths;
	char	*new_path;
	int		i;

	new_path = NULL;
	if (!ft_getenv("PATH"))
		return ;
	paths = ft_split(ft_getenv("PATH"), ':');
	if (!paths)
		printf("BAD\n");
	i = 0;
	while (paths[i])
	{
		new_path = dir_search(paths[i], *command);
		if (new_path)
		{
			free(*command);
			*command = new_path;
			break ;
		}
		free(paths[i++]);
	}
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
