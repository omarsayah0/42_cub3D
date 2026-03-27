#include "cub3d_bonus.h"

static int	is_blocked(t_game *game, int mx, int my)
{
	char	tile;
	t_door	*door;

	tile = game->config.map[my][mx];
	if (tile == '1')
		return (1);
	if (tile == 'D')
	{
		door = get_door_at(mx, my);
		if (!door || door->open < 1.0)
			return (1);
	}
	return (0);
}

static void	apply_move(t_game *game, double dx, double dy)
{
	t_player	*p;

	p = &game->player;
	if (!is_blocked(game, (int)(p->x + dx), (int)p->y))
		p->x += dx;
	if (!is_blocked(game, (int)p->x, (int)(p->y + dy)))
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
