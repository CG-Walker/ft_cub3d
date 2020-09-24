/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements_rot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:33:54 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/24 11:24:06 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	rot_right(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirX;
	mlx->player->dirX =
		mlx->player->dirX * cos(-rot_speed)
			- mlx->player->dirY * sin(-rot_speed);
	mlx->player->dirY =
		old_dir_x * sin(-rot_speed) + mlx->player->dirY * cos(-rot_speed);
	old_plane_x = mlx->player->planeX;
	mlx->player->planeX =
		mlx->player->planeX * cos(-rot_speed)
			- mlx->player->planeY * sin(-rot_speed);
	mlx->player->planeY =
		old_plane_x * sin(-rot_speed) + mlx->player->planeY * cos(-rot_speed);
}

void	rot_left(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirX;
	mlx->player->dirX =
		mlx->player->dirX * cos(rot_speed) - mlx->player->dirY * sin(rot_speed);
	mlx->player->dirY =
		old_dir_x * sin(rot_speed) + mlx->player->dirY * cos(rot_speed);
	old_plane_x = mlx->player->planeX;
	mlx->player->planeX =
		mlx->player->planeX * cos(rot_speed)
			- mlx->player->planeY * sin(rot_speed);
	mlx->player->planeY =
		old_plane_x * sin(rot_speed) + mlx->player->planeY * cos(rot_speed);
}
