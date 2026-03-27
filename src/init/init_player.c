#include "cub3d.h"

static void	set_north(t_player *p)
{
	p->dir_x = 0.0;
	p->dir_y = -1.0;
	p->plane_x = 0.66;
	p->plane_y = 0.0;
}

static void	set_south(t_player *p)
{
	p->dir_x = 0.0;
	p->dir_y = 1.0;
	p->plane_x = -0.66;
	p->plane_y = 0.0;
}

static void	set_east(t_player *p)
{
	p->dir_x = 1.0;
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = 0.66;
}

static void	set_west(t_player *p)
{
	p->dir_x = -1.0;
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = -0.66;
}

int	init_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->x = (double)game->config.p_pos[0] + 0.5;
	p->y = (double)game->config.p_pos[1] + 0.5;
	if (game->config.p_faced == 'N')
		set_north(p);
	else if (game->config.p_faced == 'S')
		set_south(p);
	else if (game->config.p_faced == 'E')
		set_east(p);
	else
		set_west(p);
	return (0);
}
