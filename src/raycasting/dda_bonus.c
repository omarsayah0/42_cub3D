#include "cub3d_bonus.h"

static double	get_pwd(t_ray *ray)
{
	if (ray->side == 0)
		return (ray->side_dist_x - ray->delta_dist_x);
	return (ray->side_dist_y - ray->delta_dist_y);
}

static double	get_hit_wall_x(t_ray *ray, t_player *p)
{
	double	pwd;
	double	wall_x;

	pwd = get_pwd(ray);
	if (ray->side == 0)
		wall_x = p->y + pwd * ray->ray_dir_y;
	else
		wall_x = p->x + pwd * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

static int	door_blocks(t_ray *ray, t_game *game)
{
	t_door	*door;
	double	wall_x;

	door = get_door_at(ray->map_x, ray->map_y);
	if (!door)
		return (1);
	wall_x = get_hit_wall_x(ray, &game->player);
	return (wall_x > door->open);
}

static int	is_solid(t_ray *ray, t_game *game)
{
	char	c;

	c = game->config.map[ray->map_y][ray->map_x];
	if (c == '1')
		return (1);
	if (c == 'D')
		return (door_blocks(ray, game));
	return (0);
}

void	perform_dda_bonus(t_ray *ray, t_game *game)
{
	while (!is_solid(ray, game))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}
