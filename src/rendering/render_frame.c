#include "cub3d.h"

static void	render_column(t_game *game, int x)
{
	t_ray	ray;

	init_ray(&ray, &game->player, x);
	compute_ray_step(&ray, &game->player);
	perform_dda(&ray, game->config.map);
	compute_projection(&ray);
	draw_wall(game, &ray, x);
}

void	render_frame(t_game *game)
{
	int	x;

	draw_background(game);
	x = 0;
	while (x < WIN_W)
	{
		render_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
