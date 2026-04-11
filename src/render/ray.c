/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:44:46 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 18:58:27 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_ray_dir(t_game *game, t_ray *ray, int x)
{
	double	camera;

	camera = 2.0 * x / WIDTH - 1.0;
	ray->dir_x = game->dir_x + game->plane_x * camera;
	ray->dir_y = game->dir_y + game->plane_y * camera;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

static void	init_ray_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x > 0)
		ray->step_x = 1;
	else
		ray->step_x = -1;
	if (ray->dir_y > 0)
		ray->step_y = 1;
	else
		ray->step_y = -1;
	if (ray->step_x == 1)
		ray->side_x = (ray->map_x + 1.0 - game->player_x) * ray->delta_x;
	else
		ray->side_x = (game->player_x - ray->map_x) * ray->delta_x;
	if (ray->step_y == 1)
		ray->side_y = (ray->map_y + 1.0 - game->player_y) * ray->delta_y;
	else
		ray->side_y = (game->player_y - ray->map_y) * ray->delta_y;
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	init_ray_dir(game, ray, x);
	init_ray_step(game, ray);
}

static void	calc_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpendicular_dist = ray->side_x - ray->delta_x;
	else
		ray->perpendicular_dist = ray->side_y - ray->delta_y;
}

void	dda_alg(t_game *game, t_ray *ray)
{
	int	wall_flag;

	wall_flag = 0;
	while (!wall_flag)
	{
		if (ray->side_y > ray->side_x)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_x >= game->width || ray->map_y >= game->height)
			wall_flag = 1;
		else if (game->map[ray->map_y][ray->map_x] == '1')
			wall_flag = 1;
	}
	calc_perp_dist(ray);
}
