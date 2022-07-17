#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"

//gcc main.c -I../mlx_mac/ -L../mlx_mac/ -lmlx -framework OpenGL -framework AppKit

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 640
#define screenHeight 480

typedef	struct	s_data {
	void	*img;
	char	*addr;
	int		*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}



void raycast (void *mlx, void *win, int **texture)
{
	int x;
	int buffer[screenHeight][screenWidth];

	x = 0;
	t_data data;
	
	data.img = mlx_new_image(mlx, screenWidth, screenHeight);
	data.data = (int *) mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	while (x < screenWidth)
	{
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		int mapX = posX;
		int mapY = posY;

		double sideDistX;
		double sideDistY;

		// double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		// double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
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
			if(worldMap[mapX][mapY] > 0)
			{
				hit = 1;
			}
		}
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);



		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		int texNum;

		double wallX;
		if (side == 0)
		{
			texNum =  (rayDirX > 0) ? 1 : 0;
			wallX = posY + perpWallDist * rayDirY;
		}
		else
		{
			texNum =  (rayDirY < 0) ? 3 : 2;
			wallX = posX + perpWallDist * rayDirX;
		}
      	wallX -= floor((wallX));

		int texX = (int) (wallX * texWidth);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = texWidth - texX - 1;
		// if (side == 0 && rayDirX > 0)
		// 	texX = texWidth - texX - 1;
		// if (side == 1 && rayDirY < 0)
		// 	texX = texWidth - texX - 1;
		
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;


		int y = drawStart;
		while (y < drawEnd)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = texture[texNum][texHeight * texY + texX];
			if(side == 1)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
			// data.data[y * screenWidth + x] = color;
			++y;
		}
		++x;
	}
	// t_data data;
	
	// data.img = mlx_new_image(mlx, screenWidth, screenHeight);
	// data.data = (int *) mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	int y = 0;
	while (y < screenHeight)
	{
		int x = 0;
		while (x < screenWidth)
		{
			data.data[y * screenWidth + x] = buffer[y][x];
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mlx, win, data.img, 0, 0);
}

int	*xpm_to_img(void *mlx, char *path, t_data *tmp, void *win)
{
	int		size_x;
	int		size_y;
	int		*buffer;

	tmp->img = mlx_xpm_file_to_image(mlx, path, &size_x, &size_y);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	buffer = (int *)malloc(sizeof(int) * size_x * size_y);
	for (int y = 0; y < texHeight; ++y)
	{
		for (int x = 0; x < texWidth; ++x)
		{
			buffer[y * texHeight + x] = tmp->data[y * texHeight + x];
		}
	}
	mlx_destroy_image(mlx, tmp->img);
	return buffer;
}

int main(void)
{
	void *mlx;
	void *win;
	int **texture;
	t_data tmp;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3d");

	// texture = (int **)malloc(sizeof(int *) * 4);
	texture = calloc(4, sizeof(int *));

	texture[0] = xpm_to_img(mlx, "../asset/textures/wall_s.xpm", &tmp, win);
	texture[1] = xpm_to_img(mlx, "../asset/textures/wall_n.xpm", &tmp, win);
	texture[2] = xpm_to_img(mlx, "../asset/textures/wall_w.xpm", &tmp, win);
	texture[3] = xpm_to_img(mlx, "../asset/textures/wall_e.xpm", &tmp, win);



	raycast(mlx, win, texture);
	mlx_loop(mlx);


	return (0);
}