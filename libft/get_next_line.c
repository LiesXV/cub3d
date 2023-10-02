/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:29:35 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/03/10 11:47:27 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *stach, char *buf)
{
	char	*temp;

	temp = ft_strjoin(stach, buf);
	return (free(stach), temp);
}

char	*read_file(int fd, char *buf, char *stach)
{
	int		bytes_read;

	if (!stach)
		stach = ft_calloc(1, 1);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(buf, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stach), free(buf), NULL);
		buf[bytes_read] = 0;
		stach = ft_free(stach, buf);
	}
	return (free(buf), stach);
}

char	*got_line(char	*stach)
{
	int		i;
	char	*line;

	i = 0;
	if (!stach[i])
		return (NULL);
	while (stach[i] != '\n' && stach[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stach[i] && stach[i] != '\n')
	{
		line[i] = stach[i];
		i++;
	}
	if (stach[i] && stach[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*clean_stach(char	*stach)
{
	int		slen;
	int		npos;
	char	*line;

	npos = 0;
	while (stach[npos] != '\n' && stach[npos])
		npos++;
	if (!stach[npos])
	{
		free(stach);
		return (NULL);
	}
	if (stach[npos] == '\n')
		line = ft_calloc(ft_strlen(stach) - npos, sizeof(char));
	else if (stach[npos] == 0)
	{
		line = ft_calloc(ft_strlen(stach) - npos + 2, sizeof(char));
		npos++;
	}
	npos++;
	slen = 0;
	while (stach[npos])
		line[slen++] = stach[npos++];
	return (free(stach), line);
}

char	*get_next_line(int fd)
{
	static char	*stach = NULL;
	char		buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || read(fd, 0, 0) || BUFFER_SIZE <= 0)
	{
		free(stach);
		stach = NULL;
		return (NULL);
	}
	stach = read_file(fd, buf, stach);
	if (stach == NULL)
		return (NULL);
	line = got_line(stach);
	stach = clean_stach(stach);
	return (line);
}
