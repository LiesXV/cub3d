/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:50:52 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/25 16:27:12 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	character;
	char	*str;

	len = ft_strlen(s);
	character = (char)c;
	str = (char *)s;
	while (len >= 0)
	{
		if (str[len] == character)
			return (((char *)&str[len]));
		len--;
	}
	if (character == 0)
		return ((char *)&str[ft_strlen(str) + 1]);
	return (0);
}
