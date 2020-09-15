/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/15 12:08:44 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

/*
** TEMPORAIRE
*/

/*int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,3,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

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

void	floor_and_sky_color(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height / 2)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_ceiling;
		x++;
		y = 0;
	}
	x = 0;
	y = mlx->screen_height / 2;
	while (x < mlx->screen_width)
	{
		while (y < mlx->screen_height)
			mlx->data[x + (y++ * mlx->screen_width)] = mlx->texture->rgb_floor;
		x++;
		y = mlx->screen_height / 2;
	}
}

void	floor_and_sky_text(t_mlx *mlx)
{
	for(int y = 0; y < screenHeight; y++)
		{
			float rayDirX0 = mlx->player->dirX - mlx->player->planeX;
			float rayDirY0 = mlx->player->dirY - mlx->player->planeY;
			float rayDirX1 = mlx->player->dirX + mlx->player->planeX;
			float rayDirY1 = mlx->player->dirY + mlx->player->planeY;

			int p = y - mlx->screen_height / 2;
			float posZ = 0.5 * mlx->screen_height;
			float rowDistance = posZ / p;

			float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / mlx->screen_width;
			float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / mlx->screen_width;
			
			float floorX = mlx->player->posX + rowDistance * rayDirX0;
			float floorY = mlx->player->posY + rowDistance * rayDirY0;

			for(int x = 0; x < mlx->screen_width; ++x)
			{
				int cellX = (int)(floorX);
				int cellY = (int)(floorY);

				int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
				int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

				floorX += floorStepX;
				floorY += floorStepY;

				int color;

				color = mlx->texture->floor[texWidth * ty + tx];
				color = (color >> 1) & 8355711;
				mlx->data[x + (y * mlx->screen_width)] = color;        

				color = mlx->texture->ceiling[texWidth * ty + tx];
				color = (color >> 1) & 8355711;
				mlx->data[x + ((mlx->screen_height - y - 1) * mlx->screen_width)] = color;        
				}
			}
}

void	size_sprite(t_mlx *mlx, t_sprite *sprite)
{
		sprite->h = mlx->screen_height;
		sprite->w = mlx->screen_width;
		sprite->spriteX = mlx->player->sprite_x - mlx->player->posX;
      	sprite->spriteY = mlx->player->sprite_y - mlx->player->posY;

		sprite->invDet = 1.0 / (mlx->player->planeX * mlx->player->dirY - mlx->player->dirX * mlx->player->planeY);

		sprite->transformX = sprite->invDet * (mlx->player->dirY * sprite->spriteX - mlx->player->dirX * sprite->spriteY);
		sprite->transformY = sprite->invDet * ((-(mlx->player->planeY)) * sprite->spriteX + mlx->player->planeX * sprite->spriteY);
		sprite->spriteScreenX = (int)((sprite->w / 2) * (1 + sprite->transformX / sprite->transformY));

		sprite->spriteHeight = abs((int)(sprite->h / (sprite->transformY)));
}

void	draw_sprite(t_mlx *mlx, t_sprite *sprite)
{
			sprite->drawStartY = -(sprite->spriteHeight) / 2 + sprite->h / 2;
		if (sprite->drawStartY < 0) 
			sprite->drawStartY = 0;
		sprite->drawEndY = sprite->spriteHeight / 2 + sprite->h / 2;
		if (sprite->drawEndY >= sprite->h) 
			sprite->drawEndY = sprite->h - 1;

		sprite->spriteWidth = abs((int) (sprite->h / (sprite->transformY)));
		sprite->drawStartX = -(sprite->spriteWidth) / 2 + sprite->spriteScreenX;
		if (sprite->drawStartX < 0) 
			sprite->drawStartX = 0;
		sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
		if (sprite->drawEndX >= sprite->w) 
			sprite->drawEndX = sprite->w - 1;
}
void	add_sprite(t_mlx *mlx, double *ZBuffer)
{

	t_sprite *sprite;
	sprite = malloc(sizeof(t_sprite));

	size_sprite(mlx, sprite);
	draw_sprite(mlx, sprite);

	for(sprite->stripe = sprite->drawStartX; sprite->stripe < sprite->drawEndX; sprite->stripe++)
    {
        sprite->texX = (int)(256 * (sprite->stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX)) * texWidth / sprite->spriteWidth) / 256;
        if(sprite->transformY > 0 && sprite->stripe > 0 && sprite->stripe < sprite->w && sprite->transformY < ZBuffer[sprite->stripe])
        for(sprite->y = sprite->drawStartY; sprite->y < sprite->drawEndY; sprite->y++)
        {
         	sprite->d = (sprite->y) * 256 - sprite->h * 128 + sprite->spriteHeight * 128;
          	sprite->texY = ((sprite->d * texHeight) / sprite->spriteHeight) / 256;
          	sprite->color = mlx->texture->sprite[(texWidth * sprite->texY) + sprite->texX];
          	if((sprite->color & 0x00FFFFFF) != 0) 
		  		mlx->data[sprite->stripe + (sprite->y * mlx->screen_width)] = sprite->color;
        }
    }
}

void	add_map(t_mlx *mlx)
{
	int y;
	int x;
	int color;

	x = 0;
	y = 0;
	while (x < mlx->map_height)
	{
		while (y < mlx->map_width)
		{
			if (mlx->map[x][y] != '0')
			{
				if (mlx->map[x][y] == '1')
					color = 0x000000;
				if (mlx->map[x][y] == '2')
					color = 0xFF0000;
				if (mlx->map[x][y] == '3')
					color = 0x00CC00;
				mlx->data[(x + (screenHeight/35) + ((y + (screenWidth/35)) * mlx->screen_width))] = color;
			}
		y++;
		}
	y = 0;
	x++;
	}
	y = (int)mlx->player->posX + (screenHeight/35) + ((int)mlx->player->posY + (screenWidth/35)) * mlx->screen_width;
	mlx->data[y] = 0x000000;
}

int		raycasting(t_mlx *mlx)
{
	t_ray *ray;
	ray = malloc(sizeof(t_ray));

	double ZBuffer[screenWidth];

	ray->x = 0;
	ray->w = mlx->screen_width;
	ray->h = mlx->screen_height; 
	if (mlx->texture->rgb_ceiling == 0 && mlx->texture->rgb_floor == 0)
		floor_and_sky_text(mlx);
	else
		floor_and_sky_color(mlx);
	ray->x = 0;

	while (ray->x++ < ray->w) // Wall casting
	{
		ray->camerax = 2 * ray->x / (double)ray->w - 1;
		ray->raydirx = mlx->player->dirX + mlx->player->planeX * ray->camerax;
		ray->raydiry = mlx->player->dirY + mlx->player->planeY * ray->camerax;

		ray->mapx = (int)mlx->player->posX;
		ray->mapy = (int)mlx->player->posY;

		ray->deltadistx = (ray->raydiry == 0) ? 0 : ((ray->raydirx == 0) ? 1 : fabs(1 / ray->raydirx));
		ray->deltadisty = (ray->raydirx == 0) ? 0 : ((ray->raydiry == 0) ? 1 : fabs(1 / ray->raydiry));

		ray->hit = 0;

		if (ray->raydirx < 0)
		{
			ray->stepx = -1;
			ray->sidedistx = (mlx->player->posX - ray->mapx) * ray->deltadistx;
		}
		else
		{
			ray->stepx = 1;
			ray->sidedistx = (ray->mapx + 1.0 - mlx->player->posX) * ray->deltadistx;
		}
		if (ray->raydiry < 0)
		{
			ray->stepy = -1;
			ray->sidedisty = (mlx->player->posY - ray->mapy) * ray->deltadisty;
		}
		else
		{
			ray->stepy = 1;
			ray->sidedisty = (ray->mapy + 1.0 - mlx->player->posY) * ray->deltadisty;
		}

		while (ray->hit == 0)
		{
			if (ray->sidedistx < ray->sidedisty)
			{
				ray->sidedistx += ray->deltadistx;
				ray->mapx += ray->stepx;
				ray->side = 0;
			}
			else
			{
				ray->sidedisty += ray->deltadisty;
				ray->mapy += ray->stepy;
				ray->side = 1;
			}
			if (mlx->map[(int)ray->mapx][(int)ray->mapy] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist =
				(ray->mapx - mlx->player->posX + (1 - ray->stepx) / 2) / ray->raydirx;
		else
			ray->perpwalldist =
				(ray->mapy - mlx->player->posY + (1 - ray->stepy) / 2) / ray->raydiry;

		ray->h = mlx->screen_height;

		ray->lineheight = (int)(ray->h / ray->perpwalldist);

		ray->drawstart = -ray->lineheight / 2 + ray->h / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + ray->h / 2;
		if (ray->drawend >= ray->h)
			ray->drawend = ray->h - 1;

		if (ray->side == 0)
			ray->wallX = mlx->player->posY + ray->perpwalldist * ray->raydiry;
		else
			ray->wallX = mlx->player->posX + ray->perpwalldist * ray->raydirx;
		ray->wallX -= floor((ray->wallX));

		ray->texX = (int)(ray->wallX * (double)texWidth);
		if (ray->side == 0 && ray->raydirx > 0)
			ray->texX = texWidth - ray->texX - 1;
		if (ray->side == 1 && ray->raydiry < 0)
			ray->texX = texWidth - ray->texX - 1;

		ray->step = 1.0 * texHeight / ray->lineheight;
		ray->texPos = (ray->drawstart - ray->h / 2 + ray->lineheight / 2) * ray->step;
		for (ray->y = ray->drawstart; ray->y<ray->drawend; ray->y++)
		{
			ray->texY = (int)ray->texPos & (texHeight - 1);
			ray->texPos += ray->step;
			if (ray->side == 1)
			{
				if (ray->raydiry >= 0)
					ray->color = mlx->texture->west[(texHeight * ray->texY) + ray->texX];
				else
					ray->color = mlx->texture->east[(texHeight * ray->texY) + ray->texX];
			}
			else
			{
				if (ray->raydirx >= 0)
					ray->color = mlx->texture->north[(texHeight * ray->texY) + ray->texX];
				else
					ray->color = mlx->texture->south[(texHeight * ray->texY) + ray->texX];
			}
			mlx->data[ray->x - 1 + ray->y * mlx->screen_width] = ray->color;
		}	
		ZBuffer[ray->x] = ray->perpwalldist;
	}
		/* -----------------SPRITE----------------- */
	if(mlx->player->sprite_x != -1)
			add_sprite(mlx, ZBuffer);
	add_map(mlx);
	put_frame(mlx);
	return (0);
}

