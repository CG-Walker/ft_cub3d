/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/23 12:21:23 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
	int y;
	int x;
	int color;

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
	y = (int)mlx->player->posX + (mlx->screen_height / 35) +
		((int)mlx->player->posY + (mlx->screen_width / 35)) * mlx->screen_width;
	mlx->data[y] = 0x000000;
}

void	init_pos_player(t_mlx *mlx, int x, int y)
{
	mlx->player->posX = (double)x + 0.5;
	mlx->player->posY = (double)y + 0.5;
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
		printf("ERREUR: player not found\n");
	if (nb_sprite > 1)
		printf("WARNING: plusieurs position de sprite trouve, une seule sera prise en compte\n");
}

void	init_player(t_mlx *mlx)
{
	t_player	*player;
	t_texture	*texture;

	player = malloc(sizeof(t_player));
	texture = malloc(sizeof(t_texture));
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.86;
	player->init_posx = -1;
	player->init_poxy = -1;
	texture->rgb_ceiling = 0;
	texture->rgb_floor = 0;
	player->sprite_x = -1;
	player->sprite_y = -1;
	mlx->player = player;
	mlx->texture = texture;
}

void	get_texture(t_mlx *mlx)
{
	void	*texture;
	int		a;

	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/wood.xpm", &a, &a);
	mlx->texture->ceiling =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/greystone.xpm", &a, &a);
	mlx->texture->floor =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	is_close(t_mlx *mlx, t_point size, t_point begin, t_point p)
{
	mlx->map[begin.y][begin.x] = '3';
	if (begin.y > 0 && mlx->map[begin.y - 1][begin.x] == '0')
	{
		p.y = begin.y - 1;
		p.x = begin.x;
		is_close(mlx, size, p, begin);
	}
	if ((begin.y < (size.y - 1)) && mlx->map[begin.y + 1][begin.x] == '0')
	{
		p.y = begin.y + 1;
		p.x = begin.x;
		is_close(mlx, size, p, begin);
	}
	if ((begin.x < (size.x - 1)) && mlx->map[begin.y][begin.x + 1] == '0')
	{
		p.x = begin.x + 1;
		p.y = begin.y;
		is_close(mlx, size, p, begin);
	}
	if (begin.x > 0 && mlx->map[begin.y][begin.x - 1] == '0')
	{
		p.x = begin.x - 1;
		p.y = begin.y;
		is_close(mlx, size, p, begin);
	}
}

int		check_error_map(t_mlx *mlx)
{
	int i;
	int j;

	i = -1;
	while (++i < mlx->map_height)
	{
		j = -1;
		while (++j < mlx->map_width)
		{
			printf("%c", mlx->map[i][j]);
			if (mlx->map[i][j] < '0' || mlx->map[i][j] > '3')
				return (2);
			if (mlx->map[i][j] == '3' && (i == 0 || i ==
				mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
				return (1);
		}
		printf("\n");
	}
	return (0);
}

int		clean_exit(t_mlx *mlx)
{
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

int		check_map(t_mlx *mlx)
{
	t_point	size;
	t_point	begin;
	int		j;
	int		i;

	size.y = mlx->map_height;
	size.x = mlx->map_width;
	begin.x = mlx->player->init_poxy;
	begin.y = mlx->player->init_posx;
	i = -1;
	while (++i < mlx->map_height)
	{
		j = -1;
		while (++j < mlx->map_width)
			if (mlx->map[i][j] == ' ')
				mlx->map[i][j] = '0';
	}
	is_close(mlx, size, begin, begin);
	i = 0;
	return (check_error_map(mlx));
}

void	engine(t_mlx *mlx)
{
	put_frame(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_hook(mlx->window, 17, 0, clean_exit, mlx);
	mlx_loop(mlx->mlx);
}

void	erreur_exit(t_mlx *mlx, int error_id)
{
	write(1, "error\n", 7);
	if (error_id == 1)
		write(1, "malloc fail\n", 13);
	if (error_id == 2)
		write(1, "map not found\n", 15);
	if (error_id == 3)
		write(1, "player not found\n", 18);
	if (error_id == 4)
		write(1, "map incorrect\n", 15);
	if (error_id == 5)
		write(1, "texture not loaded\n", 20);
	if (error_id == 6)
		write(1, "capture error\n", 15);
	clean_exit(mlx);
}

int		main(int argc, char *argv[])
{
	t_mlx *mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
		erreur_exit(mlx, 1);
	mlx->mlx = mlx_init();
	mlx->capture = 0;
	init_player(mlx);
	if (argc == 2 || argc == 3)
		full_parsing(argv[1], mlx);
	else
		erreur_exit(mlx, 2);
	check_player_pos(mlx);
	if (mlx->player->init_posx == -1 || mlx->player->init_poxy == -1)
		erreur_exit(mlx, 3);
	if (check_map(mlx) != 0)
		erreur_exit(mlx, 4);
	mlx->window = mlx_new_window(mlx->mlx,
		mlx->screen_width, mlx->screen_height, "Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	get_texture(mlx);
	raycasting(mlx);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		mlx->capture = 1;
	engine(mlx);
	return (0);
}

/*
**	//mlx_hook(mlx->window, 17, 0, clean_exit, mlx);
*/
