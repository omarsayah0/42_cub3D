#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
	config->floor_rgb[0] = -1;
	config->floor_rgb[1] = -1;
	config->floor_rgb[2] = -1;
	config->ceiling_rgb[0] = -1;
	config->ceiling_rgb[1] = -1;
	config->ceiling_rgb[2] = -1;
	config->raw_map_lines = NULL;
	config->map = NULL;
	config->map_start = -1;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_config(t_config *config)
{
	free(config->no_path);
	free(config->so_path);
	free(config->we_path);
	free(config->ea_path);
	free_matrix(config->raw_map_lines);
	free_matrix(config->map);
	config->map = NULL;
	config->map_data.grid = NULL;
	init_config(config);
}

int	print_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}