#include "cub3d.h"

static char	*dup_clean_line(char *line)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = 0;
	while (line[len] && line[len] != '\n' && line[len] != '\r')
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = line[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static int	count_file_lines(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	fill_file_lines(const char *filename, char **lines, int count)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < count)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines[i] = dup_clean_line(line);
		free(line);
		if (!lines[i])
			break ;
		i++;
	}
	drain_gnl(fd);
	close(fd);
	lines[i] = NULL;
	return (i == count);
}

int	has_cub_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	read_cub_file(const char *filename, char ***lines, int *line_count)
{
	int	count;

	count = count_file_lines(filename);
	if (count < 0)
		return (print_error("failed to open file"));
	if (count == 0)
		return (print_error("empty file"));
	*lines = malloc(sizeof(char *) * (count + 1));
	if (!*lines)
		return (print_error("malloc failed"));
	if (!fill_file_lines(filename, *lines, count))
	{
		free_matrix(*lines);
		*lines = NULL;
		return (print_error("failed to read file"));
	}
	*line_count = count;
	return (0);
}
