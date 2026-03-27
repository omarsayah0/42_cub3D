#include "cub3d.h"

static char	*make_empty_line(size_t width)
{
	char	*line;
	size_t	i;

	line = malloc(width + 3);
	if (!line)
		return (NULL);
	i = 0;
	while (i < width + 2)
		line[i++] = ' ';
	line[i] = '\0';
	return (line);
}

static char	*make_content_line(char *raw, size_t width,
		t_player_info *p_info, size_t row)
{
	char	*line;
	size_t	j;

	line = malloc(width + 3);
	if (!line)
		return (NULL);
	line[0] = ' ';
	j = 0;
	while (raw[j] && raw[j] != '\n')
	{
		line[j + 1] = raw[j];
		if (raw[j] == 'N' || raw[j] == 'S' || raw[j] == 'E' || raw[j] == 'W')
		{
			(*p_info->count)++;
			p_info->pos[0] = j + 1;
			p_info->pos[1] = row;
			*p_info->dir = raw[j];
		}
		j++;
	}
	while (j < width)
		line[++j] = ' ';
	line[j + 1] = ' ';
	line[j + 2] = '\0';
	return (line);
}

static char	**fill_grid(char **grid, char **raw_lines,
		size_t line_count, t_player_info *p_info)
{
	size_t	width;
	size_t	i;

	width = getm_length(raw_lines);
	i = 0;
	while (i < line_count)
	{
		grid[i + 1] = make_content_line(raw_lines[i], width, p_info, i + 1);
		if (!grid[i + 1])
			return (free_matrix(grid), NULL);
		i++;
	}
	grid[i + 1] = make_empty_line(width);
	if (!grid[i + 1])
		return (free_matrix(grid), NULL);
	grid[i + 2] = NULL;
	return (grid);
}

static char	**alloc_grid(size_t line_count)
{
	char	**grid;
	size_t	i;

	grid = malloc(sizeof(char *) * (line_count + 3));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < line_count + 3)
		grid[i++] = NULL;
	return (grid);
}

char	**build_padded_map(char **raw_lines, size_t width, int *p_pos,
		char *p_dir)
{
	char			**grid;
	size_t			line_count;
	int				p_count;
	t_player_info	p_info;

	line_count = 0;
	while (raw_lines && raw_lines[line_count])
		line_count++;
	grid = alloc_grid(line_count);
	if (!grid)
		return (NULL);
	p_count = 0;
	p_info.pos = p_pos;
	p_info.dir = p_dir;
	p_info.count = &p_count;
	grid[0] = make_empty_line(width);
	if (!grid[0])
		return (free_matrix(grid), NULL);
	if (!fill_grid(grid, raw_lines, line_count, &p_info))
		return (NULL);
	if (p_count != 1)
		return (print_error("Invalid player count"), free_matrix(grid), NULL);
	return (grid);
}
