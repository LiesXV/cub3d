/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:26:08 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:08:32 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstcpy;
	unsigned char	*srccpy;
	size_t			k;

	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	k = len;
	if (dstcpy <= srccpy)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (k > 0)
		{
			dstcpy[k - 1] = srccpy[k - 1];
			k--;
		}
	}
	return (dst);
}
