#include "cub3d.h"

static int	file_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4)
		return (0);
	i -= 4;
	if (!(filename[i] == '.' && filename[i + 1] == 'c' \
		&& filename[i + 2] == 'u' && filename[i + 3] == 'b'))
		return (0);
	return (1);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	map_line(char *line)
{
	int	i;

	if (empty_line(line))
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '1' || line[i] == '0' || \
		line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || \
		line[i] == 'W' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	//uzantı kontrolü
    if (!file_extension(filename))
    {
        ft_printf("Error\nInvalid file extension\n");
        return (-1);
    }
	//map dosyasını açıyoruz
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCannot open file\n");
		return (-1);
	}
	//satır satır okuyoruz
	line = get_next_line(fd, 0);
	while (line)
	{
		//satır çeşidine bakıp aksiyon alıyoruz
		if(empty_line(line))
			;
		else if (map_line(line))
			ft_printf("MAP %s", line);
		else//baştaki 6 satır
		{
			if (parse_texture_line(line, game) < 0)
			{
				free(line);
				get_next_line(fd, 1);
				close(fd);
				return (-1);
			}
			
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	close(fd);

	game->height = map_height(filename);
	if (!game->height)
		return (-1);
	game->map = read_map(filename, game->height);
	if (!game->map)
		return (-1);
	if (!validate_map(game))
		return (-1);
	if (!validate_walls(game))
		return (-1);
	
	int i = 0;
	while (game->map[i])
	{
		printf("MAP[%d]: %s\n", i, game->map[i]);
		i++;
	}
    return (0);
}
