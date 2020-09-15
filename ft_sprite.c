/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:14:14 by badrien           #+#    #+#             */
/*   Updated: 2020/09/15 13:51:15 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	size_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->h = mlx->screen_height;
	sprite->w = mlx->screen_width;
	sprite->spriteX = mlx->player->sprite_x - mlx->player->posX;
	sprite->spriteY = mlx->player->sprite_y - mlx->player->posY;
	sprite->invDet = 1.0 / (mlx->player->planeX * mlx->player->dirY -
		mlx->player->dirX * mlx->player->planeY);
	sprite->transformX = sprite->invDet * (mlx->player->dirY * sprite->spriteX
		- mlx->player->dirX * sprite->spriteY);
	sprite->transformY = sprite->invDet * ((-(mlx->player->planeY)) *
		sprite->spriteX + mlx->player->planeX * sprite->spriteY);
	sprite->spriteScreenX = (int)((sprite->w / 2) *
		(1 + sprite->transformX / sprite->transformY));
	sprite->spriteHeight = abs((int)(sprite->h / (sprite->transformY)));
}

void	pre_draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->drawStartY = -(sprite->spriteHeight) / 2 + sprite->h / 2;
	if (sprite->drawStartY < 0)
		sprite->drawStartY = 0;
	sprite->drawEndY = sprite->spriteHeight / 2 + sprite->h / 2;
	if (sprite->drawEndY >= sprite->h)
		sprite->drawEndY = sprite->h - 1;
	sprite->spriteWidth = abs((int)(sprite->h / (sprite->transformY)));
	sprite->drawStartX = -(sprite->spriteWidth) / 2 + sprite->spriteScreenX;
	if (sprite->drawStartX < 0)
		sprite->drawStartX = 0;
	sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawEndX >= sprite->w)
		sprite->drawEndX = sprite->w - 1;
}

void	draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->stripe = sprite->drawStartX;
	while (sprite->stripe++ < sprite->drawEndX)
	{
		sprite->texX = (int)(256 * (sprite->stripe - (-sprite->spriteWidth / 2 +
			sprite->spriteScreenX)) * texWidth / sprite->spriteWidth) / 256;
		if (sprite->transformY > 0 && sprite->stripe > 0 && sprite->stripe
			< sprite->w && sprite->transformY < sprite->zbuffer[sprite->stripe])
		{
			sprite->y = sprite->drawStartY;
			while (sprite->y < sprite->drawEndY)
			{
				sprite->d = (sprite->y) * 256 - sprite->h *
					128 + sprite->spriteHeight * 128;
				sprite->texY = ((sprite->d * texHeight)
					/ sprite->spriteHeight) / 256;
				sprite->color = mlx->texture->sprite[(texWidth * sprite->texY)
					+ sprite->texX];
				if ((sprite->color & 0x00FFFFFF) != 0)
					mlx->data[sprite->stripe +
						(sprite->y * mlx->screen_width)] = sprite->color;
				sprite->y++;
			}
		}
	}
}

void	add_sprite(t_mlx *mlx, double *zbuffer)
{
	t_sprite *sprite;

	sprite = malloc(sizeof(t_sprite));
	size_sprite(mlx, sprite);
	pre_draw_sprite(mlx, sprite);
	sprite->zbuffer = zbuffer;
	draw_sprite(mlx, sprite);
	free(sprite);
}
