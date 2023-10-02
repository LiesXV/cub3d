/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:44:33 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/09/27 13:11:59 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbwords(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
			i++;
		else if (s[i - 1] != c && s[i] == c)
		{
			j++;
			i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		j++;
	return (j);
}

static int	word_len(char const *s, char c, int start)
{
	int	j;

	j = 0;
	while (s[start] == c)
		start++;
	while (s[start] && s[start] != c)
	{
		j++;
		start++;
	}
	if (j > 0)
		return (j);
	else
		return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**if_error(char const *s)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	else if (s[0] == '\0')
	{
		result = (char **)malloc (sizeof (char *) * 1);
		if (!result)
			return (NULL);
		result[0] = NULL;
		return (result);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;
	int		count;

	if (!s || s[0] == '\0')
		return (if_error(s));
	count = 0;
	i = 0;
	result = malloc (sizeof(char *) * (nbwords(s, c) + 1));
	if (!result)
		return (NULL);
	while (i < nbwords(s, c))
	{
		while (s[count] == c)
			count++;
		result[i] = ft_substr(s, count, word_len(s, c, count));
		if (!(result[i]))
			return (free_split(result), NULL);
		count += word_len(s, c, count);
		i++;
	}
	result[i] = NULL;
	return (result);
}
