/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:07:16 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/12/15 12:07:16 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (n > 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_putunsigned(unsigned int n)
{
	int		count;
	char	*num;

	count = 0;
	if (n == 0)
		return (ft_putchar('0'));
	else
	{
		num = ft_uitoa(n);
		if (!num)
			count = -1;
		else
			count = ft_putstr(num);
		free(num);
	}
	return (count);
}
