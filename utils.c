#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	handle_exit(void *parameter)
{
	t_game	*game;

	game = (t_game *)parameter;
	exit_game(game);
	return (0);
}

void	exit_game(t_game *game)
{
	if (game->map)
		free_map(game -> map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game -> mlx, game -> win);
	if (game->mlx)
	{
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);		
	}
	if (game->tex.no)
		free(game->tex.no);
	if (game->tex.so)
		free(game->tex.so);
	if (game->tex.we)
		free(game->tex.we);
	if (game->tex.ea)
		free(game->tex.ea);
	exit(0);
}

void    put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;//dst dizideki adres

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img_data + (y * game->size_line) \
		+ (x * game->bpp / 8);//nereye yazacağımızı hesaplıyor
	*(unsigned int *)dst = color;//adrese yazacağımız değer
}