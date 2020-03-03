/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/03/03 17:53:03 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "ft_map.h"

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
	int x = 0;
	int y = 0;
	while (x < screenWidth)
	{
		while (y < screenHeight / 2)
		{
			mlx->data[x + (y * screenWidth)] = 0x0066CC;
			y++;
		}
		y = 0;
		x++;
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
		y = screenHeight / 2;
		x++;
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

void drawBuffer(int **buffer, t_mlx *mlx)
{
	int x;
	int y;
	
	x = 0;
	y = 0;

	while (x < screenWidth)
	{
		while (y < screenHeight)
		{
			mlx->data[x + (y * screenWidth)] = buffer[x][y];
			y++;
		}
		y = 0;
		x++;
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

	void *texture;
	int *image;
	int a;

	a = 64;

	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/greystone.xpm", &a, &a);

	image = (int*) mlx_get_data_addr(texture,&mlx->bpp, &mlx->sl, &mlx->endian);


	double wallX; //where exactly the wall was hit
	int texX;
	double step;
	double texPos;
	int texY;
	int color;

	x = 0;
	w = screenWidth;
	floor_and_sky(mlx);

	while (x++ < w)
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

	/* DEBUT TEXTURE */
		
    //texturing calculations
    
	//int texNum = worldMap[mapx][mapy] - 1; //1 subtracted from it so that texture 0 can be used!

		//int **buffer[screenHeight][screenWidth];

    	//calculate value of wallX
    	if (side == 0) 
			wallX = mlx->player->posY + perpwalldist * raydiry;
    	else
			wallX = mlx->player->posX + perpwalldist * raydirx;
    	wallX -= floor((wallX));

    //x coordinate on the texture
    	texX = (int)(wallX * (double)texWidth);
    	if(side == 0 && raydirx > 0) texX = texWidth - texX - 1;
    	if(side == 1 && raydiry < 0) texX = texWidth - texX - 1;
		
	
	// How much to increase the texture coordinate per screen pixel
    	step = 1.0 * texHeight / lineheight;
    // Starting texture coordinate
    	texPos = (drawstart - h / 2 + lineheight / 2) * step;
    	for(int y = drawstart; y<drawend; y++)
		{
    	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
    		texY = (int)texPos & (texHeight - 1);
    		texPos += step;
        	color = image[(texHeight * texY) + texX];
        	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        	if (side == 1) color = (color >> 1) & 8355711;
        	mlx->data[x + y * screenWidth] = color;
		}
    }

	/* FIN TEXTURE*/

	put_frame(mlx);
	return (0);
}


void	init_player(t_mlx *mlx)
{
	t_player *player;
	player = malloc(sizeof(t_player));

	player->posX = 22;
	player->posY = 12;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.86;

	mlx->player = player;
}

int		move(int key, t_mlx *mlx)
{
	double moveSpeed = 0.3;
	double rotSpeed = 0.1;
	if (key == A_KEY)
	{
		if (worldMap[(int)(mlx->player->posX - mlx->player->dirY * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX -= mlx->player->dirY * moveSpeed;
		if (worldMap[(int)(mlx->player->posX)][(int)(mlx->player->posY + mlx->player->dirX * moveSpeed)] == 0)
			mlx->player->posY += mlx->player->dirX * moveSpeed;
	}
	if (key == D_KEY)
	{
		if (worldMap[(int)(mlx->player->posX + mlx->player->dirY * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX += mlx->player->dirY * moveSpeed;
		if (worldMap[(int)(mlx->player->posX)][(int)(mlx->player->posY - mlx->player->dirX * moveSpeed)] == 0)
			mlx->player->posY -= mlx->player->dirX * moveSpeed;
	}
	//move forward if no wall in front of you
	if (key == W_KEY)
	{
		if (worldMap[(int)(mlx->player->posX + mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX += mlx->player->dirX * moveSpeed;
		if (worldMap[(int)(mlx->player->posX)][(int)(mlx->player->posY + mlx->player->dirY * moveSpeed)] == 0)
			mlx->player->posY += mlx->player->dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == S_KEY)
	{
		if (worldMap[(int)(mlx->player->posX - mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX -= mlx->player->dirX * moveSpeed;
		if (worldMap[(int)mlx->player->posX][(int)(mlx->player->posY - mlx->player->dirY * moveSpeed)] == 0)
			mlx->player->posY -= mlx->player->dirY * moveSpeed;
	}
	//rotate to the right
	if (key == RIGHT_KEY)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->player->dirX;
		mlx->player->dirX = mlx->player->dirX * cos(-rotSpeed) - mlx->player->dirY * sin(-rotSpeed);
		mlx->player->dirY = oldDirX * sin(-rotSpeed) + mlx->player->dirY * cos(-rotSpeed);
		double oldPlaneX = mlx->player->planeX;
		mlx->player->planeX = mlx->player->planeX * cos(-rotSpeed) - mlx->player->planeY * sin(-rotSpeed);
		mlx->player->planeY = oldPlaneX * sin(-rotSpeed) + mlx->player->planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (key == LEFT_KEY)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->player->dirX;
		mlx->player->dirX = mlx->player->dirX * cos(rotSpeed) - mlx->player->dirY * sin(rotSpeed);
		mlx->player->dirY = oldDirX * sin(rotSpeed) + mlx->player->dirY * cos(rotSpeed);
		double oldPlaneX = mlx->player->planeX;
		mlx->player->planeX = mlx->player->planeX * cos(rotSpeed) - mlx->player->planeY * sin(rotSpeed);
		mlx->player->planeY = oldPlaneX * sin(rotSpeed) + mlx->player->planeY * cos(rotSpeed);
	}
	if (key == ESC_KEY)
	{
		exit(0);
	}
	mlx_clear_window(mlx->mlx, mlx->window);
	raycasting(mlx);
	return (1);
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
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);

	return (0);
}
 //mlx_xpm_file_to_image(mlx->mlx, )

 // -lz