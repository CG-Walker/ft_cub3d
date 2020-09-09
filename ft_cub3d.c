/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:46:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/09 12:41:45 by badrien          ###   ########.fr       */
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

void	floor_and_sky(t_mlx *mlx)
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

void	add_sprite(t_mlx *mlx, double ZBuffer[screenWidth])
{
		double spriteX;
		double spriteY;
		double invDet;
		double transformX;
		double transformY;
		
		int spriteScreenX;
		int spriteHeight;
		int drawStartY;
		int drawEndY;
		int spriteWidth;
		int drawStartX;
		int drawEndX;
		int stripe;
		int texX;
		int texY;
		int y;
		int d;
		int color;
		int h;
		int w;

		h = screenHeight;
		w = screenWidth;

		spriteX = mlx->player->sprite_x - mlx->player->posX;
      	spriteY = mlx->player->sprite_y - mlx->player->posY;

		invDet = 1.0 / (mlx->player->planeX * mlx->player->dirY - mlx->player->dirX * mlx->player->planeY);

		transformX = invDet * (mlx->player->dirY * spriteX - mlx->player->dirX * spriteY);
		transformY = invDet * ((-(mlx->player->planeY)) * spriteX + mlx->player->planeX * spriteY);
		
		spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

		spriteHeight = abs((int)(h / (transformY)));

		drawStartY = -spriteHeight / 2 + h / 2;
		if (drawStartY < 0) 
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h) 
			drawEndY = h - 1;

		spriteWidth = abs((int) (h / (transformY)));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) 
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w) 
			drawEndX = w - 1;

		for(stripe = drawStartX; stripe < drawEndX; stripe++)
      	{
        	texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        	if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        	for(y = drawStartY; y < drawEndY; y++)
        	{
          		d = (y) * 256 - h * 128 + spriteHeight * 128;
          		texY = ((d * texHeight) / spriteHeight) / 256;
          		color = mlx->texture->sprite[(texWidth * texY) + texX];
          		if((color & 0x00FFFFFF) != 0) 
		  			mlx->data[stripe + (y * mlx->screen_width)] = color;
        	}
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

	double ZBuffer[screenWidth];

	x = 0;
	w = mlx->screen_width;
	h = mlx->screen_height; 
	if (mlx->texture->rgb_ceiling == 0 && mlx->texture->rgb_floor == 0)
		floor_and_sky_text(mlx);
	else
		floor_and_sky(mlx);
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
			if (mlx->map[(int)mapx][(int)mapy] == '1')
				hit = 1;
		}
		if (side == 0)
			perpwalldist =
				(mapx - mlx->player->posX + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist =
				(mapy - mlx->player->posY + (1 - stepy) / 2) / raydiry;

		h = mlx->screen_height;

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
			mlx->data[x - 1 + y * mlx->screen_width] = color;
		}	
		ZBuffer[x] = perpwalldist;
	}
		/* -----------------SPRITE----------------- */
		if(mlx->player->sprite_x != -1)
			add_sprite(mlx, ZBuffer);

		put_frame(mlx);
	return (0);
}

void check_player_pos(t_mlx *mlx)
{
	size_t x;
	size_t y;

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
			}
			y++;
		}
		y = 0;
		x++;
	}
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

	a = 64;
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/wood.xpm", &a, &a);
	mlx->texture->ceiling =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	
	texture = mlx_xpm_file_to_image(mlx->mlx, "pics/greystone.xpm", &a, &a);
	mlx->texture->floor =
		(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

int 			is_close(t_mlx *mlx, t_point size, t_point begin, char c)
{
	t_point p;

	//printf("TEST\n");
	//printf("valeur case actuel: %c\n\n\n", mlx->map[begin.x][begin.y]);
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

	/*------------*/

	t_point size;
	t_point begin;

	size.y = mlx->map_height;
	size.x = mlx->map_width;
	begin.x = mlx->player->init_poxy;
	begin.y = mlx->player->init_posx;

	//mlx->map[(int)mlx->player->posX][(int)mlx->player->posY] = '0';
	
	printf("valeur begin x et begin y: %f et %f\n\n\n",mlx->player->posX,mlx->player->posY);

	printf("valeur begin x et begin y: %d et %d\n\n\n",begin.x,begin.y);

	int i;
	int j;
	int error;
	
	error = 0;

	for(i=0; i<mlx->map_height; i++)
    {
        for(j=0; j<mlx->map_width; j++)
            if(mlx->map[i][j] == ' ')
				mlx->map[i][j] = '0';
        printf("\n");
    }
	
	printf("\n%d\n",is_close(mlx, size, begin, '3'));

	for(i=0; i<mlx->map_height; i++)
    {
        for(j=0; j<mlx->map_width; j++)
        {
			printf("%c", mlx->map[i][j]);
			if(mlx->map[i][j] < '0' ||  mlx->map[i][j] > '3')
			{
				printf("ERREUR ICI");
				error = 2;
			}
			if(mlx->map[i][j] == '3' && (i == 0 || i == mlx->map_height - 1 || j == 0 || j == mlx->map_width - 1))
			{
				//printf("FUITE ICI");
				error = 1;
			}	
		}  
        printf("\n");
    }
	if(error > 0)
	{
		printf("ON AS UNE ERREUR! type: %d\n", error);
		return (1);
	}
	else

	/*------------------*/

	mlx->window = mlx_new_window(mlx->mlx, mlx->screen_width, mlx->screen_height, "Cub3D");
	mlx->frame = NULL;
	put_frame(mlx);
	get_texture(mlx);
	raycasting(mlx);
	mlx_hook(mlx->window, 2, 0, move, mlx);
	mlx_loop(mlx->mlx);

	return (0);
}
