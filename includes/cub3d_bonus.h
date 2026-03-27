#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

# define MOUSE_SPEED	0.009

# define MM_TILE	12
# define MM_RADIUS	5
# define MM_X		1138
# define MM_Y		10
# define MM_WALL	0x555555
# define MM_FLOOR	0xAAAAAA
# define MM_VOID	0x111111
# define MM_PLAYER	0xFF0000
# define MM_DIR		0xFFFF00
# define MM_LINE	10
# define MM_DOOR	0xFF8800

# define KEY_E		101
# define MAX_DOORS	64
# define DOOR_SPEED	0.04
# define DOOR_WAIT	150
# define DOOR_TEX	"textures/output_Door.xpm"

# define MM_COIN		0xFFD700
# define MAX_COINS		64
# define COIN_FRAMES	27
# define COIN_ANIM_SPEED	8
# define COIN_COLLECT_DIST	0.8

typedef struct s_minimap
{
	int	cx;
	int	cy;
	int	pmx;
	int	pmy;
}	t_minimap;

typedef struct s_door
{
	int		x;
	int		y;
	double	open;
	int		opening;
	int		wait;
}	t_door;

typedef struct s_door_mgr
{
	t_door	arr[MAX_DOORS];
	int		count;
}	t_door_mgr;

typedef struct s_coin
{
	int	x;
	int	y;
	int	collected;
}	t_coin;

typedef struct s_coin_mgr
{
	t_coin		arr[MAX_COINS];
	int			count;
	t_texture	frames[COIN_FRAMES];
	int			frame;
	int			timer;
}	t_coin_mgr;

typedef struct s_sprite
{
	double	tz;
	int		sx;
	int		h;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
}	t_sprite;

void		draw_minimap(t_game *game);
int			mouse_move(int x, int y, t_game *game);

t_door_mgr	*get_door_mgr(void);
t_door		*get_door_at(int x, int y);
void		init_doors(t_game *game);
void		update_doors(t_game *game);
void		try_open_door(t_game *game);

t_texture	*get_door_tex(void);
void		load_door_tex(t_game *game);
void		cleanup_door_tex(t_game *game);

void		perform_dda_bonus(t_ray *ray, t_game *game);
void		draw_door_wall(t_game *game, t_ray *ray, int x);
int			key_press_bonus(int keycode, t_game *game);

t_coin_mgr	*get_coin_mgr(void);
void		init_coins(t_game *game);
void		cleanup_coins(t_game *game);
t_texture	*get_coin_frame_tex(void);
void		update_coins(t_game *game);
double		*zbuf_access(void);
void		render_coin(t_game *game, t_coin *coin, t_texture *tex);

#endif
