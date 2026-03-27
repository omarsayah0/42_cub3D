#include "cub3d.h"

static void	apply_move(t_game *game, double dx, double dy)
{
	t_player	*p;
	char		**map;

	p = &game->player;
	map = game->config.map;
	if (map[(int)p->y][(int)(p->x + dx)] != '1')
		p->x += dx;
	if (map[(int)(p->y + dy)][(int)p->x] != '1')
		p->y += dy;
}

void	update_movement(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (game->keys.w)
		apply_move(game, p->dir_x * MOVE_SPEED, p->dir_y * MOVE_SPEED);
	if (game->keys.s)
		apply_move(game, -p->dir_x * MOVE_SPEED, -p->dir_y * MOVE_SPEED);
	if (game->keys.a)
		apply_move(game, p->dir_y * MOVE_SPEED, -p->dir_x * MOVE_SPEED);
	if (game->keys.d)
		apply_move(game, -p->dir_y * MOVE_SPEED, p->dir_x * MOVE_SPEED);
}
