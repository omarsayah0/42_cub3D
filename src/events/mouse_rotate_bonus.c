#include "cub3d_bonus.h"

static void	apply_rotation(t_player *p, double angle)
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

int	mouse_move(int x, int y, t_game *game)
{
	static int	warping = 0;
	int			dx;

	(void)y;
	if (warping)
	{
		warping = 0;
		return (0);
	}
	dx = x - WIN_W / 2;
	if (dx == 0)
		return (0);
	apply_rotation(&game->player, dx * MOUSE_SPEED);
	warping = 1;
	mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	mlx_do_sync(game->mlx);
	return (0);
}
