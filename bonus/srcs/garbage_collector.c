/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:02:59 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/02 17:35:21 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	add_address(t_collector **lst, void *address)
{
	t_collector	*newlst;
	t_collector	*tmp;

	newlst = malloc(sizeof(t_collector));
	if (!newlst)
		return (1);
	newlst->address = address;
	newlst->next = NULL;
	if (*lst == NULL)
		*lst = newlst;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newlst;
	}
	return (0);
}

void	free_gb(t_collector **lst)
{
	t_collector	*cur;
	t_collector	*tmp;

	cur = *lst;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->address)
			free(tmp->address);
		if (tmp)
			free(tmp);
	}
	*lst = NULL;
}

int	add_tab_to_gb(t_collector **lst, char **args)
{
	int	k;

	if (add_address(lst, args) == 1)
		return (1);
	k = 0;
	while (args[k] != NULL)
	{
		if (add_address(lst, args[k]) == 1)
			return (1);
		k++;
	}
	return (0);
}
