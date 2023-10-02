/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:45:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/03/31 12:48:17 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*node;
	t_list	*next_node;

	if (lst == NULL)
		return ;
	node = *lst;
	while (node)
	{
		next_node = node->next;
		if (node->cmd)
			free_split(node->cmd);
		if (node->path)
			free(node->path);
		free(node);
		node = next_node;
	}
	*lst = NULL;
	return ;
}
