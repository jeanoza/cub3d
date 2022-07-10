#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"

//gcc main.c -I../mlx_mac/ -L../mlx_mac/ -lmlx -framework OpenGL -framework AppKit

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

typedef	struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_player {
	int		x;
	int		y;
}	t_player;

typedef struct	s_game {
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	char		**map;
	t_player	*player;
}	t_game;


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


void raycast (void *mlx, void *win)
{
	int x;

	x = 0;
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
			if(worldMap[mapX][mapY] > 0) hit = 1;
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

		int color = 0;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = encode_rgb(255, 0, 0);    break; //red
			case 2:  color = encode_rgb(0, 255, 0);  break; //green
			case 3:  color = encode_rgb(0, 0, 255);   break; //blue
			case 4:  color = encode_rgb(255, 255, 255);  break; //white
			default: color = encode_rgb(255, 255, 0); break; //yellow
		}

		if (side == 1) color = color / 2;

		t_data data;
		
		data.img = mlx_new_image(mlx, screenWidth, screenHeight);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);


		int _y = drawStart;
		while (_y < drawEnd)
		{
			mlx_pixel_put(mlx, win, x, _y, color);
			++_y;
		}
		++x;
	}
}

void copy_map_into_game(t_game *game)
{
	int y;
	int x;
	y = 0;
	while (y < mapHeight)
	{
		x = 0;
		while (x < mapWidth)
		{
			printf("%d ", worldMap[y][x]);
			game->map[y][x] = worldMap[y][x] + '0';
			++x;
		}
		++y;
	}
}

int main(void)
{
	t_game *game;

	game = calloc(1, sizeof(game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->map = calloc(mapHeight, 8);
	// copy_map_into_game(game);
	// int y;
	// int x;
	// y = 0;
	// while (y < mapHeight)
	// {
	// 	x = 0;
	// 	while (x < mapWidth)
	// 	{
	// 		printf("%c\n", game->map[y][x]);
	// 		++x;
	// 	}
	// 	printf("\n");
	// 	++y;
	// }

	// raycast(game);
	// mlx_loop(mlx);



	return (0);
}