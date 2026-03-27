#include "cub3d.h"

int	file_validation(t_config *config)
{
	if (path_validation(config) || color_validation(config))
	{
		free_config(config);
		return (1);
	}
	if (map_validation(config))
	{
		free_config(config);
		return (1);
	}
	return (0);
}
