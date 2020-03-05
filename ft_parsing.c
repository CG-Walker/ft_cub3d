/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:11:40 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/05 17:57:04 by cgoncalv         ###   ########.fr       */
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

	a = 64;
	i = 2;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1)
	{
		printf("ERROR LOADING TEXTURE.\n");
		exit(-1);
	}
	printf("%s loaded.\n", &s[i]);
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
	if (s[0] == 'R')
		r_id(s, mlx);
	if (s[0] == 'N' && s[1] == 'O')
		nesw_id(s, 0, mlx);
	if (s[0] == 'S' && s[1] == 'O')
		nesw_id(s, 1, mlx);
	if (s[0] == 'W' && s[1] == 'E')
		nesw_id(s, 2, mlx);
	if (s[0] == 'E' && s[1] == 'A')
		nesw_id(s, 3, mlx);
	if (s[0] == 'F')
		fc_id(s, 0, mlx);
	if (s[0] == 'C')
		fc_id(s, 1, mlx);
	/*
	if (s[0] == 'S')
		s_id(s, mlx);
	*/
	else
		return (-1);
	return (0);
}

void	parsing(char *file, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		ret;
	size_t	width;
	size_t	height;
	size_t	tmp;

	ret = 1;
	width = 0;
	height = 0;
	fd = open(file, O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line[0] != '\n')
			check_id(line, mlx);
		free(line);
	}
	printf("floor : %i\nsky : %d\n", mlx->texture->rgb_floor, mlx->texture->rgb_ceiling);
	/*
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strlen(line);
		if (width < tmp)
			width = tmp;
		height++;
		free(line);
	}
	*/
}
