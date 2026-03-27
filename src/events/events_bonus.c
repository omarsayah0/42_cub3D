#include "cub3d_bonus.h"

static int	win_close(t_game *game)
{
	cleanup_door_tex(game);
	cleanup_coins(game);
	cleanup_exit(game);
	return (0);
}

static int	game_loop(t_game *game)
{
	update_movement(game);
	update_rotation(game);
	update_doors(game);
	update_coins(game);
	render_frame(game);
	return (0);
}

void	start_game(t_game *game)
{
	init_doors(game);
	load_door_tex(game);
	init_coins(game);
	mlx_hook(game->win, 2, 1L << 0, key_press_bonus, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 17, 0, win_close, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
