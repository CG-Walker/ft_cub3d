/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:14:14 by badrien           #+#    #+#             */
/*   Updated: 2020/09/23 16:09:22 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	size_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->h = mlx->screen_height;
	sprite->w = mlx->screen_width;
	sprite->spritex = mlx->player->sprite_x - mlx->player->posX;
	sprite->spritey = mlx->player->sprite_y - mlx->player->posY;
	sprite->invdet = 1.0 / (mlx->player->planeX * mlx->player->dirY -
		mlx->player->dirX * mlx->player->planeY);
	sprite->transformx = sprite->invdet * (mlx->player->dirY * sprite->spritex
		- mlx->player->dirX * sprite->spritey);
	sprite->transformy = sprite->invdet * ((-(mlx->player->planeY)) *
		sprite->spritex + mlx->player->planeX * sprite->spritey);
	sprite->spritescreenx = (int)((sprite->w / 2) *
		(1 + sprite->transformx / sprite->transformy));
	sprite->spriteheight = abs((int)(sprite->h / (sprite->transformy)));
}

void	pre_draw_sprite(t_sprite *sprite)
{
	sprite->drawstarty = -(sprite->spriteheight) / 2 + sprite->h / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->spriteheight / 2 + sprite->h / 2;
	if (sprite->drawendy >= sprite->h)
		sprite->drawendy = sprite->h - 1;
	sprite->spritewidth = abs((int)(sprite->h / (sprite->transformy)));
	sprite->drawstartx = -(sprite->spritewidth) / 2 + sprite->spritescreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawendx >= sprite->w)
		sprite->drawendx = sprite->w - 1;
}

void	draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->stripe = sprite->drawstartx;
	while (sprite->stripe++ < sprite->drawendx)
	{
		sprite->texx = (int)(256 * (sprite->stripe - (-sprite->spritewidth / 2 +
			sprite->spritescreenx)) * texWidth / sprite->spritewidth) / 256;
		if (sprite->transformy > 0 && sprite->stripe > 0 && sprite->stripe
			< sprite->w && sprite->transformy < sprite->zbuffer[sprite->stripe])
		{
			sprite->y = sprite->drawstarty;
			while (sprite->y < sprite->drawendy)
			{
				sprite->d = (sprite->y) * 256 - sprite->h *
					128 + sprite->spriteheight * 128;
				sprite->texy = ((sprite->d * texHeight)
					/ sprite->spriteheight) / 256;
				sprite->color = mlx->texture->sprite[(texWidth * sprite->texy)
					+ sprite->texx];
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

	if (!(sprite = malloc(sizeof(t_sprite))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	size_sprite(mlx, sprite);
	pre_draw_sprite(sprite);
	sprite->zbuffer = zbuffer;
	draw_sprite(mlx, sprite);
	free(sprite);
}
