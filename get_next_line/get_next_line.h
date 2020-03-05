/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:05:20 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/05 16:04:42 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define READ 1
# define OVER 0
# define ERROR -1

# define BOOL int
# define TRUE 1
# define FALSE 0

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

void	*ft_memcpy(void *dst, const void *src, size_t n);

int		get_next_line(int fd, char **line);
int		gnl_strchr(const char *str, int c);

size_t	gnl_strlen(const char *str);

char	*gnl_strdup(char *s1);
char	*stradd(char *s1, char const *s2);

#endif
