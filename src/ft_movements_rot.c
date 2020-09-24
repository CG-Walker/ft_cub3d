/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements_rot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:33:54 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/24 12:34:09 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	rot_right(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirx;
	mlx->player->dirx =
		mlx->player->dirx * cos(-rot_speed)
			- mlx->player->diry * sin(-rot_speed);
	mlx->player->diry =
		old_dir_x * sin(-rot_speed) + mlx->player->diry * cos(-rot_speed);
	old_plane_x = mlx->player->planex;
	mlx->player->planex =
		mlx->player->planex * cos(-rot_speed)
			- mlx->player->planey * sin(-rot_speed);
	mlx->player->planey =
		old_plane_x * sin(-rot_speed) + mlx->player->planey * cos(-rot_speed);
}

void	rot_left(t_mlx *mlx, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player->dirx;
	mlx->player->dirx =
		mlx->player->dirx * cos(rot_speed) - mlx->player->diry * sin(rot_speed);
	mlx->player->diry =
		old_dir_x * sin(rot_speed) + mlx->player->diry * cos(rot_speed);
	old_plane_x = mlx->player->planex;
	mlx->player->planex =
		mlx->player->planex * cos(rot_speed)
			- mlx->player->planey * sin(rot_speed);
	mlx->player->planey =
		old_plane_x * sin(rot_speed) + mlx->player->planey * cos(rot_speed);
}
