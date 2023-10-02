/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:42:12 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:08:00 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ssize;
	size_t	dsize;

	if (dstsize == 0 && dst == NULL)
		return (0);
	ssize = ft_strlen(src);
	dsize = ft_strlen(dst);
	if (dstsize <= dsize)
		return (dstsize + ssize);
	else if (dstsize <= dsize + ssize)
	{
		ft_strncat(dst, src, dstsize - dsize - 1);
		return (dsize + ssize);
	}
	else
	{
		ft_strncat(dst, src, ssize);
		return (dsize + ssize);
	}
}
