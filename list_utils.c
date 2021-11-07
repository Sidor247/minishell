/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwhis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:38:38 by cwhis             #+#    #+#             */
/*   Updated: 2021/09/14 19:11:53 by cwhis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*array_to_list(void **arr)
{
	t_list	*list;

	while (*arr)
	{
		safe_lstadd_back(&list, *arr);
		arr++;
	}
	return (list);
}

void	**list_to_array(t_list *list, int *arr_size)
{
	t_list	*tmp;
	void	**arr;
	int		size;
	int		i;

	size = ft_lstsize(list);
	arr = safe_malloc((size + 1) * sizeof(void *));
	tmp = list;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	arr[size] = NULL;
	if (arr_size)
		*arr_size = size;
	return (arr);
}

void	print_list(void *content)
{	
	ft_putendl_fd(content, STDOUT_FILENO);
}

void	safe_lstadd_back(t_list **lst, void *content)
{
	t_list	*tmp;

	tmp = ft_lstnew(content);
	if (!tmp)
		fatal_error();
	ft_lstadd_back(lst, tmp);
}

void	lst_remove(t_list **node, t_list *element)
{
	t_list	*tmp;

	if (*node == element)
	{
		*node = element->next;
		ft_lstdelone(element, &free);
		return ;
	}
	tmp = *node;
	while (tmp->next)
	{
		if (tmp->next == element)
		{
			tmp->next = element->next;
			ft_lstdelone(element, &free);
			return ;
		}
		tmp = tmp->next;
	}
}
