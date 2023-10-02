/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:06:56 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/12/15 12:06:56 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(2, &c, 1));
}

int	ft_format(va_list ap, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (format == 'u')
		return (ft_putunsigned(va_arg(ap, unsigned int)));
	else if (format == 'p')
	{
		return (ft_printptr(va_arg(ap, unsigned long long int), 16,
				"0123456789abcdef"));
	}
	else if (format == 'x')
		ft_putnb_base(va_arg(ap, unsigned int), 16, "0123456789abcdef", &count);
	else if (format == 'X')
		ft_putnb_base(va_arg(ap, unsigned int), 16, "0123456789ABCDEF", &count);
	else if (format == '%')
		return (ft_putpurcent());
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	ap;
	int		count;
	int		tmp;

	count = 0;
	tmp = 0;
	va_start (ap, s);
	i = 0;
	while (s[i] && count >= 0)
	{
		if (s[i] == '%')
		{
			tmp = ft_format (ap, s[i + 1]);
			if (tmp == -1)
				return (-1);
			count += tmp;
			i++;
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end (ap);
	return (count);
}
