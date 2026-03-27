#include "cub3d_bonus.h"

static void	update_one_door(t_door *d, int px, int py)
{
	if (d->opening == -1 && px == d->x && py == d->y)
		d->opening = 1;
	d->open += d->opening * DOOR_SPEED;
	if (d->open >= 1.0)
	{
		d->open = 1.0;
		d->opening = 0;
	}
	if (d->open <= 0.0)
	{
		d->open = 0.0;
		d->opening = 0;
	}
	if (d->open >= 1.0 && d->opening == 0)
	{
		if (px == d->x && py == d->y)
			d->wait = DOOR_WAIT;
		else if (d->wait == 0)
			d->wait = DOOR_WAIT;
		else if (--(d->wait) == 0)
			d->opening = -1;
	}
}

void	update_doors(t_game *game)
{
	int		i;
	int		px;
	int		py;

	px = (int)game->player.x;
	py = (int)game->player.y;
	i = 0;
	while (i < get_door_mgr()->count)
	{
		update_one_door(&get_door_mgr()->arr[i], px, py);
		i++;
	}
}
