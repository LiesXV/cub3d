/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:45:34 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/08/06 00:46:03 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_command(char *str, int i)
{
	i++;
	while (str[i] != 39 && str[i])
		i++;
	return (i + 1);
}

static int	word_len(char const *s, char c, int start)
{
	int	j;

	j = 0;
	if (s[start] == 39)
	{
		j += 2;
		while (s[start] && s[start + 1] != 39)
		{
			j++;
			start++;
		}
	}
	else
	{
		while (s[start] && s[start] != c)
		{
			j++;
			start++;
		}
	}
	if (j > 0)
		return (j);
	else
		return (0);
}

int	nbwords(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == 39 && s[i] != c)
		{
			i = split_command(s, i);
			j++;
		}
		else if (s[i - 1] != c && s[i] == c)
		{
			j++;
			i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c && s[i - 1] != 39)
		j++;
	return (j);
}

char	**ft_split_pipex(char *str, char limiter)
{
	int		i;
	int		count;
	char	**result;

	count = 0;
	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	result = malloc(sizeof(char *) * (nbwords(str, limiter) + 1));
	if (!result)
		return (NULL);
	while (i < nbwords(str, limiter))
	{
		while (str[count] == limiter)
			count++;
		result[i] = ft_substr_pipex(str, count, word_len(str, limiter, count));
		if (!(result[i]))
			return (free_split(result), NULL);
		count += word_len(str, limiter, count);
		i++;
	}
	result[i] = NULL;
	return (result);
}
