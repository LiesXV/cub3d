/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:07:25 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/12/15 12:07:25 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		if (ft_putchar(str[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putpurcent(void)
{
	return (ft_putchar('%'));
}

int	ft_putnbr(int nb)
{
	int		count;
	char	*str;

	count = 0;
	str = ft_itoa(nb);
	if (str == NULL)
		return (-1);
	count = ft_putstr(str);
	free (str);
	return (count);
}

void	ft_putnb_base(long long unsigned int nbr, long long unsigned int size,
						char *base, int *count)
{
	static int	tmp;

	tmp = 0;
	if (nbr > (size - 1))
		ft_putnb_base((nbr / size), size, base, count);
	if (tmp != -1 && *count != -1)
	{
		tmp = ft_putchar(base[nbr % size]);
		*count = *count + tmp;
	}
	else
		*count = -1;
}

int	ft_printptr(unsigned long long int nbr, unsigned long long int size,
			char *base)
{
	int	result;
	int	tmp;

	tmp = 0;
	result = 0;
	result += ft_putstr("0x");
	if (result == -1)
		return (-1);
	ft_putnb_base(nbr, size, base, &tmp);
	if (tmp == -1)
		return (-1);
	return (result + tmp);
}
