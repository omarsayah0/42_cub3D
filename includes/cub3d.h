#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define WIN_W		1280
# define WIN_H		720
# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3

# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# define MOVE_SPEED	0.05
# define ROT_SPEED	0.10

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_player_info
{
	int		*pos;
	char	*dir;
	int		*count;
}	t_player_info;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	**raw_map_lines;
	char	**map;
	int		map_start;
	size_t	width;
	size_t	height;
	int		p_pos[2];
	int		p_count;
	char	p_faced;
	t_map	map_data;
}	t_config;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	t_config	config;
	t_player	player;
	t_keys		keys;
	void		*mlx;
	void		*win;
	t_img		img;
	t_texture	tex[4];
	int			floor_color;
	int			ceil_color;
	char		*level_name;
	int			won;
	int			start_timer;
}	t_game;

char	*get_next_line(int fd);

void	init_config(t_config *config);
void	free_config(t_config *config);
void	free_matrix(char **matrix);
int		print_error(char *msg);

int		has_cub_extension(const char *filename);
int		read_cub_file(const char *filename, char ***lines, int *line_count);

char	*skip_spaces(char *str);
int		is_empty_line(const char *line);
int		is_map_line(char *line);
int		is_config_line(char *line);
int		config_complete(t_config *config);

int		parse_texture_line(char *line, t_config *config);
int		parse_color_line(char *line, t_config *config);

int		collect_raw_map(char **lines, int count,
			int start, t_config *config);
int		parse_elements(char **lines, int count, t_config *config);
int		parse_config_file(const char *filename, t_config *config);

void	drain_gnl(int fd);
int		file_validation(t_config *config);
int		map_validation(t_config *config);
int		color_validation(t_config *config);
int		path_validation(t_config *config);
int		flood_fill(char **map, int x, int y);
size_t	getm_length(char **matrix);
char	**build_padded_map(char **raw_lines, size_t width, int *p_pos,
			char *p_dir);
int		check_map_validity(char **map, int x, int y);
int		check_characters(char **map);

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_wall
{
	int		tex_idx;
	int		tex_x;
	double	tex_pos;
	double	step;
}	t_wall;

void	init_game_structs(t_game *game);
int		init_player(t_game *game);
int		init_mlx(t_game *game);
int		init_textures(t_game *game);
int		init_game(t_game *game, t_config *config);
int		cleanup_game(t_game *game, char *msg);
void	cleanup_exit(t_game *game);

void	init_ray(t_ray *ray, t_player *p, int x);
void	compute_ray_step(t_ray *ray, t_player *p);
void	perform_dda(t_ray *ray, char **map);
void	compute_projection(t_ray *ray);
void	cast_rays(t_game *game);

void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_pixel(t_texture *tex, int x, int y);
void	draw_background(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);
void	render_frame(t_game *game);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	update_movement(t_game *game);
void	update_rotation(t_game *game);
void	start_game(t_game *game);

#endif
