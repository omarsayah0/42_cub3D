#include "cub3d_bonus.h"

static void	render_column(t_game *game, int x)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	init_ray(&ray, &game->player, x);
	compute_ray_step(&ray, &game->player);
	perform_dda_bonus(&ray, game);
	compute_projection(&ray);
	zbuf_access()[x] = ray.perp_wall_dist;
	if (game->config.map[ray.map_y][ray.map_x] == 'D')
		draw_door_wall(game, &ray, x);
	else
		draw_wall(game, &ray, x);
}

static void	render_sprites(t_game *game)
{
	int			i;
	t_coin_mgr	*m;
	t_texture	*tex;

	m = get_coin_mgr();
	tex = get_coin_frame_tex();
	i = 0;
	while (i < m->count)
	{
		if (!m->arr[i].collected)
			render_coin(game, &m->arr[i], tex);
		i++;
	}
}

static void	draw_start_screen(t_game *game)
{
	int	y;

	y = WIN_H / 2 - 20;
	if (game->level_name)
		mlx_string_put(game->mlx, game->win,
			WIN_W / 2 - 20, y, 0xFFFFFF, game->level_name);
	mlx_string_put(game->mlx, game->win, WIN_W / 2 - 152, y + 30,
		0xFFD700, "Mission: Collect all the collectibles!");
	game->start_timer--;
}

static void	draw_win_screen(t_game *game)
{
	mlx_string_put(game->mlx, game->win,
		WIN_W / 2 - 100, WIN_H / 2 - 10,
		0xFFD700, "Congratulations! You Won! press ESC to quit.");
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
	render_sprites(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->start_timer > 0)
		draw_start_screen(game);
	if (game->won)
		draw_win_screen(game);
}
