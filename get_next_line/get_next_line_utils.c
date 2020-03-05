/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:05:11 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/05 16:09:08 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (s == NULL)
		return (0);
	while (*s++)
		len++;
	return (len);
}

char	*gnl_strdup(char *s1)
{
	char	*copy;
	size_t	i;
	size_t	size_s1;

	i = -1;
	size_s1 = gnl_strlen(s1);
	if (size_s1 == 0)
		return (NULL);
	if (!(copy = malloc(sizeof(char) * (size_s1 + 1))))
		return (NULL);
	while (++i < size_s1)
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dst);
}

char	*stradd(char *s1, char const *s2)
{
	char	*ret;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = gnl_strlen(s1);
	size_s2 = gnl_strlen(s2);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!(ret = malloc((sizeof(char) * (size_s1 + size_s2) + 1))))
		return (NULL);
	if (s1 != NULL)
	{
		ft_memcpy(ret, s1, size_s1);
		ft_memcpy(&ret[size_s1], s2, size_s2 + 1);
		free(s1);
	}
	else
		ft_memcpy(ret, s2, size_s2 + 1);
	return (ret);
}

int		gnl_strchr(const char *s, int c)
{
	size_t i;
	size_t size_s;

	i = 0;
	size_s = gnl_strlen(s);
	while (i < size_s)
	{
		if (c == s[i])
			return (i);
		i++;
	}
	if (c == s[i])
		return (i);
	return (-1);
}
