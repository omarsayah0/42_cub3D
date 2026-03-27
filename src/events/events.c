#include "cub3d.h"

static int	win_close(t_game *game)
{
	cleanup_exit(game);
	return (0);
}

static int	game_loop(t_game *game)
{
	update_movement(game);
	update_rotation(game);
	render_frame(game);
	return (0);
}

void	start_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, win_close, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
