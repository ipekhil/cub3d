#include "cub3d.h"

static void	move_player(t_game *game, double dir_x, double dir_y)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = 0.05;
	new_x = game->player_x + dir_x * speed;
	new_y = game->player_y + dir_y * speed;
	if (game->map[(int)game->player_y][(int)new_x] != '1')
		game->player_x = new_x;
	if (game->map[(int)new_y][(int)game->player_x] != '1')
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

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	if (keycode == 119)
		game->key_w = 1;
	else if (keycode == 115)
		game->key_s = 1;
	else if (keycode == 97)
		game->key_a = 1;
	else if (keycode == 100)
		game->key_d = 1;
	else if (keycode == 65361)
		game->key_left = 1;
	else if (keycode == 65363)
		game->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->key_w = 0;
	else if (keycode == 115)
		game->key_s = 0;
	else if (keycode == 97)
		game->key_a = 0;
	else if (keycode == 100)
		game->key_d = 0;
	else if (keycode == 65361)
		game->key_left = 0;
	else if (keycode == 65363)
		game->key_right = 0;
	return (0);
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
