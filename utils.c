/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:45:27 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 14:36:38 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	free_textures(t_game *game)
{
	if (game->tex.no_path)
		free(game->tex.no_path);
	if (game->tex.so_path)
		free(game->tex.so_path);
	if (game->tex.we_path)
		free(game->tex.we_path);
	if (game->tex.ea_path)
		free(game->tex.ea_path);
	if (game->tex.no.img)
		mlx_destroy_image(game->mlx, game->tex.no.img);
	if (game->tex.so.img)
		mlx_destroy_image(game->mlx, game->tex.so.img);
	if (game->tex.we.img)
		mlx_destroy_image(game->mlx, game->tex.we.img);
	if (game->tex.ea.img)
		mlx_destroy_image(game->mlx, game->tex.ea.img);
}

void	exit_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	free_textures(game);
	if (game->mlx)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img_data + (y * game->size_line)
		+ (x * game->bpp / 8);
	*(unsigned int *)dst = color;
}
