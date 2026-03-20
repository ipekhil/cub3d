#include "cub3d.h"

int	map_height(char	*filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	line = get_next_line(fd, 0);
	while (line)
	{	
		if (map_line(line))
			height++;
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	close(fd);
	return (height);
}

char	**read_map(char	*filename, int height)
{
	int		i;
	int		fd;
	char	**map;
	char	*line;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	line = get_next_line(fd, 0);
	i = 0;
	while (line && (i < height))
	{
		if (map_line(line))
			map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd, 0);
	}
	map[i] = NULL;
	get_next_line(fd, 1);
	close(fd);
	return (map);
}

static int	check_map_cell(t_game *game, int row, int col, int *player_count)
{
	if (game -> map[row][col] == 'N' || game -> map[row][col] == 'S' || \
		game -> map[row][col] == 'E' || game -> map[row][col] == 'W')
	{
		(*player_count)++;
		game->player_x = col + 0.5;
		game->player_y = row + 0.5;
		if (game->map[row][col] == 'N')
			game->angle = -M_PI / 2;
		else if (game->map[row][col] == 'S')
			game->angle = M_PI / 2;	
		else if (game->map[row][col] == 'E')
			game->angle = 0;
		else if (game->map[row][col] == 'W')
			game->angle = M_PI;
	}
	else if (game -> map[row][col] != '0' && game -> map[row][col] != '1' && \
			game -> map[row][col] != ' ')
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	int	row;
	int	col;
	int	player_count;

	player_count = 0;
	row = -1;
	while (game -> map[++row])
	{
		col = -1;
		while (game -> map[row][++col])
		{
			if (!check_map_cell(game, row, col, &player_count))
				return (0);
		}
	}
	if (player_count != 1)
		return (0);
	return (1);
}

int validate_walls(t_game *game)
{
	(void)game;
	return (1);
}
