#include "cub3d.h"

//mlx tek bir int bekliyor ama bizim 3 rengimiz var o yüzden 
//kırmızıyı 16 yeşili 8 bit kaydırıyoruz
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
			if (y < HEIGHT / 2)//tavan
				put_pixel(game, x, y, make_color(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2]));
			else//zemin
				put_pixel(game, x, y, make_color(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2]));
		}	
	}
}

//her sütun için ışın hesabı yapar
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera;//ekranın boyutunu -1 ve 1 arasına çeken değerdir. sütunun ekrandaki konumu

	//plane üzerindeki her noktayı camera değeriyle seçiyoruz. Ray o noktaya doğru gidiyor.
	camera = 2.0 * x / WIDTH - 1.0;
	ray->dir_x = game->dirX + game->planeX * camera;
	ray->dir_y = game->dirY + game->planeY * camera;
	//ray oyuncunun konumundan başlar
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	//delta = 1 / dir
	// delta iki çizgi arasındaki mesafedir
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;//1/0 = sonsuz ama C'de bu crash eder. O yüzden elle çok büyük bir sayı veriyoruz:
	else
		ray->delta_x = fabs(1 / ray->dir_x);//mutlak değer yön negatif olamaz
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);

	// step_x 1 ise sağa gider -1 ise sola
	if (ray->dir_x > 0)
		ray->step_x = 1;
	else
		ray->step_x = -1;
	if (ray->dir_y > 0)
		ray->step_y = 1;
	else
		ray->step_y = -1;

	//side_x : oyuncudan ilk dikey çizgiye olan mesafe, side_y: oyuncudan ilk yatay çizgiye olan mesafe
	if (ray->step_x == 1)
		ray->side_x = (ray->map_x + 1.0 - game->player_x) * ray->delta_x;
	else
		ray->side_x = (game->player_x - ray->map_x) * ray->delta_x;
	if (ray->step_y == 1)
		ray->side_y = (ray->map_y + 1.0 - game->player_y) * ray->delta_y;
	else
		ray->side_y = (game->player_y - ray->map_y) * ray->delta_y;
}
//duvara çarp ve duvara olan dik mesafeyi hesapla(perp dist)
static void	dda_alg(t_game *game, t_ray *ray)
{
	int	wall_flag;

	wall_flag = 0;
	while (!wall_flag)
	//dikey çizgi mi yatay çizgi mi daha yakın ona bakar ve yakın olana atlar, duvarsa durur
	{	if (ray->side_y > ray->side_x)//x yönüne adım
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // dikey çizgiye çarptı
		}
		else//y yönüne adım
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // yatay çizgiye çarptı
		}
		//duvar kontrolü seg faulttan sonra ekledim oyuncu framein içinde mi kalıyor onu kontrol ediyor
		if (ray->map_x < 0 || ray->map_y < 0 ||
			ray->map_x >= game->width || ray->map_y >= game->height)
			wall_flag = 1;
		else if (game->map[ray->map_y][ray->map_x] == '1')
			wall_flag = 1;
	}
	//Fish-eye effect: ışınlar bir noktadan çıkıyor, yelpaze gibi yayılıyor. Gerçek göz gibi.
	//Perp_dist: sanki göz bir nokta değil, bir çizgi gibi davranıyor. Tüm ışınlar aynı düzlemden geçiyor.
	//Bunu sağlamak için ray'in gerçek mesafesi yerine kamera düzlemine dik mesafeyi kullanıyoruz.
	if (ray->side == 0)
		ray->perpendicular_dist = ray->side_x - ray->delta_x;
	else
		ray->perpendicular_dist = ray->side_y - ray->delta_y;

}

//perp diste göre duvar yüksekliğini hesapla ve çiz
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	wall_height;
	int	w_top;
	int	w_bottom;
	int	color;

	wall_height = HEIGHT / ray->perpendicular_dist;//mesafesine göre duvarın uzunluğu
	w_top = HEIGHT / 2 - wall_height / 2;//çizeceğimiz duvarın üst noktası
	w_bottom = HEIGHT / 2 + wall_height / 2;//çizeceğimiz duvarın alt noktası

	if (w_top < 0)
		w_top = 0;
	if (w_bottom >= HEIGHT)
		w_bottom = HEIGHT;
	color = w_top;
	while (color <= w_bottom)
	{
		put_pixel(game, x, color, 0xAAAAAA);
		color++;
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
		dda_alg(game, &ray);
		draw_column(game, &ray, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
