#include "cub3d.h"

size_t	getm_length(char **matrix)
{
	size_t	len;
	size_t	m_len;
	size_t	line_len;

	len = 0;
	m_len = 0;
	while (matrix[len])
	{
		line_len = ft_strlen(matrix[len]);
		if (line_len > 0 && matrix[len][line_len - 1] == '\n')
			line_len--;
		if (line_len > m_len)
			m_len = line_len;
		len++;
	}
	return (m_len);
}

int	check_characters(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != 'D' && c != 'C')
				return (print_error("Invalid character in map"));
			j++;
		}
		i++;
	}
	return (0);
}

static int	run_map_checks(char **temp_map, t_config *config)
{
	if (check_characters(temp_map))
	{
		free_matrix(temp_map);
		return (1);
	}
	if (!check_map_validity(temp_map, config->p_pos[0], config->p_pos[1]))
	{
		free_matrix(temp_map);
		return (1);
	}
	free_matrix(temp_map);
	return (0);
}

static int	set_map_data(t_config *config)
{
	size_t	i;

	config->map = build_padded_map(config->raw_map_lines, config->width,
			config->p_pos, &config->p_faced);
	if (!config->map)
		return (1);
	config->map_data.grid = config->map;
	config->map_data.width = config->width;
	i = 0;
	while (config->map[i])
		i++;
	config->map_data.height = i;
	return (0);
}

int	map_validation(t_config *config)
{
	size_t	max_len;
	char	**temp_map;

	if (config->raw_map_lines == NULL)
		return (print_error("missing map"));
	max_len = getm_length(config->raw_map_lines);
	config->width = max_len;
	config->height = 0;
	temp_map = build_padded_map(config->raw_map_lines, config->width,
			config->p_pos, &config->p_faced);
	if (!temp_map)
		return (1);
	if (run_map_checks(temp_map, config))
		return (1);
	return (set_map_data(config));
}
