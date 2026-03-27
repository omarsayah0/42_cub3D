#include "cub3d.h"

static void	set_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	init_ray(t_ray *ray, t_player *p, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_dir_x = p->dir_x + p->plane_x * ray->camera_x;
	ray->ray_dir_y = p->dir_y + p->plane_y * ray->camera_x;
	ray->map_x = (int)p->x;
	ray->map_y = (int)p->y;
	set_delta_dist(ray);
}
