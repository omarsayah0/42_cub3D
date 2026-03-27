#include "cub3d.h"

static void	fill_row(t_img *img, int y, int color)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		put_pixel(img, x, y, color);
		x++;
	}
}

void	draw_background(t_game *game)
{
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		fill_row(&game->img, y, game->ceil_color);
		y++;
	}
	while (y < WIN_H)
	{
		fill_row(&game->img, y, game->floor_color);
		y++;
	}
}
