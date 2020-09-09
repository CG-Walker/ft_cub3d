/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:47:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/09 13:27:55 by badrien          ###   ########.fr       */
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

typedef struct	s_ray
{
    /* data */
}				t_ray;

typedef struct	s_texture
{
	int *west;
	int *east;
	int *north;
	int *south;
    int *sprite;
    int *ceiling;
    int *floor;
    int rgb_floor;
    int rgb_ceiling;
}				t_texture;


typedef struct  s_player
{
    int init_posx;
    int init_poxy;

    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;

    double sprite_x;
    double sprite_y;
}               t_player;

typedef struct  s_mlx
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
	t_ray		*ray;
	t_texture	*texture;
}               t_mlx;

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

void	parsing(char *file, t_mlx *mlx);

#endif