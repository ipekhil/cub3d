/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:46:55 by staylan           #+#    #+#             */
/*   Updated: 2026/04/09 18:46:59 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->dir_x = -1;
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	if (load_textures(game) == -1)
		return (-1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		return (-1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (-1);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	init_game(&game);
	if (parse_file(argv[1], &game) == -1)
		exit_game(&game);
	if (init_mlx(&game) == -1)
		exit_game(&game);
	update_dir(&game);
	render(&game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
