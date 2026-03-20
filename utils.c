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
	free_map(game -> map);
	if (game->win)
		mlx_destroy_window(game -> mlx, game -> win);
	if (game->mlx)
	{
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);		
	}
	exit(0);
}