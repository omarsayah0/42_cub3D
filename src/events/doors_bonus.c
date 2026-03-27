#include "cub3d_bonus.h"

t_door_mgr	*get_door_mgr(void)
{
	static t_door_mgr	mgr;

	return (&mgr);
}

t_door	*get_door_at(int x, int y)
{
	int	i;

	i = 0;
	while (i < get_door_mgr()->count)
	{
		if (get_door_mgr()->arr[i].x == x && get_door_mgr()->arr[i].y == y)
			return (&get_door_mgr()->arr[i]);
		i++;
	}
	return (NULL);
}

void	init_doors(t_game *game)
{
	int	y;
	int	x;
	int	h;

	h = game->config.map_data.height;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (game->config.map[y][x] && get_door_mgr()->count < MAX_DOORS)
		{
			if (game->config.map[y][x] == 'D')
			{
				get_door_mgr()->arr[get_door_mgr()->count].x = x;
				get_door_mgr()->arr[get_door_mgr()->count].y = y;
				get_door_mgr()->arr[get_door_mgr()->count].open = 0.0;
				get_door_mgr()->arr[get_door_mgr()->count].opening = 0;
				get_door_mgr()->arr[get_door_mgr()->count].wait = 0;
				get_door_mgr()->count++;
			}
			x++;
		}
		y++;
	}
}

void	try_open_door(t_game *game)
{
	int		tx;
	int		ty;
	t_door	*door;

	tx = (int)(game->player.x + game->player.dir_x * 1.2);
	ty = (int)(game->player.y + game->player.dir_y * 1.2);
	door = get_door_at(tx, ty);
	if (!door)
	{
		tx = (int)(game->player.x + game->player.dir_x * 2.0);
		ty = (int)(game->player.y + game->player.dir_y * 2.0);
		door = get_door_at(tx, ty);
	}
	if (!door)
		return ;
	door->wait = 0;
	if (door->opening == 0 && door->open < 0.01)
		door->opening = 1;
	else if (door->opening == 0 && door->open > 0.99)
		door->opening = -1;
	else
		door->opening = -door->opening;
}
