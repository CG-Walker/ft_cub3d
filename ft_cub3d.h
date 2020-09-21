/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:47:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/21 12:19:05 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <math.h>

# include <mlx.h>

# include "keynote.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_map.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_sprite
{
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	double *zbuffer;

	int spritescreenx;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int stripe;
	int texx;
	int texy;
	int y;
	int d;
	int color;
	int h;
	int w;
}				t_sprite;

typedef struct	s_ray
{
    int		w;
	int		x;
	int		y;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		h;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texY;
	int		color;
	int		texX;
	double	step;
	double	wallX;
	double	texPos;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
}				t_ray;

typedef struct	s_floor_sky
{
	int		p;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
	int		color;
	int		y;	
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	float	posz;
	float	rowdistance;
	float	floorstepx;
	float	floorstepy;	
	float	floorx;
	float	floory;
}				t_floor_sky;

typedef struct	s_texture // -> tableau de texture pour avoir des taille differente 
{
	int	*west;
	int	*east;
	int	*north;
	int	*south;
    int	*sprite;
    int	*ceiling;
    int	*floor;
    int	rgb_floor;
    int	rgb_ceiling;
}				t_texture;

typedef struct	s_player
{
    int		init_posx;
    int		init_poxy;

    double	posX;
    double	posY;
    double	dirX;
    double	dirY;
    double	planeX;
    double	planeY;
    double	sprite_x;
    double	sprite_y;
}				t_player;

typedef struct	s_mlx
{
    void        *mlx;
    void        *window;
    int         screen_width;
    int         screen_height;
    char        **map;
    int         map_width;
    int         map_height;
    void        *frame;
    int         *data;
    int         bpp;
    int         sl;
    int         endian;
    t_player    *player;
	t_texture	*texture;
}				t_mlx;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

/*
** ft_cub3d
*/

int		raycasting(t_mlx *mlx);

/*
** ft_deplacements
*/

int		move(int key, t_mlx *mlx);

/*
**  ft_parsing
*/

void	full_parsing(char *file, t_mlx *mlx);

/*
** ft_sprite
*/

void	add_sprite(t_mlx *mlx, double *ZBuffer);

/*
** ft_raycasting
*/

int		raycasting(t_mlx *mlx);

/*
**	ft_capture
*/

int		capture(t_mlx *mlx);
#endif