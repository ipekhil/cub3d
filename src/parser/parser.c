/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:47:50 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 20:03:22 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	file_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4)
		return (0);
	i -= 4;
	if (!(filename[i] == '.' && filename[i + 1] == 'c'
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
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
		|| line[i] == 'W' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

static int	parse_config(int fd, t_game *game)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		if (!empty_line(line) && !map_line(line) && map_started)
			return (free(line), get_next_line(fd, 1),
				ft_printf("Error\nConfig element after map\n"), -1);
		if (!empty_line(line) && map_line(line))
			map_started = 1;
		if (!empty_line(line) && !map_line(line)
			&& parse_texture_line(line, game) < 0)
			return (free(line), get_next_line(fd, 1),
				ft_printf("Error\nInvalid line\n"), -1);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	return (0);
}

int	parse_file(char *filename, t_game *game)
{
	int	fd;

	if (!file_extension(filename))
		return (ft_printf("Error\nInvalid file extension\n"), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nCannot open file\n"), -1);
	if (parse_config(fd, game) < 0)
		return (close(fd), -1);
	close(fd);
	game->height = map_height(filename);
	if (!game->height)
		return (-1);
	game->map = read_map(filename, game->height);
	if (!game->map)
		return (-1);
	if (pad_map(game) < 0)
		return (-1);
	if (!validate_map(game) || !validate_walls(game))
		return (-1);
	return (0);
}
