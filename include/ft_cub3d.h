/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:47:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/24 12:44:18 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <math.h>

# include <mlx.h>

# include "keynote.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define CAPTURE_FILENAME "capture.bmp"
# define IMG_DEPTH 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

# define ERROR_MALLOC_FAILED 1
# define ERROR_MAP_NOT_FOUND 2
# define ERROR_PLAYER_NOT_FOUND 3
# define ERROR_MAP_INCORRECT 4
# define ERROR_TEXTURE_NOT_LOADED 5
# define ERROR_CAPTURE_FAILED 6
# define ERROR_UNEXPECTED_ARGS 7
# define ERROR_SCREEN_SIZE 8
# define ERROR_RGB 9

# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef unsigned char	t_byte;
typedef struct			s_sprite
{
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	double	*zbuffer;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		stripe;
	int		texx;
	int		texy;
	int		y;
	int		d;
	int		color;
	int		h;
	int		w;
}						t_sprite;

typedef struct			s_ray
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
	int		texy;
	int		color;
	int		texx;
	double	step;
	double	wallx;
	double	texpos;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
}						t_ray;

typedef struct			s_floor_sky
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
}						t_floor_sky;

typedef struct			s_texture
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
}						t_texture;

typedef struct			s_player
{
	int		init_posx;
	int		init_poxy;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	sprite_x;
	double	sprite_y;
}						t_player;

typedef struct			s_mlx
{
	void		*mlx;
	void		*window;
	size_t		screen_width;
	size_t		screen_height;
	char		**map;
	size_t		map_width;
	size_t		map_height;
	void		*frame;
	int			*data;
	int			bpp;
	int			sl;
	int			endian;
	int			capture;
	t_player	*player;
	t_texture	*texture;
}						t_mlx;

typedef struct			s_point
{
	int			x;
	int			y;
}						t_point;

/*
** ft_capture.c
*/

int						capture(t_mlx *mlx);
int						bmp_write(t_mlx *mlx,
							t_byte file_header[FILE_HEADER_SIZE],
								t_byte info_header[INFO_HEADER_SIZE]);
void					bmp_write_pixels(int fd, t_mlx *mlx, t_byte *bmp_data);
void					bmp_fill_header(t_mlx *mlx,
							t_byte file_header[FILE_HEADER_SIZE],
								t_byte info_header[INFO_HEADER_SIZE]);

/*
** ft_cub3d.c
*/

void					put_frame(t_mlx *mlx);
void					add_map(t_mlx *mlx);
void					engine(t_mlx *mlx);
int						main(int argc, char *argv[]);

/*
**	ft_draw_floor_sky.c
*/

void					floor_and_sky_color(t_mlx *mlx);
void					get_data(t_mlx *mlx, t_floor_sky *data);
void					draw_data(t_mlx *mlx, t_floor_sky *data, int x);
void					floor_and_sky_text(t_mlx *mlx);

/*
**	ft_draw_wall.c
*/

void					calc_ray(t_mlx *mlx, t_ray *ray);
void					calc_side_dist(t_mlx *mlx, t_ray *ray);
void					check_hit(t_mlx *mlx, t_ray *ray);
void					print_wall(t_mlx *mlx, t_ray *ray);

/*
**	ft_exit.c
*/

void					error_exit(t_mlx *mlx, int error_id);
int						clean_exit(t_mlx *mlx);

/*
**	ft_init.c
*/

void					init_pos_player(t_mlx *mlx, int x, int y);
void					check_player_pos(t_mlx *mlx);
void					init_data(t_mlx *mlx);
void					get_texture(t_mlx *mlx);

/*
**	ft_map.c
*/

void					is_close(t_mlx *mlx, t_point size,
							t_point begin, t_point p);
int						check_error_map(t_mlx *mlx);
int						check_map(t_mlx *mlx);

/*
** ft_movements_rot
*/

void					rot_right(t_mlx *mlx, double rot_speed);
void					rot_left(t_mlx *mlx, double rot_speed);

/*
** ft_movements
*/

int						move(int key, t_mlx *mlx);
void					mv_left(t_mlx *mlx, double move_speed);
void					mv_right(t_mlx *mlx, double move_speed);
void					mv_forward(t_mlx *mlx, double move_speed);
void					mv_backward(t_mlx *mlx, double move_speed);

/*
**	ft_parsing_params
*/

void					r_id(char *s, t_mlx *mlx);
void					nesw_id(char *s, int nesw, t_mlx *mlx);
void					fc_id(char *s, int fc, t_mlx *mlx);
int						check_id(char *s, t_mlx *mlx);

/*
**  ft_parsing
*/

size_t					count_file_size(int fd, size_t file_size);
void					full_parsing(char *file, t_mlx *mlx, size_t i);
char					**make_world_map(char *file,
							size_t file_size, t_mlx *mlx);
char					**fill_world_map(t_mlx *mlx, char **world_map,
							int fd, t_point size);

/*
** ft_raycasting
*/

void					calc_draw_size(t_mlx *mlx, t_ray *ray);
void					calc_tex_size(t_mlx *mlx, t_ray *ray);
void					draw_wall(t_mlx *mlx, t_ray *ray, double *zbuffer);
int						raycasting(t_mlx *mlx);

/*
** ft_sprite
*/

void					size_sprite(t_mlx *mlx, t_sprite *sprite);
void					pre_draw_sprite(t_sprite *sprite);
void					draw_sprite(t_mlx *mlx, t_sprite *sprite);
void					add_sprite(t_mlx *mlx, double *zbuffer);

#endif
