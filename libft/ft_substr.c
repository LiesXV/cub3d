/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:07:38 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	k;

	if (s == NULL)
		return (NULL);
	if (len > (size_t)ft_strlen(s))
		len = ft_strlen(s);
	i = 0;
	k = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] && i < len + start)
	{
		if (i >= (size_t) start)
		{
			str[k] = s[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}
