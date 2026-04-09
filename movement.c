/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:46:11 by staylan           #+#    #+#             */
/*   Updated: 2026/04/09 20:17:20 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_at(t_game *game, double x, double y)
{
	return (game->map[(int)y][(int)x] == '1');
}

static void	move_player(t_game *game, double dir_x, double dir_y)
{
	double	speed;
	double	new_x;
	double	new_y;
	double	buf;

	speed = 0.05;
	buf = 0.1;
	new_x = game->player_x + dir_x * speed;
	new_y = game->player_y + dir_y * speed;
	if (!wall_at(game, new_x + buf, game->player_y)
		&& !wall_at(game, new_x - buf, game->player_y))
		game->player_x = new_x;
	if (!wall_at(game, game->player_x, new_y + buf)
		&& !wall_at(game, game->player_x, new_y - buf))
		game->player_y = new_y;
}

static void	apply_keys(t_game *game)
{
	double	rot_speed;

	rot_speed = 0.03;
	if (game->key_w)
		move_player(game, cos(game->angle), sin(game->angle));
	if (game->key_s)
		move_player(game, -cos(game->angle), -sin(game->angle));
	if (game->key_a)
		move_player(game, sin(game->angle), -cos(game->angle));
	if (game->key_d)
		move_player(game, -sin(game->angle), cos(game->angle));
	if (game->key_left)
		game->angle -= rot_speed;
	if (game->key_right)
		game->angle += rot_speed;
}

int	game_loop(t_game *game)
{
	apply_keys(game);
	update_dir(game);
	render(game);
	return (0);
}

void	update_dir(t_game *game)
{
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
	game->plane_x = -sin(game->angle) * 0.66;
	game->plane_y = cos(game->angle) * 0.66;
}
