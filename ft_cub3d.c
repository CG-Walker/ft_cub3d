/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/02/25 16:36:18 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "ft_map.h"

/*
void	draw_screen(t_mlx *mlx)
{
	double i;
	if (worldMap[(int)mlx->player->posX + i][(int)mlx->player->posY + i] == '1')
	{
		mlx_pixel_put(mlx->mlx, mlx->window, 1, 500 - (i * 10), 0xFFFFFF);
	}
	else
	{
		i++;
		if (mlx->player->posX + i > mapWidth || mlx->player->posY + i > mapHeight)
			i--;
	}
	
}
*/

int		raycasting(t_mlx *mlx)
{
	/*
	double posX = 21.5, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	*/
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	int w = screenWidth;
	
	double cameraX; //x-coordinate in camera space
    double rayDirX;
    double rayDirY;
	int x = 0;

	while (x++ < w)
    {
		//calculate ray position and direction
    	cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
    	rayDirX = mlx->player->dirX + mlx->player->planeX * cameraX;
    	rayDirY = mlx->player->dirY + mlx->player->planeY * cameraX;
	
		//which box of the map we're in
		int mapX = (int)mlx->player->posX;
		int mapY = (int)mlx->player->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (mlx->player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - mlx->player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mlx->player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - mlx->player->posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) 
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) 
			perpWallDist = (mapX - mlx->player->posX + (1 - stepX) / 2) / rayDirX;
		else           
			perpWallDist = (mapY - mlx->player->posY + (1 - stepY) / 2) / rayDirY;

		int h = screenHeight;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		int color;
		switch(worldMap[mapX][mapY])
      	{
        	case 1:  color = 0xFF0000;	break; //red
        	case 2:  color = 0x00FF00;  break; //green
        	case 3:  color = 0x0000FF;  break; //blue
        	case 4:  color = 0xFFFFFF;  break; //white
        	default: color = 0xFFFF33; 	break; //yellow
      	}
		while (drawStart <= drawEnd)
		{
			mlx_pixel_put(mlx->mlx, mlx->window, x, drawStart, color);
			drawStart++;
		}
	}
	return (0);
}

void init_player(t_mlx *mlx)
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

int move(int key, t_mlx *mlx)
{	
	double moveSpeed = 0.2;
	double rotSpeed = 0.1;
	if (key == A_KEY)
	{
		mlx->player->posY -= moveSpeed;
	}
	if (key == D_KEY)
	{
		mlx->player->posY += moveSpeed;
	}
	//move forward if no wall in front of you
    if (key == W_KEY)
    {
      if(worldMap[(int)(mlx->player->posX + mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0) mlx->player->posX += mlx->player->dirX * moveSpeed;
      if(worldMap[(int)(mlx->player->posX)][(int)(mlx->player->posY + mlx->player->dirY * moveSpeed)] == 0) mlx->player->posY += mlx->player->dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (key == S_KEY)
    {
      if(worldMap[(int)(mlx->player->posX - mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0) mlx->player->posX -= mlx->player->dirX * moveSpeed;
      if(worldMap[(int)mlx->player->posX][(int)(mlx->player->posY - mlx->player->dirY * moveSpeed)] == 0) mlx->player->posY -= mlx->player->dirY * moveSpeed;
    }
	if (key == ESC_KEY)
	{
		exit(0);
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
	mlx_clear_window(mlx->mlx, mlx->window);
	raycasting(mlx);
	return (1);
}

int main(void)
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));

	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");

	init_player(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}