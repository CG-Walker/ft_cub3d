/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:06:34 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/22 13:45:37 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

#define CAPTURE_FILENAME "capture.bmp"
#define IMG_DEPTH 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define t_byte unsigned char

int     bmp_write(t_mlx *image, t_byte file_header[FILE_HEADER_SIZE], t_byte info_header[INFO_HEADER_SIZE]);
void	bmp_write_pixels(int fd, t_mlx *image, t_byte *bmp_data);
void	bmp_fill_header(t_mlx *image, t_byte file_header[FILE_HEADER_SIZE], t_byte info_header[INFO_HEADER_SIZE]);

int		capture(t_mlx *state)
{
	t_byte	file_header[FILE_HEADER_SIZE];
	t_byte	info_header[INFO_HEADER_SIZE];


	bmp_fill_header(state, file_header, info_header);
    printf("SCREEN_WIDTH : %d\n", state->screen_width);
	if (!bmp_write(state, file_header, info_header))
	{
		return (1);
	}
	return (0);
}

/*
** bmp file format:
**     header:
**         file_header:
**             2: signature = "BM"
**             4: file size
**             4: reserved
**             4: offset to pixel array
**         info_header:
**	       4: header size
**	       4: image screen_width
**	       4: image screen_height
**	       2: number of color planes
**	       2: bits per pixel
**	       4: compression
**	       4: image size
**	       4: horizontal resolution
**	       4: vertical resolution
**	       4: colors in color table
**	       4: important color count
**     data:
**         pixel in rgb format (without alpha component)
**         padding added at the end of each pixel row
**         so the length of the row is a multiple of 4
*/

int     bmp_write(t_mlx *image, t_byte file_header[FILE_HEADER_SIZE],
						t_byte info_header[INFO_HEADER_SIZE])
{
	int		fd;
	t_byte	*bmp_data;

	if ((fd = open(CAPTURE_FILENAME, O_WRONLY | O_CREAT, 0644)) < 0)
		return (FALSE);
	if ((bmp_data = malloc(sizeof(unsigned char) *
			(image->screen_width * IMG_DEPTH))) == NULL)
	{
		close(fd);
		return (FALSE);
	}
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	bmp_write_pixels(fd, image, bmp_data);
	close(fd);
	return (TRUE);
}

void	bmp_write_pixels(int fd, t_mlx *mlx, t_byte *bmp_data)
{
	int		i;
	int		j;
	t_byte	padding[3];
	int		padding_size;
	int		z;
	
	
	char *image;
	//image = (int)mlx->data;
	
	image = malloc(sizeof(char) * mlx->map_height * mlx->map_width);
	int x;
	while (x++ < mlx->map_height * mlx->map_width)
		image[x] = (mlx->data[x]);

	ft_bzero(padding, 3);
	padding_size = (4 - (mlx->screen_width * IMG_DEPTH) % 4) % 4;
	i = mlx->screen_height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < mlx->screen_width)
		{
			z = mlx->data[j + (i * mlx->screen_width)];
			bmp_data[3 * j + 2] = z / (256 * 256);
			bmp_data[3 * j + 1] = (z / 256) % 256;
			bmp_data[3 * j + 0] = z % 256;
		}
		write(fd, bmp_data, mlx->screen_width * 3);
		write(fd, padding, padding_size);
	}
}

void	bmp_fill_header(t_mlx *image, t_byte file_header[FILE_HEADER_SIZE],
						t_byte info_header[INFO_HEADER_SIZE])
{
	int	file_size;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (IMG_DEPTH * image->screen_width
			+ ((4 - (image->screen_width * IMG_DEPTH) % 4) % 4)) * image->screen_height;
	ft_bzero(file_header, FILE_HEADER_SIZE);
	ft_bzero(info_header, INFO_HEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(image->screen_width);
	info_header[5] = (unsigned char)(image->screen_width >> 8);
	info_header[6] = (unsigned char)(image->screen_width >> 16);
	info_header[7] = (unsigned char)(image->screen_width >> 24);
	info_header[8] = (unsigned char)(image->screen_height);
	info_header[9] = (unsigned char)(image->screen_height >> 8);
	info_header[10] = (unsigned char)(image->screen_height >> 16);
	info_header[11] = (unsigned char)(image->screen_height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(IMG_DEPTH * 8);
}