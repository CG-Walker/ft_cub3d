/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:56:46 by badrien           #+#    #+#             */
/*   Updated: 2020/09/24 14:03:41 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	init_pos_player(t_mlx *mlx, int x, int y)
{
	mlx->player->posx = (double)x + 0.5;
	mlx->player->posy = (double)y + 0.5;
	mlx->player->init_posx = x;
	mlx->player->init_poxy = y;
	if (mlx->map[x][y] == 'E')
		rot_right(mlx, 1.6);
	if (mlx->map[x][y] == 'S')
		rot_right(mlx, 3.1);
	if (mlx->map[x][y] == 'W')
		rot_right(mlx, 4.7);
	if (mlx->map[x][y] == 'N')
		rot_right(mlx, 6.3);
	mlx->map[x][y] = '0';
}

void	check_player_pos(t_mlx *mlx)
{
	size_t	x;
	size_t	y;
	int		nb_sprite;

	nb_sprite = 0;
	x = -1;
	y = -1;
	while (++x < mlx->map_height)
	{
		while (++y < mlx->map_width)
			if (mlx->map[x][y] == 'N' || mlx->map[x][y] == 'S'
				|| mlx->map[x][y] == 'E' || mlx->map[x][y] == 'W')
				init_pos_player(mlx, x, y);
			else if (mlx->map[x][y] == '2')
			{
				mlx->player->sprite_x = x + 0.5;
				mlx->player->sprite_y = y + 0.5;
				nb_sprite++;
			}
		y = 0;
	}
	if (mlx->player->init_posx == -1 || mlx->player->init_poxy == -1)
		error_exit(mlx, ERROR_PLAYER_NOT_FOUND);
	if (nb_sprite > 1)
		write(1, "WARNING: More than 1 sprite found\n", 35);
}

void	init_data(t_mlx *mlx)
{
	t_player	*player;
	t_texture	*texture;

	mlx->mlx = mlx_init();
	mlx->capture = 0;
	if (!(player = malloc(sizeof(t_player))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	if (!(texture = malloc(sizeof(t_texture))))
		error_exit(mlx, ERROR_MALLOC_FAILED);
	player->dirx = -1;
	player->diry = 0;
	player->planex = 0;
	player->planey = 0.86;
	player->init_posx = -1;
	player->init_poxy = -1;
	texture->rgb_ceiling = 0;
	texture->rgb_floor = 0;
	player->sprite_x = -1;
	player->sprite_y = -1;
	mlx->map = NULL;
	mlx->frame = NULL;
	mlx->zbuffer = NULL;
	mlx->player = player;
	mlx->texture = texture;
	get_texture(mlx);
}

void	get_texture(t_mlx *mlx)
{
	void	*texture;
	int		a;

	texture = mlx_xpm_file_to_image(mlx->mlx, "./pics/wood.xpm", &a, &a);
	mlx->texture->ceiling =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "./pics/greystone.xpm", &a, &a);
	mlx->texture->floor =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}
