#include "cub3d.h"

static int	parse_one_config_line(char *line, t_config *config)
{
	line = skip_spaces(line);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2))
		return (parse_texture_line(line, config));
	if (!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (parse_texture_line(line, config));
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_color_line(line, config));
	return (print_error("unknown identifier in config area"));
}

static int	validate_map_block(char **lines, int count, int start)
{
	int	i;

	i = start;
	while (i < count)
	{
		if (is_empty_line(lines[i]))
			return (print_error("empty line in map"));
		if (!is_map_line(lines[i]))
			return (print_error("invalid map block"));
		i++;
	}
	return (0);
}

int	collect_raw_map(char **lines, int count, int start, t_config *config)
{
	int	i;
	int	j;

	if (validate_map_block(lines, count, start))
		return (1);
	config->raw_map_lines = malloc(sizeof(char *) * (count - start + 1));
	if (!config->raw_map_lines)
		return (print_error("malloc failed"));
	i = start;
	j = 0;
	while (i < count)
	{
		config->raw_map_lines[j] = ft_strdup(lines[i]);
		if (!config->raw_map_lines[j])
			return (free_matrix(config->raw_map_lines),
				config->raw_map_lines = NULL, print_error("malloc failed"));
		i++;
		j++;
	}
	config->raw_map_lines[j] = NULL;
	config->map_start = start;
	return (0);
}

int	parse_elements(char **lines, int count, t_config *config)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (is_empty_line(lines[i]))
			i++;
		else if (is_config_line(lines[i]))
		{
			if (parse_one_config_line(lines[i], config))
				return (1);
			i++;
		}
		else if (!config_complete(config))
			return (print_error("map found before full config"));
		else if (is_map_line(lines[i]))
			return (collect_raw_map(lines, count, i, config));
		else
			return (print_error("unknown identifier in config area"));
	}
	if (!config_complete(config))
		return (print_error("missing texture or color identifiers"));
	return (print_error("missing map"));
}

int	parse_config_file(const char *filename, t_config *config)
{
	char	**lines;
	int		line_count;
	int		status;

	lines = NULL;
	line_count = 0;
	init_config(config);
	if (!has_cub_extension(filename))
		return (print_error("invalid file extension"));
	if (read_cub_file(filename, &lines, &line_count))
		return (1);
	status = parse_elements(lines, line_count, config);
	free_matrix(lines);
	if (status)
	{
		free_config(config);
		return (1);
	}
	return (0);
}