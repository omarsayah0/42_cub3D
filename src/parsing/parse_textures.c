#include "cub3d.h"

static char	*trimmed_path_copy(char *str)
{
	char	*copy;
	size_t	len;
	size_t	i;

	str = skip_spaces(str);
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	if (len == 0)
		return (NULL);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static int	set_texture_path(char *id, char *path, t_config *config)
{
	char	**slot;

	slot = NULL;
	if (!ft_strncmp(id, "NO", 2))
		slot = &config->no_path;
	else if (!ft_strncmp(id, "SO", 2))
		slot = &config->so_path;
	else if (!ft_strncmp(id, "WE", 2))
		slot = &config->we_path;
	else if (!ft_strncmp(id, "EA", 2))
		slot = &config->ea_path;
	if (!slot)
		return (print_error("unknown texture identifier"));
	if (*slot)
		return (print_error("duplicate texture identifier"));
	*slot = path;
	return (0);
}

static int	parse_texture_data(char *line, int id_len, t_config *config)
{
	char	*path;

	if (line[id_len] != ' ' && line[id_len] != '\t')
		return (print_error("malformed texture line"));
	path = trimmed_path_copy(line + id_len);
	if (!path)
		return (print_error("malformed texture line"));
	if (set_texture_path(line, path, config))
	{
		free(path);
		return (1);
	}
	return (0);
}

int	parse_texture_line(char *line, t_config *config)
{
	if (!ft_strncmp(line, "NO", 2))
		return (parse_texture_data(line, 2, config));
	if (!ft_strncmp(line, "SO", 2))
		return (parse_texture_data(line, 2, config));
	if (!ft_strncmp(line, "WE", 2))
		return (parse_texture_data(line, 2, config));
	if (!ft_strncmp(line, "EA", 2))
		return (parse_texture_data(line, 2, config));
	return (print_error("unknown texture identifier"));
}