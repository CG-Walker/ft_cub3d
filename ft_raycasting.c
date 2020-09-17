/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:12:54 by badrien           #+#    #+#             */
/*   Updated: 2020/09/17 10:17:26 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	floor_and_sky_color(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height / 2)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_ceiling;
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

void	floor_and_sky_text(t_mlx *mlx)
{
	t_floor_sky	*data;
	int x;
	int y;

	data = malloc(sizeof(t_ray));
	y = 0;
	x = 0;

	while(y < mlx->screen_height)
	{
		data->raydirx0 = mlx->player->dirX - mlx->player->planeX;
		data->raydiry0 = mlx->player->dirY - mlx->player->planeY;
		data->raydirx1 = mlx->player->dirX + mlx->player->planeX;
		data->raydiry1 = mlx->player->dirY + mlx->player->planeY;
	
		data->p = y - mlx->screen_height / 2;
		data->posz = 0.5 * mlx->screen_height;
		data->rowdistance = data->posz / data->p;
		data->floorstepx = data->rowdistance * (data->raydirx1 - data->raydirx0) / mlx->screen_width;
		data->floorstepy = data->rowdistance * (data->raydiry1 - data->raydiry0) / mlx->screen_width;
	
		data->floorx = mlx->player->posX + data->rowdistance * data->raydirx0;
		data->floory = mlx->player->posY + data->rowdistance * data->raydiry0;

		x = 0;
		while(++x < mlx->screen_width)
		{
			data->cellx = (int)(data->floorx);
			data->celly = (int)(data->floory);
			
			data->tx = (int)(texWidth * (data->floorx - data->cellx)) & (texWidth - 1);
			data->ty = (int)(texHeight * (data->floory - data->celly)) & (texHeight - 1);

			data->floorx += data->floorstepx;
			data->floory += data->floorstepy;

			data->color = mlx->texture->floor[texWidth * data->ty + data->tx];
			data->color = (data->color >> 1) & 8355711;
			mlx->data[x + (y * mlx->screen_width)] = data->color;        

			data->color = mlx->texture->ceiling[texWidth * data->ty + data->tx];
			data->color = (data->color >> 1) & 8355711;
			mlx->data[x + ((mlx->screen_height - y - 1) * mlx->screen_width)] = data->color;        
		}
	y++;
	}
	free(data);
}

int		raycasting(t_mlx *mlx)
{
	t_ray	*ray;
	double	zbuffer[mlx->screen_width]; // --> transforme into malloc to pass norm

	ray = malloc(sizeof(t_ray));
	ray->x = 0;
	ray->w = mlx->screen_width;
	ray->h = mlx->screen_height;
	if (mlx->texture->rgb_ceiling == 0 && mlx->texture->rgb_floor == 0)
		floor_and_sky_text(mlx);
	else
		floor_and_sky_color(mlx);
	ray->x = 0;

	while (ray->x++ < ray->w)
	{
		ray->camerax = 2 * ray->x / (double)ray->w - 1;
		ray->raydirx = mlx->player->dirX + mlx->player->planeX * ray->camerax;
		ray->raydiry = mlx->player->dirY + mlx->player->planeY * ray->camerax;

		ray->mapx = (int)mlx->player->posX;
		ray->mapy = (int)mlx->player->posY;

		ray->deltadistx = (ray->raydiry == 0) ? 0 : ((ray->raydirx == 0) ? 1 : fabs(1 / ray->raydirx));
		ray->deltadisty = (ray->raydirx == 0) ? 0 : ((ray->raydiry == 0) ? 1 : fabs(1 / ray->raydiry));

		ray->hit = 0;

		if (ray->raydirx < 0)
		{
			ray->stepx = -1;
			ray->sidedistx = (mlx->player->posX - ray->mapx) * ray->deltadistx;
		}
		else
		{
			ray->stepx = 1;
			ray->sidedistx = (ray->mapx + 1.0 - mlx->player->posX) * ray->deltadistx;
		}
		if (ray->raydiry < 0)
		{
			ray->stepy = -1;
			ray->sidedisty = (mlx->player->posY - ray->mapy) * ray->deltadisty;
		}
		else
		{
			ray->stepy = 1;
			ray->sidedisty = (ray->mapy + 1.0 - mlx->player->posY) * ray->deltadisty;
		}

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
		if (ray->side == 0)
			ray->perpwalldist =
				(ray->mapx - mlx->player->posX + (1 - ray->stepx) / 2) / ray->raydirx;
		else
			ray->perpwalldist =
				(ray->mapy - mlx->player->posY + (1 - ray->stepy) / 2) / ray->raydiry;

		ray->h = mlx->screen_height;

		ray->lineheight = (int)(ray->h / ray->perpwalldist);

		ray->drawstart = -ray->lineheight / 2 + ray->h / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + ray->h / 2;
		if (ray->drawend >= ray->h)
			ray->drawend = ray->h - 1;

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
		ray->texPos = (ray->drawstart - ray->h / 2 + ray->lineheight / 2) * ray->step;
		for (ray->y = ray->drawstart; ray->y<ray->drawend; ray->y++)
		{
			ray->texY = (int)ray->texPos & (texHeight - 1);
			ray->texPos += ray->step;
			if (ray->side == 1)
			{
				if (ray->raydiry >= 0)
					ray->color = mlx->texture->west[(texHeight * ray->texY) + ray->texX];
				else
					ray->color = mlx->texture->east[(texHeight * ray->texY) + ray->texX];
			}
			else
			{
				if (ray->raydirx >= 0)
					ray->color = mlx->texture->north[(texHeight * ray->texY) + ray->texX];
				else
					ray->color = mlx->texture->south[(texHeight * ray->texY) + ray->texX];
			}
			mlx->data[ray->x - 1 + ray->y * mlx->screen_width] = ray->color;
		}	
		zbuffer[ray->x] = ray->perpwalldist;
	}
	if (mlx->player->sprite_x != -1)
		add_sprite(mlx, zbuffer);
	add_map(mlx);
	put_frame(mlx);
	free(ray);
	return (0);
}
