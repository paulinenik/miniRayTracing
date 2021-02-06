/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 22:21:14 by rgordon           #+#    #+#             */
/*   Updated: 2020/12/06 15:04:40 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*checkstore(char **storage, char **line)
{
	char *endl;
	char *temp;
	char *tline;

	temp = *storage;
	tline = *line;
	endl = NULL;
	if ((endl = ft_strchr(*storage, '\n')))
	{
		*endl = '\0';
		*line = ft_strjoin(*line, *storage);
		*storage = ft_strdup(++endl);
		free(temp);
	}
	else
	{
		*line = ft_strjoin(*line, *storage);
		free(temp);
		*storage = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	}
	free(tline);
	return (endl);
}

static int	checkread(int readlen, char **storage, char **line)
{
	if (readlen == 0 && *storage && *line)
	{
		free(*storage);
		*storage = NULL;
		return (0);
	}
	if (!*line)
		free(*storage);
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	int			readlen;
	static char	*storage;

	if (fd >= 0 && fd < 1024 && BUFFER_SIZE > 0 && line)
	{
		*line = ft_strdup("");
		if (storage && *line)
		{
			if (checkstore(&storage, line))
				return (1);
		}
		else
			storage = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		while ((readlen = read(fd, storage, BUFFER_SIZE)) > 0 && storage
		&& *line)
		{
			storage[readlen] = '\0';
			if (checkstore(&storage, line))
				return (1);
		}
		return (checkread(readlen, &storage, line));
	}
	return (-1);
}
