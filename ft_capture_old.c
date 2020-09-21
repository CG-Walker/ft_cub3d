/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:12:03 by cgoncalv          #+#    #+#             */
/*   Updated: 2020/09/21 16:03:38 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

#define CAPTURE_FILENAME "capture.bmp"
#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

#define t_byte unsigned char

void generateBitmapImage(unsigned char* image, t_mlx *mlx);
unsigned char* createBitmapFileHeader(t_mlx *mlx, int stride);
unsigned char* createBitmapInfoHeader(t_mlx *mlx);

int capture(t_mlx *mlx)
{
	unsigned char image[mlx->screen_width][mlx->screen_height][BYTES_PER_PIXEL];

	int i;
	int j;
	for (i = 0; i < mlx->screen_width; i++)
	{
		for (j = 0; j < mlx->screen_height; j++)
		{
			image[i][j][2] = mlx->data[i + j * mlx->screen_width] / (256*256); ///red
			image[i][j][1] = (mlx->data[i + j * mlx->screen_width] / 256) % 256; ///green
			image[i][j][0] = mlx->data[i + j * mlx->screen_width] % 256; ///blue
		}
	}
	generateBitmapImage((unsigned char*)image, mlx);
	printf("Image generated!!");
}

void generateBitmapImage (unsigned char* image, t_mlx *mlx)
{
    int widthInBytes = mlx->screen_width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(CAPTURE_FILENAME, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(mlx, stride);
    write(imageFile, fileHeader, FILE_HEADER_SIZE);

    unsigned char* infoHeader = createBitmapInfoHeader(mlx);
    write(imageFile, infoHeader, INFO_HEADER_SIZE);

    int i = mlx->screen_height;
    while (i > 0) {
        write(imageFile, image + (i*widthInBytes), mlx->screen_width);
        write(imageFile, padding, paddingSize);
        i--;
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader (t_mlx *mlx, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * mlx->screen_height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (t_mlx *mlx)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

	infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
	infoHeader[4] = (unsigned char)(mlx->screen_width);
	infoHeader[5] = (unsigned char)(mlx->screen_width >> 8);
	infoHeader[6] = (unsigned char)(mlx->screen_width >> 16);
	infoHeader[7] = (unsigned char)(mlx->screen_width >> 24);
	infoHeader[8] = (unsigned char)(mlx->screen_height);
	infoHeader[9] = (unsigned char)(mlx->screen_height >> 8);
	infoHeader[10] = (unsigned char)(mlx->screen_height >> 16);
	infoHeader[11] = (unsigned char)(mlx->screen_height >> 24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

	return (infoHeader);
}