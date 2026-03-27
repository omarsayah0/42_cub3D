#include "cub3d.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
		i++;
	return (line[i] == '\0');
}

int	is_map_line(char *line)
{
	int	i;

	if (is_empty_line(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	is_config_line(char *line)
{
	line = skip_spaces(line);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (1);
	if (line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

int	config_complete(t_config *config)
{
	if (!config->no_path || !config->so_path)
		return (0);
	if (!config->we_path || !config->ea_path)
		return (0);
	if (config->floor_rgb[0] < 0 || config->floor_rgb[1] < 0)
		return (0);
	if (config->floor_rgb[2] < 0 || config->ceiling_rgb[0] < 0)
		return (0);
	if (config->ceiling_rgb[1] < 0 || config->ceiling_rgb[2] < 0)
		return (0);
	return (1);
}