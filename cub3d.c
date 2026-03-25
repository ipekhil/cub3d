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
	game->dir_x = -1;
	game->dir_y = 0;
	ft_memset(&game->tex, 0, sizeof(t_texture));
	game->img = NULL;
	game->img_data = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->endian = 0;
}

int main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	init_game(&game);
	if (parse_file(argv[1], &game) == -1)
		exit_game(&game);
	printf("width: %d, height: %d\n", game.width, game.height);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	if (load_textures(&game) == -1)
		exit_game(&game);
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
	if (!game.win)
		return (1);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	//ramde boş piksel dizisi oluşturur
	if (!game.img)
		return (1);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp,
			&game.size_line, &game.endian);
	//dizinin bilgilerini verir
	update_dir(&game);
	render(&game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (1);
}
