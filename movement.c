#include "cub3d.h"

// static void	update_player_position(t_game *game, int new_x, int new_y)
// {
// 	//game->map[(int)game->player_y][(int)game->player_x] = '0';
// 	//game->map[new_y][new_x] = 'P';
// 	game->player_x = new_x;
// 	game->player_y = new_y;
// 	game->moves++;
// 	printf("Moves: %d\n", game -> moves);
// }

static void	move_player(t_game *game, double dir_x, double dir_y)
{
	double speed = 0.15;

    game->player_x += dir_x * speed;
    game->player_y += dir_y * speed;

    printf("X: %.2f | Y: %.2f | Açı: %.2f\n", 
           game->player_x, game->player_y, game->angle);
	// if (game -> map[new_y][new_x] != '1')
	// {
	// 	//if (!handler(game, new_x, new_y))
	// 		return ;
	// }
	// else
	// 	return ;
	//update_player_position(game, new_x, new_y);
	//render(game);
}

int	key_hook(int keycode, t_game	*game)
{
	double	rot_speed;

	rot_speed = 0.1;
	if (keycode == 65307)
		exit_game(game);
	else if (keycode == 65363)//sağ
		game->angle += rot_speed;
	else if (keycode == 65361)//sol
		game->angle -= rot_speed;
	else if (keycode == 119)//W
		move_player(game, cos(game->angle), sin(game->angle));
	else if (keycode == 115)//S
		move_player(game, -cos(game->angle), -sin(game->angle));
	else if (keycode == 97)//A
		move_player(game, sin(game->angle), -cos(game->angle));
	else if (keycode == 100)//D
		move_player(game, -sin(game->angle), cos(game->angle));
	return (0);
}
