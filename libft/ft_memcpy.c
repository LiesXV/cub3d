/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:12:28 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:08:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*dstcpy;
	unsigned char	*srccpy;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		dstcpy[i] = srccpy[i];
		i++;
	}
	return (dst);
}
