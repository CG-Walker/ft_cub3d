/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/02/26 15:03:26 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "ft_map.h"

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
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x0066CC);
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = screenHeight / 2;
	while (x < screenWidth)
	{
		while (y < screenHeight )
		{
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x330000);
			y++;
		}
		y = screenHeight / 2;
		x++;
	}
}

void draw(t_mlx *mlx,int start, int end, int mapX, int mapY, int x)
{
	int color;
	switch(worldMap[mapX][mapY])
	{
		case 1:  color = 0xFF0000;	break; //red
		case 2:  color = 0x00FF00;  break; //green
		case 3:  color = 0x0000FF;  break; //blue
		case 4:  color = 0xFFFFFF;  break; //white
		default: color = 0xFFFF33; 	break; //yellow
	}
	while (start <= end)
	{
		mlx_pixel_put(mlx->mlx, mlx->window, x, start, color);
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

		draw(mlx, drawstart, drawend, mapx, mapy, x);
	}
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
	player->planeY = 0.66;

	mlx->player = player;
}

int		move(int key, t_mlx *mlx)
{	
	double moveSpeed = 0.4;
	double rotSpeed = 0.1;
	if (key == A_KEY)
	{
		if (worldMap[(int)(mlx->player->posX - mlx->player->dirX * moveSpeed)][(int)mlx->player->posX] == 0)
			mlx->player->posX -= mlx->player->dirY * moveSpeed;
		if (worldMap[(int)(mlx->player->posX)][(int)(mlx->player->posY + mlx->player->dirX * moveSpeed)] == 0)
			mlx->player->posY += mlx->player->dirX * moveSpeed;
	}
	if (key == D_KEY)
	{
		if (worldMap[(int)(mlx->player->posX + mlx->player->dirX * moveSpeed)][(int)mlx->player->posX] == 0)
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

	init_player(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
