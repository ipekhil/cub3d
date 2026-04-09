/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:46:41 by staylan           #+#    #+#             */
/*   Updated: 2026/04/09 18:46:45 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_height(char *filename)
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

static int	fill_map(int fd, char **map, int height)
{
	int		i;
	char	*line;

	line = get_next_line(fd, 0);
	i = 0;
	while (line && (i < height))
	{
		if (map_line(line))
			map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd, 0);
	}
	if (line)
		free(line);
	map[i] = NULL;
	get_next_line(fd, 1);
	return (i);
}

char	**read_map(char *filename, int height)
{
	int		fd;
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	fill_map(fd, map, height);
	close(fd);
	return (map);
}

static int	pad_map_row(t_game *game, int i)
{
	char	*padded;

	padded = malloc(sizeof(char) * (game->width + 1));
	if (!padded)
		return (-1);
	ft_memset(padded, ' ', game->width);
	padded[game->width] = '\0';
	ft_memcpy(padded, game->map[i], ft_strlen(game->map[i]));
	free(game->map[i]);
	game->map[i] = padded;
	return (0);
}

int	pad_map(t_game *game)
{
	int	i;

	i = 0;
	game->width = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) > game->width)
			game->width = ft_strlen(game->map[i]);
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) < game->width)
		{
			if (pad_map_row(game, i) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
