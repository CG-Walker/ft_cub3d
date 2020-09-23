/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:11:40 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/23 16:08:26 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

size_t	count_file_size(int fd, size_t file_size)
{
	char	*line;
	int		ret;

	ret = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (*line != '\n' && *line != 0)
		{
			file_size++;
			free(line);
			break ;
		}
		free(line);
		file_size++;
	}
	return (file_size);
}

char	**make_world_map(char *file, size_t file_size, t_mlx *mlx)
{
	char	**world_map;
	char	*line;
	int		ret;
	int		fd;
	t_point size;

	size.x = 0;
	size.y = 0;
	ret = 1;
	if (!(world_map = malloc(sizeof(char*) * (mlx->map_height + 1))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	world_map[mlx->map_height] = NULL;
	fd = open(file, O_RDONLY);
	while (size.x++ < (int)file_size)
	{
		get_next_line(fd, &line);
		free(line);
	}
	size.x = 0;
	world_map = fill_world_map(mlx, world_map, fd, size);
	close(fd);
	return (world_map);
}

char	**fill_world_map(t_mlx *mlx, char **world_map, int fd, t_point size)
{
	int		ret;
	char	*line;

	while (size.y < (int)mlx->map_height)
	{
		ret = get_next_line(fd, &line);
		if (!(world_map[size.y] = malloc(sizeof(char) * (mlx->map_width + 1))))
			error_exit(mlx, ERROR_MALLOC_FAILED);
		while (size.x < (int)mlx->map_width)
		{
			if (line[size.x] != 0 && line[size.x] != '\n')
				world_map[size.y][size.x] = line[size.x];
			else
			{
				while (size.x < (int)mlx->map_width)
					world_map[size.y][size.x++] = ' ';
				break ;
			}
			size.x++;
		}
		world_map[size.y++][mlx->map_width] = 0;
		size.x = 0;
		free(line);
	}
	return (world_map);
}

void	map_parsing(char *file, size_t file_size, int fd, t_mlx *mlx)
{
	char	*line;
	int		ret;
	t_point size;
	int		tmp;

	ret = 1;
	size.x = 0;
	size.y = 1;
	file_size = count_file_size(fd, file_size);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strlen(line);
		if (size.x < tmp)
			size.x = tmp;
		size.y++;
		free(line);
	}
	close(fd);
	mlx->map_height = size.y;
	mlx->map_width = size.x;
	mlx->map = make_world_map(file, file_size, mlx);
}

void	full_parsing(char *file, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		ret;
	size_t	i;

	ret = 1;
	i = 0;
	fd = open(file, O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line[0] != '\n')
		{
			if (check_id(line, mlx) == 1)
			{
				i++;
				break ;
			}
		}
		i++;
	}
	ret = get_next_line(fd, &line);
	if (line[0] != '\n')
		map_parsing(file, i, fd, mlx);
	check_player_pos(mlx);
}
