/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:47:08 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:07:45 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	if (ft_strlen(find) == 0)
		return ((char *) str);
	while (str[i] && i < len)
	{
		while (str[i + j] == find[j] && str[i + j] && find[j] && i + j < len)
			j++;
		if (find[j] == '\0')
			return ((char *) &str[i]);
		j = 0;
		i++;
	}
	return (0);
}
