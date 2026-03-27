#include "cub3d.h"

static void	set_step_x(t_ray *ray, t_player *p)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->x) * ray->delta_dist_x;
	}
}

static void	set_step_y(t_ray *ray, t_player *p)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->y) * ray->delta_dist_y;
	}
}

void	compute_ray_step(t_ray *ray, t_player *p)
{
	set_step_x(ray, p);
	set_step_y(ray, p);
}
