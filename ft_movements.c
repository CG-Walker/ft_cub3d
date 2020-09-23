/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:46:26 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/23 15:23:10 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		move(int key, t_mlx *mlx)
{
	double move_speed;
	double rot_speed;

	move_speed = 0.3;
	rot_speed = 0.1;
	if (key == A_KEY)
		mv_left(mlx, move_speed);
	if (key == D_KEY)
		mv_right(mlx, move_speed);
	if (key == W_KEY)
		mv_forward(mlx, move_speed);
	if (key == S_KEY)
		mv_backward(mlx, move_speed);
	if (key == RIGHT_KEY)
		rot_right(mlx, rot_speed);
	if (key == LEFT_KEY)
		rot_left(mlx, rot_speed);
	if (key == ESC_KEY || key == DESTROYNOTIFY)
		clean_exit(mlx);
	mlx_clear_window(mlx->mlx, mlx->window);
	raycasting(mlx);
	return (TRUE);
}

void	mv_left(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirY * move_speed)]
	[(int)mlx->player->posY] != '1')
		mlx->player->posX -= mlx->player->dirY * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirX * move_speed)] != '1')
		mlx->player->posY += mlx->player->dirX * move_speed;
}

void	mv_right(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirY * move_speed)]
	[(int)mlx->player->posY] != '1')
		mlx->player->posX += mlx->player->dirY * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY - mlx->player->dirX * move_speed)] != '1')
		mlx->player->posY -= mlx->player->dirX * move_speed;
}

void	mv_forward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirX * move_speed)]
	[(int)mlx->player->posY] != '1')
		mlx->player->posX += mlx->player->dirX * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirY * move_speed)] != '1')
		mlx->player->posY += mlx->player->dirY * move_speed;
}

void	mv_backward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirX * move_speed)]
	[(int)mlx->player->posY] != '1')
		mlx->player->posX -= mlx->player->dirX * move_speed;
	if (mlx->map[(int)mlx->player->posX]
	[(int)(mlx->player->posY - mlx->player->dirY * move_speed)] != '1')
		mlx->player->posY -= mlx->player->dirY * move_speed;
}
