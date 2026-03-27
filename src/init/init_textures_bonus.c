#include "cub3d_bonus.h"

static t_texture	*door_tex(void)
{
	static t_texture	tex;

	return (&tex);
}

t_texture	*get_door_tex(void)
{
	return (door_tex());
}

void	load_door_tex(t_game *game)
{
	door_tex()->img = mlx_xpm_file_to_image(game->mlx, DOOR_TEX,
			&door_tex()->width, &door_tex()->height);
	if (!door_tex()->img)
	{
		ft_putstr_fd("Error: Failed to load door texture\n", 2);
		cleanup_exit(game);
	}
	door_tex()->addr = mlx_get_data_addr(door_tex()->img,
			&door_tex()->bpp, &door_tex()->line_len, &door_tex()->endian);
}

void	cleanup_door_tex(t_game *game)
{
	if (door_tex()->img && game->mlx)
		mlx_destroy_image(game->mlx, door_tex()->img);
	door_tex()->img = NULL;
}
