/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:46:26 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/10 11:52:17 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	mv_left(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirY * move_speed)]
	[(int)mlx->player->posY] == 0)
		mlx->player->posX -= mlx->player->dirY * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirX * move_speed)] == 0)
		mlx->player->posY += mlx->player->dirX * move_speed;
}

void	mv_right(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirY * move_speed)]
	[(int)mlx->player->posY] == 0)
		mlx->player->posX += mlx->player->dirY * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY - mlx->player->dirX * move_speed)] == 0)
		mlx->player->posY -= mlx->player->dirX * move_speed;
}

void	mv_forward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX + mlx->player->dirX * move_speed)]
	[(int)mlx->player->posY] == 0)
		mlx->player->posX += mlx->player->dirX * move_speed;
	if (mlx->map[(int)(mlx->player->posX)]
	[(int)(mlx->player->posY + mlx->player->dirY * move_speed)] == 0)
		mlx->player->posY += mlx->player->dirY * move_speed;
}

void	mv_backward(t_mlx *mlx, double move_speed)
{
	if (mlx->map[(int)(mlx->player->posX - mlx->player->dirX * move_speed)]
	[(int)mlx->player->posY] == 0)
		mlx->player->posX -= mlx->player->dirX * move_speed;
	if (mlx->map[(int)mlx->player->posX]
	[(int)(mlx->player->posY - mlx->player->dirY * move_speed)] == 0)
		mlx->player->posY -= mlx->player->dirY * move_speed;
}

void	rot_right(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;
	old_dir_x = mlx->player->dirX;
	mlx->player->dirX = mlx->player->dirX * cos(-rot_speed) - mlx->player->dirY * sin(-rot_speed);
	mlx->player->dirY = old_dir_x * sin(-rot_speed) + mlx->player->dirY * cos(-rot_speed);
	old_plane_x = mlx->player->planeX;
	mlx->player->planeX = mlx->player->planeX * cos(-rot_speed) - mlx->player->planeY * sin(-rot_speed);
	mlx->player->planeY = old_plane_x * sin(-rot_speed) + mlx->player->planeY * cos(-rot_speed);
}

void	rot_left(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirX;
	mlx->player->dirX = mlx->player->dirX * cos(rot_speed) - mlx->player->dirY * sin(rot_speed);
	mlx->player->dirY = old_dir_x * sin(rot_speed) + mlx->player->dirY * cos(rot_speed);
	old_plane_x = mlx->player->planeX;
	mlx->player->planeX = mlx->player->planeX * cos(rot_speed) - mlx->player->planeY * sin(rot_speed);
	mlx->player->planeY = old_plane_x * sin(rot_speed) + mlx->player->planeY * cos(rot_speed);
}

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
	if (key == ESC_KEY)
		exit(0);
	mlx_clear_window(mlx->mlx, mlx->window);
	raycasting(mlx);
	return (1);
}
