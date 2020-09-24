/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:54:40 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 10:56:22 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	is_close(t_mlx *mlx, t_point size, t_point begin, t_point p)
{
	mlx->map[begin.y][begin.x] = '3';
	if (begin.y > 0 && mlx->map[begin.y - 1][begin.x] == '0')
	{
		p.y = begin.y - 1;
		p.x = begin.x;
		is_close(mlx, size, p, begin);
	}
	if ((begin.y < (size.y - 1)) && mlx->map[begin.y + 1][begin.x] == '0')
	{
		p.y = begin.y + 1;
		p.x = begin.x;
		is_close(mlx, size, p, begin);
	}
	if ((begin.x < (size.x - 1)) && mlx->map[begin.y][begin.x + 1] == '0')
	{
		p.x = begin.x + 1;
		p.y = begin.y;
		is_close(mlx, size, p, begin);
	}
	if (begin.x > 0 && mlx->map[begin.y][begin.x - 1] == '0')
	{
		p.x = begin.x - 1;
		p.y = begin.y;
		is_close(mlx, size, p, begin);
	}
}

int		check_error_map(t_mlx *mlx)
{
	size_t i;
	size_t j;

	i = -1;
	while (++i < mlx->map_height)
	{
		j = -1;
		while (++j < mlx->map_width)
		{
			if (mlx->map[i][j] < '0' || mlx->map[i][j] > '3')
				return (2);
			if (mlx->map[i][j] == '3' && (i == 0 || i ==
				mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
				return (1);
		}
	}
	return (0);
}

int		check_map(t_mlx *mlx)
{
	t_point	size;
	t_point	begin;
	int		j;
	int		i;

	size.y = mlx->map_height;
	size.x = mlx->map_width;
	begin.x = mlx->player->init_poxy;
	begin.y = mlx->player->init_posx;
	i = -1;
	while (++i < (int)mlx->map_height)
	{
		j = -1;
		while (++j < (int)mlx->map_width)
			if (mlx->map[i][j] == ' ')
				mlx->map[i][j] = '0';
	}
	is_close(mlx, size, begin, begin);
	i = 0;
	return (check_error_map(mlx));
}
