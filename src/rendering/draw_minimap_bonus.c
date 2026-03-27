#include "cub3d_bonus.h"

static int	get_tile_color(char **map, int mx, int my, int h)
{
	if (my < 0 || my >= h || mx < 0)
		return (MM_VOID);
	if (!map[my] || mx >= (int)ft_strlen(map[my]))
		return (MM_VOID);
	if (map[my][mx] == '1')
		return (MM_WALL);
	if (map[my][mx] == 'D')
		return (MM_DOOR);
	if (map[my][mx] == 'C')
		return (MM_COIN);
	return (MM_FLOOR);
}

static void	draw_tile(t_img *img, int sx, int sy, int color)
{
	int	py;
	int	px;

	py = 0;
	while (py < MM_TILE)
	{
		px = 0;
		while (px < MM_TILE)
		{
			if (sx + px >= 0 && sx + px < WIN_W
				&& sy + py >= 0 && sy + py < WIN_H)
				put_pixel(img, sx + px, sy + py, color);
			px++;
		}
		py++;
	}
}

static void	draw_mm_tiles(t_game *g, t_minimap *mm)
{
	int	dy;
	int	dx;
	int	color;

	dy = -MM_RADIUS;
	while (dy <= MM_RADIUS)
	{
		dx = -MM_RADIUS;
		while (dx <= MM_RADIUS)
		{
			color = get_tile_color(g->config.map, mm->pmx + dx,
					mm->pmy + dy, (int)g->config.map_data.height);
			draw_tile(&g->img, mm->cx + dx * MM_TILE,
					mm->cy + dy * MM_TILE, color);
			dx++;
		}
		dy++;
	}
}

static void	draw_mm_marker(t_img *img, t_player *p, int cx, int cy)
{
	double	t;
	int		px;
	int		py;

	t = 1.0;
	while (t <= MM_LINE)
	{
		px = cx + (int)(t * p->dir_x);
		py = cy + (int)(t * p->dir_y);
		if (px >= 0 && px < WIN_W && py >= 0 && py < WIN_H)
			put_pixel(img, px, py, MM_DIR);
		t += 0.5;
	}
	put_pixel(img, cx, cy, MM_PLAYER);
	put_pixel(img, cx - 1, cy, MM_PLAYER);
	put_pixel(img, cx + 1, cy, MM_PLAYER);
	put_pixel(img, cx, cy - 1, MM_PLAYER);
	put_pixel(img, cx, cy + 1, MM_PLAYER);
}

void	draw_minimap(t_game *game)
{
	t_minimap	mm;

	mm.pmx = (int)game->player.x;
	mm.pmy = (int)game->player.y;
	mm.cx = MM_X + MM_RADIUS * MM_TILE;
	mm.cy = MM_Y + MM_RADIUS * MM_TILE;
	draw_mm_tiles(game, &mm);
	draw_mm_marker(&game->img, &game->player,
			mm.cx + MM_TILE / 2, mm.cy + MM_TILE / 2);
}
