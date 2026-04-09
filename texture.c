/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:45:20 by staylan           #+#    #+#             */
/*   Updated: 2026/04/09 18:45:22 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*texture_path(char *line, int offset)
{
	int		i;
	char	*path;

	i = offset;
	while (line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
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

int	parse_texture_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !game->tex.no_path)
		game->tex.no_path = texture_path(line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !game->tex.so_path)
		game->tex.so_path = texture_path(line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !game->tex.we_path)
		game->tex.we_path = texture_path(line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !game->tex.ea_path)
		game->tex.ea_path = texture_path(line, 3);
	else if (ft_strncmp(line, "F ", 2) == 0 && !game->tex.floor_flag)
	{
		if (parse_rgb(&line[2], game->tex.floor) < 0)
			return (-1);
		game->tex.floor_flag = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !game->tex.ceiling_flag)
	{
		if (parse_rgb(&line[2], game->tex.ceiling) < 0)
			return (-1);
		game->tex.ceiling_flag = 1;
	}
	else
		return (-1);
	return (0);
}

t_tex_img	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->tex.ea);
		else
			return (&game->tex.we);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&game->tex.so);
		else
			return (&game->tex.no);
	}
}
