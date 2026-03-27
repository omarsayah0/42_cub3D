#include "cub3d_bonus.h"

t_texture	*get_coin_frame_tex(void)
{
	t_coin_mgr	*m;

	m = get_coin_mgr();
	return (&m->frames[m->frame]);
}

static void	check_collect(t_game *game, t_coin *coin)
{
	double	dx;
	double	dy;

	dx = game->player.x - (coin->x + 0.5);
	dy = game->player.y - (coin->y + 0.5);
	if (dx * dx + dy * dy < COIN_COLLECT_DIST * COIN_COLLECT_DIST)
	{
		coin->collected = 1;
		game->config.map[coin->y][coin->x] = '0';
	}
}

static void	check_win(t_game *game, t_coin_mgr *m)
{
	int	i;

	if (game->won || m->count == 0)
		return ;
	i = 0;
	while (i < m->count)
	{
		if (!m->arr[i].collected)
			return ;
		i++;
	}
	game->won = 1;
}

void	update_coins(t_game *game)
{
	int			i;
	t_coin_mgr	*m;

	m = get_coin_mgr();
	m->timer++;
	if (m->timer >= COIN_ANIM_SPEED)
	{
		m->timer = 0;
		m->frame = (m->frame + 1) % COIN_FRAMES;
	}
	i = 0;
	while (i < m->count)
	{
		if (!m->arr[i].collected)
			check_collect(game, &m->arr[i]);
		i++;
	}
	check_win(game, m);
}
