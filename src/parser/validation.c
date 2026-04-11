/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:45:35 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 18:58:30 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_map_cell(t_game *game, int row, int col, int *player_count)
{
	if (game->map[row][col] == 'N' || game->map[row][col] == 'S'
		|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
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
	else if (game->map[row][col] != '0' && game->map[row][col] != '1'
		&& game->map[row][col] != ' ')
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
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			if (!check_map_cell(game, row, col, &player_count))
				return (0);
		}
	}
	if (player_count != 1)
	{
		ft_printf("Error\nPlayer count is not 1\n");
		return (0);
	}
	return (1);
}

static int	is_surrounded(t_game *game, int row, int col)
{
	if (row == 0 || !game->map[row + 1] || col == 0)
		return (0);
	if (!game->map[row][col + 1] || game->map[row][col + 1] == ' ')
		return (0);
	if (!game->map[row][col - 1] || game->map[row][col - 1] == ' ')
		return (0);
	if ((int)ft_strlen(game->map[row - 1]) <= col
		|| game->map[row - 1][col] == ' ')
		return (0);
	if ((int)ft_strlen(game->map[row + 1]) <= col
		|| game->map[row + 1][col] == ' ')
		return (0);
	return (1);
}

int	validate_walls(t_game *game)
{
	int	row;
	int	col;

	row = -1;
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			if (game->map[row][col] != '1' && game->map[row][col] != ' ')
			{
				if (!is_surrounded(game, row, col))
				{
					ft_printf("Error\nMap not closed\n");
					return (0);
				}
			}
		}
	}
	return (1);
}
