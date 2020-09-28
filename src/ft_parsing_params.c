/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:35:10 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/28 13:33:20 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void	r_id(char *s, t_mlx *mlx)
{
	size_t i;

	i = 1;
	while (s[i] == ' ')
		i++;
	mlx->screen_width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] != ' ')
		i++;
	mlx->screen_height = ft_atoi(&s[i]);
	if (mlx->screen_width > 2560)
		mlx->screen_width = 2560;
	if (mlx->screen_height > 1440)
		mlx->screen_height = 1440;
	if (mlx->screen_height <= 50 || mlx->screen_width <= 50)
		error_exit(mlx, ERROR_SCREEN_SIZE);
}

void	nesw_id(char *s, int nesw, t_mlx *mlx)
{
	size_t	i;
	void	*texture;
	int		a;

	i = 2;
	while (s[i] == ' ')
		i++;
	if (open(&s[i], O_RDONLY) == -1)
		error_exit(mlx, ERROR_TEXTURE_NOT_LOADED);
	texture = mlx_xpm_file_to_image(mlx->mlx, &s[i], &a, &a);
	if (nesw == 0)
		mlx->texture->north =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 1)
		mlx->texture->south =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 2)
		mlx->texture->west =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 3)
		mlx->texture->east =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
	else if (nesw == 4)
		mlx->texture->sprite =
			(int*)mlx_get_data_addr(texture, &mlx->bpp, &mlx->sl, &mlx->endian);
}

void	fc_id(char *s, int fc, t_mlx *mlx)
{
	size_t	i;
	int		r;
	int		g;
	int		b;

	i = 1;
	while (s[i] == ' ')
		i++;
	r = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		i++;
	g = ft_atoi(&s[++i]);
	while (ft_isdigit(s[i]))
		i++;
	b = ft_atoi(&s[++i]);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		error_exit(mlx, ERROR_RGB);
	if (fc == 0)
		mlx->texture->rgb_floor = r + (g * 256) + (b * 256 * 256);
	else
		mlx->texture->rgb_ceiling = r + (g * 256) + (b * 256 * 256);
}

int		check_id(char *s, t_mlx *mlx)
{
	static size_t i = 0;

	if (s[0] == 'R')
		r_id(s, mlx);
	else if (s[0] == 'N' && s[1] == 'O')
		nesw_id(s, 0, mlx);
	else if (s[0] == 'S' && s[1] == 'O')
		nesw_id(s, 1, mlx);
	else if (s[0] == 'W' && s[1] == 'E')
		nesw_id(s, 2, mlx);
	else if (s[0] == 'E' && s[1] == 'A')
		nesw_id(s, 3, mlx);
	else if (s[0] == 'S' && s[1] != 'O')
		nesw_id(s, 4, mlx);
	else if (s[0] == 'F')
		fc_id(s, 0, mlx);
	else if (s[0] == 'C')
		fc_id(s, 1, mlx);
	else
		return (-1);
	i++;
	if (i == 8)
		return (1);
	return (0);
}
