#include "cub3d_bonus.h"

double	*zbuf_access(void)
{
	static double	zbuf[WIN_W];

	return (zbuf);
}

static void	clamp_sprite_bounds(t_sprite *sp)
{
	if (sp->y0 < 0)
		sp->y0 = 0;
	if (sp->y1 >= WIN_H)
		sp->y1 = WIN_H - 1;
	if (sp->x0 < 0)
		sp->x0 = 0;
	if (sp->x1 >= WIN_W)
		sp->x1 = WIN_W - 1;
}

static int	init_sprite(t_player *p, t_coin *c, t_sprite *sp)
{
	double	sx;
	double	sy;
	double	inv;

	sx = c->x + 0.5 - p->x;
	sy = c->y + 0.5 - p->y;
	inv = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	sp->tz = inv * (-p->plane_y * sx + p->plane_x * sy);
	if (sp->tz <= 0.2)
		return (0);
	sp->h = abs((int)(WIN_H / sp->tz));
	sp->sx = (int)(WIN_W / 2.0
			* (1.0 + inv * (p->dir_y * sx - p->dir_x * sy) / sp->tz));
	sp->y0 = -sp->h / 2 + WIN_H / 2;
	sp->y1 = sp->h / 2 + WIN_H / 2;
	sp->x0 = -sp->h / 2 + sp->sx;
	sp->x1 = sp->h / 2 + sp->sx;
	clamp_sprite_bounds(sp);
	return (1);
}

static void	draw_sprite_col(t_game *g, t_texture *tex, t_sprite *sp,
				int stripe)
{
	int	tex_x;
	int	y;
	int	tex_y;
	int	color;

	tex_x = (stripe - (-sp->h / 2 + sp->sx)) * tex->width / sp->h;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	y = sp->y0;
	while (y <= sp->y1)
	{
		tex_y = (y - WIN_H / 2 + sp->h / 2) * tex->height / sp->h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_tex_pixel(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(&g->img, stripe, y, color);
		y++;
	}
}

void	render_coin(t_game *game, t_coin *coin, t_texture *tex)
{
	t_sprite	sp;
	int			stripe;

	if (!init_sprite(&game->player, coin, &sp))
		return ;
	stripe = sp.x0;
	while (stripe <= sp.x1)
	{
		if (sp.tz < zbuf_access()[stripe])
			draw_sprite_col(game, tex, &sp, stripe);
		stripe++;
	}
}
