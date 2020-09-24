/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_floor_sky.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:59:35 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 11:23:45 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	floor_and_sky_color(t_mlx *mlx)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height / 2)
			mlx->data[x + (y++ * mlx->screen_width)] =
				mlx->texture->rgb_ceiling;
		x++;
		y = 0;
	}
	x = 0;
	y = mlx->screen_height / 2;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_floor;
		x++;
		y = mlx->screen_height / 2;
	}
}

void	get_data(t_mlx *mlx, t_floor_sky *data)
{
	data->raydirx0 = mlx->player->dirX - mlx->player->planeX;
	data->raydiry0 = mlx->player->dirY - mlx->player->planeY;
	data->raydirx1 = mlx->player->dirX + mlx->player->planeX;
	data->raydiry1 = mlx->player->dirY + mlx->player->planeY;
	data->p = data->y - mlx->screen_height / 2;
	data->posz = 0.5 * mlx->screen_height;
	data->rowdistance = data->posz / data->p;
	data->floorstepx = data->rowdistance * (data->raydirx1 - data->raydirx0)
		/ mlx->screen_width;
	data->floorstepy = data->rowdistance * (data->raydiry1 - data->raydiry0)
		/ mlx->screen_width;
	data->floorx = mlx->player->posX + data->rowdistance * data->raydirx0;
	data->floory = mlx->player->posY + data->rowdistance * data->raydiry0;
}

void	draw_data(t_mlx *mlx, t_floor_sky *data, int x)
{
	size_t i;
	size_t j;

	i = texHeight;
	j = texWidth;
	data->cellx = (int)(data->floorx);
	data->celly = (int)(data->floory);
	data->tx = (int)(j * (data->floorx - data->cellx)) & (j - 1);
	data->ty = (int)(i * (data->floory - data->celly)) & (i - 1);
	data->floorx += data->floorstepx;
	data->floory += data->floorstepy;
	data->color = mlx->texture->floor[texWidth * data->ty + data->tx];
	data->color = (data->color >> 1) & 8355711;
	mlx->data[x + (data->y * mlx->screen_width)] = data->color;
	data->color = mlx->texture->ceiling[texWidth * data->ty + data->tx];
	data->color = (data->color >> 1) & 8355711;
	mlx->data[x + ((mlx->screen_height - data->y - 1)
		* mlx->screen_width)] = data->color;
}

void	floor_and_sky_text(t_mlx *mlx)
{
	t_floor_sky	*data;
	size_t		x;

	if (!(data = malloc(sizeof(t_ray))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	data->y = 0;
	x = 0;
	while (data->y < (int)mlx->screen_height)
	{
		get_data(mlx, data);
		x = 0;
		while (++x < mlx->screen_width)
			draw_data(mlx, data, x);
		data->y++;
	}
	free(data);
}
