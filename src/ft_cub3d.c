/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/24 12:31:26 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	put_frame(t_mlx *mlx)
{
	if (mlx->frame != NULL)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame);
	}
	mlx->frame = mlx_new_image(mlx->mlx, mlx->screen_width, mlx->screen_height);
	mlx->data =
		(int*)mlx_get_data_addr(mlx->frame, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	add_map(t_mlx *mlx)
{
	size_t	y;
	size_t	x;
	int		color;

	x = -1;
	y = -1;
	while (++x < mlx->map_height)
	{
		while (++y < mlx->map_width)
			if (mlx->map[x][y] != '0')
			{
				if (mlx->map[x][y] == '1')
					color = 0x000000;
				if (mlx->map[x][y] == '2')
					color = 0xFF0000;
				if (mlx->map[x][y] == '3')
					color = 0x00CC00;
				mlx->data[(x + (mlx->screen_height / 35) + ((y +
					(mlx->screen_width / 35)) * mlx->screen_width))] = color;
			}
		y = 0;
	}
	y = (int)mlx->player->posx + (mlx->screen_height / 35) +
		((int)mlx->player->posy + (mlx->screen_width / 35)) * mlx->screen_width;
	mlx->data[y] = 0x000000;
}

void	engine(t_mlx *mlx)
{
	put_frame(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_hook(mlx->window, 17, 0, clean_exit, mlx);
	mlx_loop(mlx->mlx);
}

int		main(int argc, char *argv[])
{
	t_mlx *mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	init_data(mlx);
	if (argc == 2 || argc == 3)
		full_parsing(argv[1], mlx, 0);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		mlx->capture = 1;
	if ((argc != 2 && mlx->capture == 0) || (argc == 3 && mlx->capture == 0))
		error_exit(mlx, ERROR_UNEXPECTED_ARGS);
	if (check_map(mlx) != 0)
		error_exit(mlx, ERROR_MAP_INCORRECT);
	mlx->window = mlx_new_window(mlx->mlx,
		mlx->screen_width, mlx->screen_height, "Cub3D");
	put_frame(mlx);
	raycasting(mlx);
	engine(mlx);
	return (0);
}
