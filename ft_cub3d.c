/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/05 14:03:38 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

/*
** TEMPORAIRE
*/

int worldMap[mapWidth][mapHeight] =
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
};

void	put_frame(t_mlx *mlx)
{
	if (mlx->frame != NULL)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame);
	}
	mlx->frame = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->data =
		(int*)mlx_get_data_addr(mlx->frame, &mlx->bpp, &mlx->sl, &mlx->endian);
}

int		check_map()
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= mapWidth - 1)
	{
		if (worldMap[x][y] == -1)
			return (-1);
		//printf("[%d][%d] : %d\n", x, y, worldMap[x][y]);
		x++;
		if (x == mapWidth && y != mapHeight - 1)
		{
			x = 0;
			y = mapHeight - 1;
		}
	}
	x--;
	while (y >= 0)
	{
		if (worldMap[x][y] == -1)
			return (-1);
		//printf("[%d][%d] : %d\n", x, y, worldMap[x][y]);
		y--;
		if (y <= -1 && x != 0)
		{
			y = mapHeight - 1;
			x = 0;
		}
	}
	return (1);
}

void	floor_and_sky(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < screenWidth)
	{
		while (y < screenHeight / 2)
		{
			mlx->data[x + (y * screenWidth)] = 0x0066CC;
			y++;
		}
		x++;
		y = 0;
	}
	x = 0;
	y = screenHeight / 2;
	while (x < screenWidth)
	{
		while (y < screenHeight)
		{
			mlx->data[x + (y * screenWidth)] = 0x330000;
			y++;
		}
		x++;
		y = screenHeight / 2;
	}
}

void	draw(t_mlx *mlx,int start, int end, int mapX, int mapY, int x)
{
	int color;
	int debut;

	debut = start;
	switch(worldMap[mapX][mapY])
	{
		case 1:  color = 0xFF0000;	break;
		case 2:  color = 0x00FF00;  break;
		case 3:  color = 0x0000FF;  break;
		case 4:  color = 0xFFFFFF;  break;
		default: color = 0xFFFF33; 	break;
	}
	while (start <= end)
	{
		if (debut >= start - 1)
			mlx->data[x - 1 + (start * screenWidth)] = color + 0xAAAAAA;
		else if (start >= end - 1)
			mlx->data[x - 1 + (start * screenWidth)] = color + 0xAAAAAA;
		else
			mlx->data[x - 1 + (start * screenWidth)] = color;
		start++;
	}
}

int		raycasting(t_mlx *mlx)
{
	int w;
	int x;
	int mapx;
	int mapy;
	int stepx;
	int stepy;
	int h;

	double time = 0;
	double oldtime = 0;

	double camerax;
	double raydirx;
	double raydiry;

	double sidedistx;
	double sidedisty;

	double deltadistx;
	double deltadisty;
	double perpwalldist;

	int hit;
	int side;

	int lineheight;
	int drawstart;
	int drawend;

	double wallX;
	int texX;
	double step;
	double texPos;
	int texY;

	int color;

	x = 0;
	w = screenWidth;
	h = screenHeight; 
	//floor_and_sky(mlx);
	
	for(int y = 0; y < h; y++)
    {
      float rayDirX0 = mlx->player->dirX - mlx->player->planeX;
      float rayDirY0 = mlx->player->dirY - mlx->player->planeY;
      float rayDirX1 = mlx->player->dirX + mlx->player->planeX;
      float rayDirY1 = mlx->player->dirY + mlx->player->planeY;
      
			int p = y - screenHeight / 2;
      float posZ = 0.5 * screenHeight;
      float rowDistance = posZ / p;
    	
			float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

      float floorX = mlx->player->posX + rowDistance * rayDirX0;
      float floorY = mlx->player->posY + rowDistance * rayDirY0;

      for(int x = 0; x < screenWidth; ++x)
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
        mlx->data[x + (y * screenWidth)] = color;        

        color = mlx->texture->ceiling[texWidth * ty + tx];
        color = (color >> 1) & 8355711;
        mlx->data[x + ((screenHeight - y - 1) * screenWidth)] = color;        
      }
    }
	
	x = 0;

	while (x++ < w) // Wall casting
	{
		camerax = 2 * x / (double)w - 1;
		raydirx = mlx->player->dirX + mlx->player->planeX * camerax;
		raydiry = mlx->player->dirY + mlx->player->planeY * camerax;

		mapx = (int)mlx->player->posX;
		mapy = (int)mlx->player->posY;

		deltadistx = (raydiry == 0) ? 0 : ((raydirx == 0) ? 1 : fabs(1 / raydirx));
		deltadisty = (raydirx == 0) ? 0 : ((raydiry == 0) ? 1 : fabs(1 / raydiry));

		hit = 0;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (mlx->player->posX - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - mlx->player->posX) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (mlx->player->posY - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - mlx->player->posY) * deltadisty;
		}

		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (worldMap[mapx][mapy] > 0)
				hit = 1;
		}
		if (side == 0)
			perpwalldist =
				(mapx - mlx->player->posX + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist =
				(mapy - mlx->player->posY + (1 - stepy) / 2) / raydiry;

		h = screenHeight;

		lineheight = (int)(h / perpwalldist);

		drawstart = -lineheight / 2 + h / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + h / 2;
		if (drawend >= h)
			drawend = h - 1;

		if (side == 0)
			wallX = mlx->player->posY + perpwalldist * raydiry;
		else
			wallX = mlx->player->posX + perpwalldist * raydirx;
		wallX -= floor((wallX));

		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && raydirx > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && raydiry < 0)
			texX = texWidth - texX - 1;

		step = 1.0 * texHeight / lineheight;
		texPos = (drawstart - h / 2 + lineheight / 2) * step;
		for (int y = drawstart; y<drawend; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 1)
			{
				if (raydiry >= 0)
					color = mlx->texture->west[(texHeight * texY) + texX];
				else
					color = mlx->texture->east[(texHeight * texY) + texX];
			}
			else
			{
				if (raydirx >= 0)
					color = mlx->texture->north[(texHeight * texY) + texX];
				else
					color = mlx->texture->south[(texHeight * texY) + texX];
			}
			//if (side == 1)
			//	color = (color >> 1) & 8355711;
			mlx->data[x + y * screenWidth] = color;
		}
	}
	put_frame(mlx);
	return (0);
}

void	init_player(t_mlx *mlx)
{
	t_player	*player;
	t_texture	*texture;

	player = malloc(sizeof(t_player));
	texture = malloc(sizeof(t_texture));

	player->posX = 22;
	player->posY = 12;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;

	mlx->player = player;
	mlx->texture = texture;
}

void	get_texture(t_mlx *mlx)
{
	void	*texture;
	int		a;

	a = 64;
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/eagle.xpm", &a, &a);
	mlx->texture->west =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/redbrick.xpm", &a, &a);
	mlx->texture->east =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/mossy.xpm", &a, &a);
	mlx->texture->north =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/bluestone.xpm", &a, &a);
	mlx->texture->south =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/wood.xpm", &a, &a);
	mlx->texture->ceiling =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/greystone.xpm", &a, &a);
	mlx->texture->floor =
		(int*)mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);
	
}

int		main(void)
{
	t_mlx *mlx;

	if (check_map() == -1)
		exit(-1);
	mlx = malloc(sizeof(t_mlx));

	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);

	init_player(mlx);
	get_texture(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);

	return (0);
}
