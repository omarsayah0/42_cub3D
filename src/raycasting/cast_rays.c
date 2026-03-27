#include "cub3d.h"

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(&ray, &game->player, x);
		compute_ray_step(&ray, &game->player);
		perform_dda(&ray, game->config.map);
		compute_projection(&ray);
		x++;
	}
}
