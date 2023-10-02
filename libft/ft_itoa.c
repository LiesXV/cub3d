/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:52:03 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:08:39 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	long	div;
	int		count;

	count = 0;
	div = 1;
	if (n <= 0)
	{
		n = n * -1;
		count++;
	}
	while (n / div > 0)
	{
		div = div * 10;
		count++;
	}
	return (count);
}

static	void	ft_reverse(char *s)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i <= j)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	result = (char *)malloc (sizeof(char) * ft_count(n) + 1);
	if (result == NULL)
		return (NULL);
	sign = n;
	if (sign < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		result[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		result[i++] = '-';
	result[i] = '\0';
	ft_reverse(result);
	return (result);
}
