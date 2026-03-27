#include "cub3d.h"

static int	load_tex(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (print_error("Failed to load texture"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

int	init_textures(t_game *game)
{
	if (load_tex(game, &game->tex[TEX_NO], game->config.no_path))
		return (1);
	if (load_tex(game, &game->tex[TEX_SO], game->config.so_path))
		return (1);
	if (load_tex(game, &game->tex[TEX_WE], game->config.we_path))
		return (1);
	if (load_tex(game, &game->tex[TEX_EA], game->config.ea_path))
		return (1);
	return (0);
}
