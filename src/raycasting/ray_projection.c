#include "cub3d.h"

static void	clamp_draw_bounds(t_ray *ray)
{
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

void	compute_projection(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + WIN_H / 2;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	clamp_draw_bounds(ray);
}
