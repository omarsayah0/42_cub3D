#include "cub3d_bonus.h"

int	key_press_bonus(int keycode, t_game *game)
{
	if (keycode == KEY_E)
		try_open_door(game);
	key_press(keycode, game);
	return (0);
}
