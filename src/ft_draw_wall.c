/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:01:48 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 11:23:48 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	calc_ray(t_mlx *mlx, t_ray *ray)
{
	ray->camerax = 2 * ray->x / (double)ray->w - 1;
	ray->raydirx = mlx->player->dirX + mlx->player->planeX * ray->camerax;
	ray->raydiry = mlx->player->dirY + mlx->player->planeY * ray->camerax;
	ray->mapx = (int)mlx->player->posX;
	ray->mapy = (int)mlx->player->posY;
	if (ray->raydiry == 0)
		ray->deltadistx = 0;
	else
		ray->deltadistx = ((ray->raydirx == 0) ? 1 : fabs(1 / ray->raydirx));
	if (ray->raydirx == 0)
		ray->deltadisty = 0;
	else
		ray->deltadisty = ((ray->raydiry == 0) ? 1 : fabs(1 / ray->raydiry));
	ray->hit = 0;
}

void	calc_side_dist(t_mlx *mlx, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (mlx->player->posX - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - mlx->player->posX) *
			ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (mlx->player->posY - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - mlx->player->posY) *
			ray->deltadisty;
	}
}

void	check_hit(t_mlx *mlx, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (mlx->map[(int)ray->mapx][(int)ray->mapy] == '1')
			ray->hit = 1;
	}
}

void	print_wall(t_mlx *mlx, t_ray *ray)
{
	ray->y = ray->drawstart;
	while (ray->y++ < ray->drawend)
	{
		ray->texY = (int)ray->texPos & (texHeight - 1);
		ray->texPos += ray->step;
		if (ray->side == 1)
		{
			if (ray->raydiry >= 0)
				ray->color =
					mlx->texture->west[(texHeight * ray->texY) + ray->texX];
			else
				ray->color =
					mlx->texture->east[(texHeight * ray->texY) + ray->texX];
		}
		else
		{
			if (ray->raydirx >= 0)
				ray->color =
					mlx->texture->north[(texHeight * ray->texY) + ray->texX];
			else
				ray->color =
					mlx->texture->south[(texHeight * ray->texY) + ray->texX];
		}
		mlx->data[ray->x - 1 + ray->y * mlx->screen_width] = ray->color;
	}
}
