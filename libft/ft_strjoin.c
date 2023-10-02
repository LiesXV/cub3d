/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:17:33 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/30 01:39:13 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char const *s2)
{
	char		*str;
	size_t		size;
	size_t		i;
	size_t		k;

	if (s1 == NULL)
		return (NULL);
	k = 0;
	i = -1;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	while (++i < size && s1[i])
		str[i] = s1[i];
	while (i < size && s2[k])
	{
		str[i] = s2[k];
		k++;
		i++;
	}
	str[i] = '\0';
	return (free(s1), str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		size;
	size_t		i;
	size_t		k;

	if (s1 == NULL)
		return (NULL);
	k = 0;
	i = -1;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	while (++i < size && s1[i])
		str[i] = s1[i];
	while (i < size && s2[k])
	{
		str[i] = s2[k];
		k++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
