#include "cub3d.h"

static int	parse_rgb_value(char **str, int *value)
{
	int	result;

	*str = skip_spaces(*str);
	if (!ft_isdigit(**str))
		return (0);
	result = 0;
	while (ft_isdigit(**str))
	{
		result = (result * 10) + (**str - '0');
		if (result > 255)
			return (0);
		(*str)++;
	}
	*value = result;
	*str = skip_spaces(*str);
	return (1);
}

static int	parse_rgb_string(char *str, int rgb[3])
{
	int		i;

	str = skip_spaces(str);
	i = 0;
	while (i < 3)
	{
		if (!parse_rgb_value(&str, &rgb[i]))
			return (0);
		if (i < 2)
		{
			if (*str != ',')
				return (0);
			str++;
		}
		i++;
	}
	str = skip_spaces(str);
	return (*str == '\0');
}

static int	set_color_value(char id, int rgb[3], t_config *config)
{
	int	*target;

	if (id == 'F')
		target = config->floor_rgb;
	else if (id == 'C')
		target = config->ceiling_rgb;
	else
		return (print_error("unknown color identifier"));
	if (target[0] != -1 || target[1] != -1 || target[2] != -1)
		return (print_error("duplicate color identifier"));
	target[0] = rgb[0];
	target[1] = rgb[1];
	target[2] = rgb[2];
	return (0);
}

int	parse_color_line(char *line, t_config *config)
{
	int		rgb[3];

	if ((line[0] != 'F' && line[0] != 'C')
		|| (line[1] != ' ' && line[1] != '\t'))
		return (print_error("malformed color line"));
	if (!parse_rgb_string(line + 1, rgb))
		return (print_error("invalid RGB syntax"));
	return (set_color_value(line[0], rgb, config));
}