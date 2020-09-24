/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:12:54 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 11:24:22 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	calc_draw_size(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist =
			(ray->mapx - mlx->player->posX +
				(1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist =
			(ray->mapy - mlx->player->posY +
				(1 - ray->stepy) / 2) / ray->raydiry;
	ray->h = mlx->screen_height;
	ray->lineheight = (int)(ray->h / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + ray->h / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + ray->h / 2;
	if (ray->drawend >= ray->h)
		ray->drawend = ray->h - 1;
}

void	calc_tex_size(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		ray->wallX = mlx->player->posY + ray->perpwalldist * ray->raydiry;
	else
		ray->wallX = mlx->player->posX + ray->perpwalldist * ray->raydirx;
	ray->wallX -= floor((ray->wallX));
	ray->texX = (int)(ray->wallX * (double)texWidth);
	if (ray->side == 0 && ray->raydirx > 0)
		ray->texX = texWidth - ray->texX - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		ray->texX = texWidth - ray->texX - 1;
	ray->step = 1.0 * texHeight / ray->lineheight;
	ray->texPos = (ray->drawstart - ray->h /
		2 + ray->lineheight / 2) * ray->step;
}

void	draw_wall(t_mlx *mlx, t_ray *ray, double *zbuffer)
{
	ray->x = 0;
	ray->w = mlx->screen_width;
	ray->h = mlx->screen_height;
	while (ray->x++ < ray->w)
	{
		calc_ray(mlx, ray);
		calc_side_dist(mlx, ray);
		check_hit(mlx, ray);
		calc_draw_size(mlx, ray);
		calc_tex_size(mlx, ray);
		print_wall(mlx, ray);
		zbuffer[ray->x] = ray->perpwalldist;
	}
}

int		raycasting(t_mlx *mlx)
{
	t_ray	*ray;
	double	zbuffer[mlx->screen_width];

	if (!(ray = malloc(sizeof(t_ray))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	if (mlx->texture->rgb_ceiling == 0 && mlx->texture->rgb_floor == 0)
		floor_and_sky_text(mlx);
	else
		floor_and_sky_color(mlx);
	draw_wall(mlx, ray, zbuffer);
	if (mlx->player->sprite_x != -1)
		add_sprite(mlx, zbuffer);
	if (mlx->screen_height > mlx->map_height &&
		mlx->screen_width > mlx->map_width)
		add_map(mlx);
	if (mlx->capture == 1)
		capture(mlx);
	put_frame(mlx);
	free(ray);
	return (0);
}
