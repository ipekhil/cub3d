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
			if (y < HEIGHT / 2) //tavan
				put_pixel(game, x, y, make_color(game->tex.ceiling[0],
						game->tex.ceiling[1], game->tex.ceiling[2]));
			else//zemin
				put_pixel(game, x, y, make_color(game->tex.floor[0],
						game->tex.floor[1], game->tex.floor[2]));
		}
	}
}

//her sütun için ışın hesabı yapar
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera;
	//ekranın boyutunu -1 ve 1 arasına çeken değerdir. sütunun ekrandaki konumu
	//plane üzerindeki her noktayı camera değeriyle seçiyoruz. Ray o noktaya doğru gidiyor.
	camera = 2.0 * x / WIDTH - 1.0;
	ray->dir_x = game->dir_x + game->plane_x * camera;
	ray->dir_y = game->dir_y + game->plane_y * camera;
	//ray oyuncunun konumundan başlar
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	//delta = 1 / dir
	// delta iki çizgi arasındaki mesafedir
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
		//1/0 = sonsuz ama C'de bu crash eder. O yüzden elle çok büyük bir sayı veriyoruz:
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
	{
		if (ray->side_y > ray->side_x)//x yönüne adım
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
		if (ray->map_x < 0 || ray->map_y < 0 
			||	ray->map_x >= game->width || ray->map_y >= game->height)
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
static void	draw_column(t_game *game, t_ray *ray, int x, t_tex_img *tex)
{
	int		wall_height;
	int		w_top;
	int		w_bottom;
	double	hit_point;
	int 	tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	//Sıfıra bölmeyi engellemek için mesafe kontrolü
	if (ray->perpendicular_dist < 0.0001)
		ray->perpendicular_dist = 0.0001;
	wall_height = HEIGHT / ray->perpendicular_dist;//mesafesine göre duvarın uzunluğu perpendicular_dist ne kadar büyükse duvar o kadar kısa olur	
	w_top = HEIGHT / 2 - wall_height / 2;//çizeceğimiz duvarın üst noktası
	w_bottom = HEIGHT / 2 + wall_height / 2;//çizeceğimiz duvarın alt noktası
	//duvar ekranın dışına taşmasın diye sınırlandırıyoruz
	if (w_top < 0)
		w_top = 0;
	if (w_bottom >= HEIGHT)
		w_bottom = HEIGHT;
	//duvara çarptığımız noktanın koordinatını buluyoruz
	if (ray->side == 0)
		hit_point = game->player_y + ray->perpendicular_dist * ray->dir_y;
	else
		hit_point = game->player_x + ray->perpendicular_dist * ray->dir_x;
	hit_point -= floor(hit_point);
	//floor ile tam sayı kısmını atıp 0.0 - 1.0 arası değer elde ediyoruz onu da texture genişliği ile çarpıyoruz
	//ve hangi sütunu çizeceğimizi buluyoruz
	tex_x = (int)(hit_point * (double)tex->width);
	//her ekran pikseli için texture'da kaç satır atlayacağız. 
	//duvar ne kadar büüykse (wall_height) , step o kadar küçük olur çünkü duvarın her pikseli texture'da daha az satır atlar.
	step = (double)tex->height / wall_height;
	//texture'ın hangi satırından başlayacağımızı buluyoruz
	tex_pos = (w_top - HEIGHT / 2 + wall_height / 2) * step;
	//duvarın üstünden başlayarak duvarın altına kadar her piksel için texture'dan renk alıp çizeriz
	color = w_top;
	while (color <= w_bottom)
	{
		//tex_pos'u int'e çevirip texture'ın o satırından renk alıyoruz
		tex_y = (int)tex_pos % tex->height;
		if (tex_y < 0) 
			tex_y = 0; //tex_pos duvara çok yaklaşıldığında negatşf olursa mod negatif çıkabilir ve negatif index hatası olabilir
		//tex_pos'u step kadar artırarak bir sonraki piksel için texture'ın hangi satırını kullanacağımızı buluyoruz
		tex_pos = tex_pos + step;
		//texture'dan aldığımız rengi ekrana çiziyoruz
		//tex->size_line / 4: bir satırda kaç int var onu buluyoruz çünkü data int* türünde
		//onu tex_y ile çarparak texture'ın o satırının başlangıç adresini buluyoruz, tex_x ile de o satırda hangi sütunu kullanacağımızı buluyoruz
		put_pixel(game, x, color, tex->data[tex_y * (tex->size_line / 4) + tex_x]);
		color++;
	}
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
