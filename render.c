#include "cub3d.h"

//mlx tek bir int bekliyor ama bizim 3 rengimiz var o yüzden 
//kırmızıyı 16 yeşili 8 bit kaydırıyoruz
static int	make_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera;

	camera = 2.0 * x / WIDTH - 1.0;
	ray->dir_x = game->dirX + game->planeX * camera;
	ray->dir_y = game->dirY + game->planeY * camera;
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
			if (y < HEIGHT / 2)//tavan
				put_pixel(game, x, y, make_color(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2]));
			else//zemin
				put_pixel(game, x, y, make_color(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2]));
		}	
	}
}

void	render(t_game *game)
{
	int		x;
	t_ray	ray;
	x = -1;
	drawn_background(game);
	while (++x < WIDTH)
	{
		init_ray(game, &ray, x);
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}