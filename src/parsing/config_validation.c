#include "cub3d.h"

static int	has_xpm_extension(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (!ft_strncmp(path + len - 4, ".xpm", 4));
}

static int	validate_one_texture(char *path, char *msg)
{
	if (!path)
		return (print_error("missing texture path"));
	if (!has_xpm_extension(path))
		return (print_error("texture file must have .xpm extension"));
	if (access(path, F_OK) == -1)
		return (print_error(msg));
	if (access(path, R_OK) == -1)
		return (print_error("texture file is not readable"));
	return (0);
}

int	color_validation(t_config *config)
{
	if (config->floor_rgb[0] < 0 || config->floor_rgb[0] > 255
		|| config->floor_rgb[1] < 0 || config->floor_rgb[1] > 255
		|| config->floor_rgb[2] < 0 || config->floor_rgb[2] > 255)
		return (print_error("Floor RGB values must be between 0 and 255"));
	if (config->ceiling_rgb[0] < 0 || config->ceiling_rgb[0] > 255
		|| config->ceiling_rgb[1] < 0 || config->ceiling_rgb[1] > 255
		|| config->ceiling_rgb[2] < 0 || config->ceiling_rgb[2] > 255)
		return (print_error("Ceiling RGB values must be between 0 and 255"));
	return (0);
}

int	path_validation(t_config *config)
{
	if (validate_one_texture(config->no_path, "North texture file not found"))
		return (1);
	if (validate_one_texture(config->so_path, "South texture file not found"))
		return (1);
	if (validate_one_texture(config->we_path, "West texture file not found"))
		return (1);
	if (validate_one_texture(config->ea_path, "East texture file not found"))
		return (1);
	return (0);
}