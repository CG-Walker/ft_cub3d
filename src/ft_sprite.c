/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:14:14 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 13:55:02 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	size_sprite(t_mlx *mlx, t_sprite *sprite)
{
	sprite->h = mlx->screen_height;
	sprite->w = mlx->screen_width;
	sprite->spritex = mlx->player->sprite_x - mlx->player->posx;
	sprite->spritey = mlx->player->sprite_y - mlx->player->posy;
	sprite->invdet = 1.0 / (mlx->player->planex * mlx->player->diry -
		mlx->player->dirx * mlx->player->planey);
	sprite->transformx = sprite->invdet * (mlx->player->diry * sprite->spritex
		- mlx->player->dirx * sprite->spritey);
	sprite->transformy = sprite->invdet * ((-(mlx->player->planey)) *
		sprite->spritex + mlx->player->planex * sprite->spritey);
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
	while (sprite->stripe < sprite->drawendx)
	{
		sprite->texx = (int)(256 * (sprite->stripe - (-sprite->spritewidth / 2 +
			sprite->spritescreenx)) * TEXWIDTH / sprite->spritewidth) / 256;
		if (sprite->transformy > 0 && sprite->stripe > 0 && sprite->stripe
			< sprite->w && sprite->transformy < sprite->zbuffer[sprite->stripe])
		{
			sprite->y = sprite->drawstarty;
			while (sprite->y < sprite->drawendy)
			{
				sprite->d = (sprite->y) * 256 - sprite->h *
					128 + sprite->spriteheight * 128;
				sprite->texy = ((sprite->d * TEXHEIGHT)
					/ sprite->spriteheight) / 256;
				sprite->color = mlx->texture->sprite[(TEXWIDTH * sprite->texy)
					+ sprite->texx];
				if ((sprite->color & 0x00FFFFFF) != 0)
					mlx->data[sprite->stripe +
						(sprite->y * mlx->screen_width)] = sprite->color;
				sprite->y++;
			}
		}
		sprite->stripe++;
	}
}

void	add_sprite(t_mlx *mlx)
{
	t_sprite *sprite;

	if (!(sprite = malloc(sizeof(t_sprite))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	size_sprite(mlx, sprite);
	pre_draw_sprite(sprite);
	sprite->zbuffer = mlx->zbuffer;
	draw_sprite(mlx, sprite);
	free(sprite);
}
