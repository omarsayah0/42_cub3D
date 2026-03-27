#include "cub3d.h"

static const char	*get_basename(const char *path)
{
	const char	*last;

	last = path;
	while (*path)
	{
		if (*path == '/')
			last = path + 1;
		path++;
	}
	return (last);
}

static char	*extract_level_name(const char *path)
{
	const char	*base;
	const char	*start;
	const char	*end;
	char		*result;
	size_t		len;

	base = get_basename(path);
	start = ft_strchr(base, '_');
	if (!start)
		return (ft_strdup(base));
	start++;
	end = ft_strchr(start, '.');
	if (!end)
		return (ft_strdup(start));
	len = (size_t)(end - start);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_game		game;

	if (argc != 2)
		return (print_error("Usage: ./cub3D map.cub"));
	if (parse_config_file(argv[1], &config))
		return (1);
	if (file_validation(&config))
		return (1);
	if (init_game(&game, &config))
		return (1);
	game.level_name = extract_level_name(argv[1]);
	game.start_timer = 180;
	start_game(&game);
	return (0);
}
