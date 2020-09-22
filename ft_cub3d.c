/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/22 13:56:31 by badrien          ###   ########.fr       */
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
				mlx->data[(x + (mlx->screen_height / 35) + ((y + (mlx->screen_width / 35))
					* mlx->screen_width))] = color;
			}
		y = 0;
	}
	y = (int)mlx->player->posX + (mlx->screen_height / 35) +
		((int)mlx->player->posY + (mlx->screen_width / 35)) * mlx->screen_width;
	mlx->data[y] = 0x000000;
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

	//a = 64; --> le a recupere la taille de la texture donc pas besoin d'harcoder le tout
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/wood.xpm", &a, &a);
	mlx->texture->ceiling =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/greystone.xpm", &a, &a);
	mlx->texture->floor =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}

int		is_close(t_mlx *mlx, t_point size, t_point begin, char c)
{
	t_point p;

	//p = begin;
	mlx->map[begin.y][begin.x] = c;
	if (begin.y > 0 && mlx->map[begin.y - 1][begin.x] == '0')
	{
		p.y = begin.y - 1;
		p.x = begin.x;
		is_close(mlx, size, p, c);
	}
	if ((begin.y < (size.y - 1)) && mlx->map[begin.y + 1][begin.x] == '0')
	{
		p.y = begin.y + 1;
		p.x = begin.x;
		is_close(mlx, size, p, c);
	}
	if ((begin.x < (size.x - 1)) && mlx->map[begin.y][begin.x + 1] == '0')
	{
		p.x = begin.x + 1;
		p.y = begin.y;
		is_close(mlx, size, p, c);
	}
	if (begin.x > 0 && mlx->map[begin.y][begin.x - 1] == '0')
	{
		p.x = begin.x - 1;
		p.y = begin.y;
		is_close(mlx, size, p, c);
	}
	return (0);
}

int		check_map(t_mlx *mlx)
{
	t_point size;
	t_point begin;
	int j;
	int i;
	int error;

	size.y = mlx->map_height;
	size.x = mlx->map_width;
	begin.x = mlx->player->init_poxy;
	begin.y = mlx->player->init_posx;
	error = 0;

	
	for(i=0; i<mlx->map_height; i++)
    {
        for(j=0; j<mlx->map_width; j++)
            if(mlx->map[i][j] == ' ')
				mlx->map[i][j] = '0';
    }

	int x;
	int y;

	for(x=0; x<mlx->map_height; x++)
    {
        for(y=0; y<mlx->map_width; y++)
        {
			printf("%c", mlx->map[x][y]);
		}
		printf("\n");
    }

	is_close(mlx, size, begin, '3');
	for(i=0; i<mlx->map_height; i++)
    {
        for(j=0; j<mlx->map_width; j++)
        {
			printf("%c", mlx->map[i][j]);
			//if(mlx->map[i][j] < '0' ||  mlx->map[i][j] > '3')
			//	error = 2;
			if(mlx->map[i][j] == '3' && (i == 0 || i == mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
				error = 1;
		}
		printf("\n");
    }
	if (error > 0)
	{
		printf("ON AS UNE ERREUR! code erreur: %d\n", error);
		return (1);
	}
	else
		printf("MAP OK\n");
	return (0);
}

int		main(int argc, char *argv[])
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	init_player(mlx);
	if (argc == 2)
		full_parsing(argv[1], mlx);
	else
		return (1);
	check_player_pos(mlx);
	if (mlx->player->init_posx == -1 || mlx->player->init_poxy == -1)
		return (1);
	if (check_map(mlx) != 0)
		return (1);
	mlx->window = mlx_new_window(mlx->mlx,
		mlx->screen_width, mlx->screen_height, "Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	get_texture(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	//mlx_hook(mlx->window, 17, 0, clean_exit, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