void	check_player_pos(t_mlx *mlx)
{
	size_t	x;
	size_t	y;
	int		nb_sprite;

	nb_sprite = 0;
	x = 0;
	y = 0;
	while (x < mlx->map_height)
	{
		while (y < mlx->map_width)
		{
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
			if (mlx->map[x][y] == '2')
			{
				mlx->player->sprite_x = x + 0.5;
				mlx->player->sprite_y = y + 0.5;
				nb_sprite++;
			}
			y++;
		}
		y = 0;
		x++;
	}
	if(mlx->player->init_posx == -1 || mlx->player->init_poxy == -1)
		printf("ERREUR: player not found\n");
	if(nb_sprite > 1)
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

int 	is_close(t_mlx *mlx, t_point size, t_point begin, char c)
{
	t_point p;

	mlx->map[begin.y][begin.x] = c;
	if (begin.y > 0 && mlx->map[begin.y - 1][begin.x] == '0')
	{
		p.x = begin.x;
		p.y = begin.y - 1;
		is_close(mlx, size, p, c);
	}
	if ((begin.y < (size.y - 1)) && mlx->map[begin.y + 1][begin.x] == '0')
	{
		p.x = begin.x;
		p.y = begin.y + 1;
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
	is_close(mlx, size, begin, '3');
	for(i=0; i<mlx->map_height; i++)
    {
        for(j=0; j<mlx->map_width; j++)
        {
			printf("%c", mlx->map[i][j]);
			if(mlx->map[i][j] < '0' ||  mlx->map[i][j] > '3')
				error = 2;
			if(mlx->map[i][j] == '3' && (i == 0 || i == mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
				error = 1;
		}
		printf("\n");
    }
	if(error > 0)
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
		parsing(argv[1], mlx);
	else
		return(1);
	check_player_pos(mlx);
	if(mlx->player->init_posx == -1 || mlx->player->init_poxy == -1)
		return (1);
	if(check_map(mlx) != 0)
		return (1);

	mlx->window = mlx_new_window(mlx->mlx, mlx->screen_width, mlx->screen_height, "Cub3D");
	mlx->frame = NULL;

	put_frame(mlx);
	get_texture(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);

	return (0);
}
