/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:45:20 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 19:10:10 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*texture_path(char *line, int offset)
{
	int		i;
	int		len;
	char	*path;

	i = offset;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[--len] = '\0';
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\t'))
		path[--len] = '\0';
	return (path);
}

static int	check_rgb_value(char *str)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = val * 10 + (str[i] - '0');
		if (val > 255)
			return (-1);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] != '\0')
		return (-1);
	return (val);
}

static int	parse_rgb(char *line, int rgb[3])
{
	char	**split;
	int		i;

	split = ft_split(line, ',');
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_map(split);
		return (-1);
	}
	i = -1;
	while (++i < 3)
	{
		rgb[i] = check_rgb_value(split[i]);
		if (rgb[i] < 0)
		{
			free_map(split);
			return (-1);
		}
	}
	free_map(split);
	return (0);
}

static int	parse_color(char *line, int *arr, int *flag)
{
	if (*flag)
		return (-1);
	if (parse_rgb(line, arr) < 0)
		return (-1);
	*flag = 1;
	return (0);
}

int	parse_texture_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (ft_strncmp(&line[i], "NO ", 3) == 0 && !game->tex.no_path)
		game->tex.no_path = texture_path(&line[i], 3);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0 && !game->tex.so_path)
		game->tex.so_path = texture_path(&line[i], 3);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0 && !game->tex.we_path)
		game->tex.we_path = texture_path(&line[i], 3);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0 && !game->tex.ea_path)
		game->tex.ea_path = texture_path(&line[i], 3);
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (parse_color(&line[i + 2],
				game->tex.floor, &game->tex.floor_flag));
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (parse_color(&line[i + 2],
				game->tex.ceiling, &game->tex.ceiling_flag));
	else
		return (-1);
	return (0);
}
