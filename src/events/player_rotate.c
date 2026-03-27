#include "cub3d.h"

static void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	update_rotation(t_game *game)
{
	if (game->keys.left)
		rotate_player(&game->player, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(&game->player, ROT_SPEED);
}
