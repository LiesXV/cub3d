/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:42:06 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/02 19:35:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	c2;

	if (!s || !c)
		return (NULL);
	i = 0;
	c2 = (char) c;
	while (s[i] && s[i] != c2)
		i++;
	if (s[i] == c2)
		return ((char *) &s[i]);
	return (NULL);
}
