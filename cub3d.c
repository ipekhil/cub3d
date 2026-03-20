#include "cub3d.h"

void init_game(t_game *game)
{
	game -> mlx = NULL;
	game -> win = NULL;
	game -> map = NULL;
	game -> height = 0;
	game -> width = 0;
	game -> angle = 0.0;
	game -> player_x = 5.0;
	game -> player_y = 5.0;
	game -> moves = 0;
	game->dirX = -1;
	game->dirY = 0;
	game->tex.no = NULL;
	game->tex.so = NULL;
	game->tex.we = NULL;
	game->tex.ea = NULL;
	game->tex.floor_flag = 0;
	game->tex.ceiling_flag = 0;

}

int main(int argc, char **argv)
{
	t_game game;
	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	init_game(&game);
	if (parse_file(argv[1], &game) == -1)
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
	if (!game.win)
		return (1);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (1);
}