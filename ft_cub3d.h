/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:47:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/02/27 14:39:19 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <math.h>
# include <mlx.h>
# include "libft/libft.h"
# include "ft_map.h"
# include "keynote.h"

typedef struct  s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
}               t_player;

typedef struct  s_mlx
{
    void        *mlx;
    void        *window;
    void        *frame;
    int         *data;
    int         bpp;
    int         sl;
    int         endian;
    t_player    *player;
}               t_mlx;

#endif