#include "cub3d.h"

static void	set_key(t_keys *keys, int keycode, int state)
{
	if (keycode == KEY_W)
		keys->w = state;
	else if (keycode == KEY_A)
		keys->a = state;
	else if (keycode == KEY_S)
		keys->s = state;
	else if (keycode == KEY_D)
		keys->d = state;
	else if (keycode == KEY_LEFT)
		keys->left = state;
	else if (keycode == KEY_RIGHT)
		keys->right = state;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		cleanup_exit(game);
	set_key(&game->keys, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	set_key(&game->keys, keycode, 0);
	return (0);
}
