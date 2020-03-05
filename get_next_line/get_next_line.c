/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:04:50 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/05 16:09:23 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_rest(char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s++)
		if (*s == '\n')
			i++;
	return (i);
}

char	*strcut(char *s, size_t size)
{
	char *copy;

	copy = gnl_strdup(s);
	free(s);
	if (!(s = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memcpy(s, copy, size + 1);
	s[size] = '\0';
	free(copy);
	return (s);
}

int		mod_rest(int fd, char **rest, char **line)
{
	char	*rest_cpy;

	if (rest[fd] != NULL && (rest[fd][0] == '\n' || check_rest(rest[fd]) > 0))
	{
		rest_cpy = gnl_strdup(rest[fd]);
		(rest[fd][0] == '\n') ? (rest[fd] = strcut(rest[fd], 0))
		: (rest[fd] = strcut(rest[fd], gnl_strchr(rest[fd], '\n')));
		*line = stradd(*line, rest[fd]);
		free(rest[fd]);
		rest[fd] = gnl_strdup(&rest_cpy[gnl_strchr(rest_cpy, '\n') + 1]);
		free(rest_cpy);
		return (READ);
	}
	else
	{
		*line = stradd(*line, rest[fd]);
		free(rest[fd]);
		rest[fd] = NULL;
		return (0);
	}
}

int		last_line(char **line)
{
	if (!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*rest[OPEN_MAX];
	int				ret;

	if (fd < 0 || fd > OPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	*line = NULL;
	if (mod_rest(fd, rest, line) == 1)
		return (READ);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		*line = stradd(*line, buff);
		if (gnl_strchr(buff, '\n') != -1)
		{
			rest[fd] = gnl_strdup(&buff[gnl_strchr(buff, '\n') + 1]);
			*line = strcut(*line, gnl_strchr(*line, '\n'));
			return (READ);
		}
	}
	if (gnl_strlen(*line) == 0 && ret == 0)
		return (last_line(line));
	return (ret);
}
