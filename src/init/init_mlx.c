#include "cub3d.h"

static int	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		return (print_error("Window creation failed"));
	return (0);
}

static int	create_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img.img)
		return (print_error("Image creation failed"));
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("MLX init failed"));
	if (create_window(game))
		return (1);
	if (create_image(game))
		return (1);
	return (0);
}
