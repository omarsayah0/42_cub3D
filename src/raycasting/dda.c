#include "cub3d.h"

static int	hit_wall(char **map, int x, int y)
{
	return (map[y][x] == '1');
}

void	perform_dda(t_ray *ray, char **map)
{
	while (!hit_wall(map, ray->map_x, ray->map_y))
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
