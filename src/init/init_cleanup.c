#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img && game->mlx)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		game->tex[i].img = NULL;
		i++;
	}
}

static void	destroy_mlx(t_game *game)
{
	if (game->img.img && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->mlx = NULL;
}

static void	cleanup_all(t_game *game)
{
	destroy_textures(game);
	destroy_mlx(game);
	free_config(&game->config);
	if (game->level_name)
		free(game->level_name);
	game->level_name = NULL;
}

int	cleanup_game(t_game *game, char *msg)
{
	cleanup_all(game);
	if (msg)
		print_error(msg);
	return (1);
}

void	cleanup_exit(t_game *game)
{
	cleanup_all(game);
	exit(0);
}
