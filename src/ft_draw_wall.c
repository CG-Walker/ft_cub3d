/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:01:48 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 12:30:04 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	calc_ray(t_mlx *mlx, t_ray *ray)
{
	ray->camerax = 2 * ray->x / (double)ray->w - 1;
	ray->raydirx = mlx->player->dirx + mlx->player->planex * ray->camerax;
	ray->raydiry = mlx->player->diry + mlx->player->planey * ray->camerax;
	ray->mapx = (int)mlx->player->posx;
	ray->mapy = (int)mlx->player->posy;
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
		ray->sidedistx = (mlx->player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - mlx->player->posx) *
			ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (mlx->player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - mlx->player->posy) *
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
		ray->texy = (int)ray->texpos & (TEXHEIGHT - 1);
		ray->texpos += ray->step;
		if (ray->side == 1)
		{
			if (ray->raydiry >= 0)
				ray->color =
					mlx->texture->west[(TEXHEIGHT * ray->texy) + ray->texx];
			else
				ray->color =
					mlx->texture->east[(TEXHEIGHT * ray->texy) + ray->texx];
		}
		else
		{
			if (ray->raydirx >= 0)
				ray->color =
					mlx->texture->north[(TEXHEIGHT * ray->texy) + ray->texx];
			else
				ray->color =
					mlx->texture->south[(TEXHEIGHT * ray->texy) + ray->texx];
		}
		mlx->data[ray->x - 1 + ray->y * mlx->screen_width] = ray->color;
	}
}
