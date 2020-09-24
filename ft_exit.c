/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:04:35 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 11:05:11 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	error_exit(t_mlx *mlx, int error_id)
{
	write(1, "<Error>\n", 9);
	if (error_id == ERROR_MALLOC_FAILED)
		write(1, "Malloc failed.\n", 16);
	else if (error_id == ERROR_MAP_NOT_FOUND)
		write(1, "Map not found.\n", 16);
	else if (error_id == ERROR_PLAYER_NOT_FOUND)
		write(1, "Player not found.\n", 19);
	else if (error_id == ERROR_MAP_INCORRECT)
		write(1, "Map incorrect.\n", 16);
	else if (error_id == ERROR_TEXTURE_NOT_LOADED)
		write(1, "Texture can't be loaded.\n", 26);
	else if (error_id == ERROR_CAPTURE_FAILED)
		write(1, "Capture failed.\n", 17);
	else if (error_id == ERROR_UNEXPECTED_ARGS)
		write(1, "Unexpected number of arg(s) or invalide arg(s).\n", 49);
	else if (error_id == ERROR_SCREEN_SIZE)
		write(1, "Screen size incorrect.\n", 24);
	else if (error_id == ERROR_RGB)
		write(1, "RGB color incorrect.\n", 22);
	clean_exit(mlx);
}

int		clean_exit(t_mlx *mlx)
{
	size_t x;

	x = 0;
	if (mlx->map != NULL)
		while (mlx->map[x] != NULL)
			free(mlx->map[x++]);
	if (mlx->map != NULL)
		free(mlx->map);
	if (mlx != NULL)
	{
		if (mlx->frame != NULL)
			mlx_destroy_image(mlx->mlx, mlx->frame);
		free(mlx->player);
		free(mlx->texture);
		free(mlx->mlx);
		free(mlx);
	}
	exit(0);
}
