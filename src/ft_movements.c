/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:46:26 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/24 12:27:03 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

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
	if (mlx->map[(int)(mlx->player->posx - mlx->player->diry * move_speed)]
	[(int)mlx->player->posy] != '1')
		mlx->player->posx -= mlx->player->diry * move_speed;
	if (mlx->map[(int)(mlx->player->posx)]
	[(int)(mlx->player->posy + mlx->player->dirx * move_speed)] != '1')
		mlx->player->posy += mlx->player->dirx * move_speed;
}

void	mv_right(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posx + mlx->player->diry * move_speed)]
	[(int)mlx->player->posy] != '1')
		mlx->player->posx += mlx->player->diry * move_speed;
	if (mlx->map[(int)(mlx->player->posx)]
	[(int)(mlx->player->posy - mlx->player->dirx * move_speed)] != '1')
		mlx->player->posy -= mlx->player->dirx * move_speed;
}

void	mv_forward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posx + mlx->player->dirx * move_speed)]
	[(int)mlx->player->posy] != '1')
		mlx->player->posx += mlx->player->dirx * move_speed;
	if (mlx->map[(int)(mlx->player->posx)]
	[(int)(mlx->player->posy + mlx->player->diry * move_speed)] != '1')
		mlx->player->posy += mlx->player->diry * move_speed;
}

void	mv_backward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posx - mlx->player->dirx * move_speed)]
	[(int)mlx->player->posy] != '1')
		mlx->player->posx -= mlx->player->dirx * move_speed;
	if (mlx->map[(int)mlx->player->posx]
	[(int)(mlx->player->posy - mlx->player->diry * move_speed)] != '1')
		mlx->player->posy -= mlx->player->diry * move_speed;
}
