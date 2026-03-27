#include "cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (flood_fill(map, x + 1, y))
		return (1);
	if (flood_fill(map, x - 1, y))
		return (1);
	if (flood_fill(map, x, y + 1))
		return (1);
	if (flood_fill(map, x, y - 1))
		return (1);
	return (0);
}

int	check_map_validity(char **map, int x, int y)
{
	if (flood_fill(map, x, y))
	{
		print_error("Map is not enclosed by walls");
		return (0);
	}
	return (1);
}