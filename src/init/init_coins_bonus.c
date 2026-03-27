#include "cub3d_bonus.h"

t_coin_mgr	*get_coin_mgr(void)
{
	static t_coin_mgr	mgr;

	return (&mgr);
}

void	cleanup_coins(t_game *game)
{
	int	i;

	i = 0;
	while (i < COIN_FRAMES)
	{
		if (get_coin_mgr()->frames[i].img && game->mlx)
			mlx_destroy_image(game->mlx, get_coin_mgr()->frames[i].img);
		get_coin_mgr()->frames[i].img = NULL;
		i++;
	}
}

static char	*build_coin_path(int n)
{
	char	*num;
	char	*tmp;
	char	*path;

	num = ft_itoa(n);
	if (!num)
		return (NULL);
	tmp = ft_strjoin("textures/collectable/collectable_", num);
	free(num);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, ".xpm");
	free(tmp);
	return (path);
}

static void	load_coin_frames(t_game *game)
{
	t_coin_mgr	*m;
	char		*path;
	int			i;

	m = get_coin_mgr();
	i = 0;
	while (i < COIN_FRAMES)
	{
		path = build_coin_path(i + 1);
		if (!path)
			cleanup_exit(game);
		m->frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&m->frames[i].width, &m->frames[i].height);
		free(path);
		if (!m->frames[i].img)
			cleanup_exit(game);
		m->frames[i].addr = mlx_get_data_addr(m->frames[i].img,
				&m->frames[i].bpp, &m->frames[i].line_len,
				&m->frames[i].endian);
		i++;
	}
}

void	init_coins(t_game *game)
{
	t_coin_mgr	*m;
	int			y;
	int			x;

	m = get_coin_mgr();
	y = 0;
	while (y < (int)game->config.map_data.height)
	{
		x = 0;
		while (game->config.map[y][x] && m->count < MAX_COINS)
		{
			if (game->config.map[y][x] == 'C')
			{
				m->arr[m->count].x = x;
				m->arr[m->count].y = y;
				m->arr[m->count].collected = 0;
				m->count++;
			}
			x++;
		}
		y++;
	}
	load_coin_frames(game);
}
