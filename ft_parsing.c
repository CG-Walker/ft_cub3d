/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:11:40 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/22 12:26:19 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	r_id(char *s, t_mlx *mlx)
{
	size_t i;

	i = 1;
	while (s[i] == ' ')
		i++;
	mlx->screen_width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] != ' ')
		i++;
	mlx->screen_height = ft_atoi(&s[i]);
	if (mlx->screen_width > 2560)
		mlx->screen_width = 2560;
	if (mlx->screen_height > 1440)
		mlx->screen_height = 1440;
	printf("W : %d\nH : %d\n", mlx->screen_width, mlx->screen_height);
}

void	nesw_id(char *s, int nesw, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	i = 2;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1)
		exit(-1);
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
	if (nesw == 0)
		mlx->texture->north =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 1)
		mlx->texture->south =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 2)
		mlx->texture->west =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 3)
		mlx->texture->east =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 4)
		mlx->texture->sprite =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	fc_id(char *s, int fc, t_mlx *mlx)
{
	size_t	i;
	int		r;
	int		g;
	int		b;

	i = 1;
	while (s[i] == ' ')
		i++;
	r = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	g = ft_atoi(&s[++i]);
	while (ft_isdigit(s[i]))
		i++;
	b = ft_atoi(&s[++i]);
	if (fc == 0)
		mlx->texture->rgb_floor = r + (g * 256) + (b * 256 * 256);
	else
		mlx->texture->rgb_ceiling = r + (g * 256) + (b * 256 * 256);
}

int		check_id(char *s, t_mlx *mlx)
{
	static size_t i = 0;

	if (s[0] == 'R')
		r_id(s, mlx);
	else if (s[0] == 'N' && s[1] == 'O')
		nesw_id(s, 0, mlx);
	else if (s[0] == 'S' && s[1] == 'O')
		nesw_id(s, 1, mlx);
	else if (s[0] == 'W' && s[1] == 'E')
		nesw_id(s, 2, mlx);
	else if (s[0] == 'E' && s[1] == 'A')
		nesw_id(s, 3, mlx);
	else if (s[0] == 'S' && s[1] != 'O')
		nesw_id(s, 4, mlx);
	else if (s[0] == 'F')
		fc_id(s, 0, mlx);
	else if (s[0] == 'C')
		fc_id(s, 1, mlx);
	else
		return (-1);
	i++;
	if (i == 8)
		return (1);
	else
		return (0);
}

char	**mllc_world_map(char *file, size_t file_size, t_mlx *mlx)
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
		return (-1);
	world_map[mlx->map_height] = NULL;
	fd = open(file, O_RDONLY);
	while (size.x++ < file_size)
		get_next_line(fd, &line);
	size.x = 0;
	while (size.y < mlx->map_height)
	{
		ret = get_next_line(fd, &line);
		if (!(world_map[size.y] = malloc(sizeof(char) * (mlx->map_width + 1))))
			return (-1);
		while (size.x < mlx->map_width)
		{
			if (line[size.x] != 0 && line[size.x] != '\n')
				world_map[size.y][size.x] = line[size.x];
			else
			{
				while (size.x < mlx->map_width)
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

size_t	count_file_size(int fd, size_t file_size)
{
	char	*line;
	int		ret;

	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (*line != '\n' && *line != 0)
		{
			file_size++;
			free(line);
			break ;
		}
		file_size++;
	}
	return (file_size);
}

void	map_parsing(char *file, size_t file_size, int fd, t_mlx *mlx)
{
	char	*line;
	int		ret;
	t_point size;
	size_t	tmp;

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
	printf("RGB Floor  : %d\nRGB Sky  : %d\n", mlx->texture->rgb_floor,
												mlx->texture->rgb_ceiling);
	printf("Map Width  : %d\nMap Height : %d\n", size.x, size.y);
	mlx->map_height = size.y;
	mlx->map_width = size.x;
	mlx->map = mllc_world_map(file, file_size, mlx);
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
}
