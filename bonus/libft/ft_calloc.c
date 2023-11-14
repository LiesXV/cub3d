/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:59:32 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/02 19:36:56 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;
	size_t	i;

	i = 0;
	if (size > 0 && count > (SIZE_MAX / size))
		return (NULL);
	array = (char *)malloc(count * size);
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = '\0';
		i++;
	}
	return (array);
}
