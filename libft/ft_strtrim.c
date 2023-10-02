/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:51:47 by ibenhaim          #+#    #+#             */
/*   Updated: 2022/11/23 13:07:40 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_first_pos(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (ft_get_set(str[i], set))
		i++;
	return (i);
}

int	ft_last_pos(const char *str, const char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (ft_get_set(str[i], set))
		i--;
	return (i);
}

char	*ft_isnegative(int len, int start, char *trim, const char *s1)
{
	int	i;

	i = 0;
	while (i < len)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[len] = '\0';
	return (trim);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	int		len;
	int		start;

	if (s1 == NULL)
		return (NULL);
	else if (s1[0] == '\0')
		return (ft_strdup("\0"));
	len = ft_last_pos(s1, set) - ft_first_pos(s1, set) + 1;
	if (len <= 0)
	{
		trim = (char *)malloc(sizeof(char) * 1 + 1);
		if (trim == NULL)
			return (NULL);
		trim[0] = '\0';
		return (trim);
	}
	start = ft_first_pos(s1, set);
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (trim == NULL)
		return (NULL);
	ft_isnegative(len, start, trim, s1);
	return (trim);
}
