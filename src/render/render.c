/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:44:54 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 18:58:22 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	make_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	drawn_background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, make_color(game->tex.ceiling[0],
						game->tex.ceiling[1], game->tex.ceiling[2]));
			else
				put_pixel(game, x, y, make_color(game->tex.floor[0],
						game->tex.floor[1], game->tex.floor[2]));
		}
	}
}

static void	draw_wall_line(t_game *game, t_tex_img *tex, int x, t_col *col)
{
	int	tex_y;
	int	y;

	y = col->w_top;
	while (y <= col->w_bottom)
	{
		tex_y = (int)col->tex_pos % tex->height;
		if (tex_y < 0)
			tex_y = 0;
		put_pixel(game, x, y,
			tex->data[tex_y * (tex->size_line / 4) + col->tex_x]);
		col->tex_pos += col->step;
		y++;
	}
}

static void	draw_column(t_game *game, t_ray *ray, int x, t_tex_img *tex)
{
	t_col	col;
	double	hit_point;

	if (ray->perpendicular_dist < 0.0001)
		ray->perpendicular_dist = 0.0001;
	col.wall_height = HEIGHT / ray->perpendicular_dist;
	col.w_top = HEIGHT / 2 - col.wall_height / 2;
	col.w_bottom = HEIGHT / 2 + col.wall_height / 2;
	if (col.w_top < 0)
		col.w_top = 0;
	if (col.w_bottom >= HEIGHT)
		col.w_bottom = HEIGHT;
	if (ray->side == 0)
		hit_point = game->player_y + ray->perpendicular_dist * ray->dir_y;
	else
		hit_point = game->player_x + ray->perpendicular_dist * ray->dir_x;
	hit_point -= floor(hit_point);
	col.tex_x = (int)(hit_point * (double)tex->width);
	col.step = (double)tex->height / col.wall_height;
	col.tex_pos = (col.w_top - HEIGHT / 2 + col.wall_height / 2) * col.step;
	draw_wall_line(game, tex, x, &col);
}

void	render(t_game *game)
{
	int			x;
	t_ray		ray;
	t_tex_img	*tex;

	x = -1;
	drawn_background(game);
	while (++x < WIDTH)
	{
		init_ray(game, &ray, x);
		dda_alg(game, &ray);
		tex = get_texture(game, &ray);
		draw_column(game, &ray, x, tex);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
