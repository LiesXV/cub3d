/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:38:49 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/20 14:28:17 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstlast(t_list *lst)
// {
// 	while (lst)
// 	{
// 		if (!lst->next)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

t_list	*ft_lstmlast(t_list *lst)
{
	while (lst->next)
	{
		if (!lst->next->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
