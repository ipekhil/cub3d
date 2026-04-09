#include "cub3d.h"
//path kısmını ayırıyoruz
static char	*texture_path(char *line, int offset)
{
	int		i;
	char	*path;

	i = offset;
	// baştaki NO SO (offset) kısımlarını atlayıp boşlukları geçiyor
	while (line[i] == ' ')
		i++;
	//lineın path kısmını path değişkenine kopyalıyor
	path = ft_strdup(&line[i]);
	i = 0;
	//sondaki newlineı siliyor
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}

static int	valid_rgb_str(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ' || s[i] == '\n')
		i++;
	return (s[i] == '\0');
}

static long	ft_atol(const char *s)
{
	long	res;

	res = 0;
	while (*s == ' ')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (res > 255)
			return (256);
		s++;
	}
	return (res);
}

static int	parse_rgb(char *line, int rgb[3])
{
	char	**split;
	int		i;
	long	val;

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
			return (free_map(split), -1);
	if (split[3])
		return (free_map(split), -1);
	i = -1;
	while (++i < 3)
	{
		if (!valid_rgb_str(split[i]))
			return (free_map(split), -1);
		val = ft_atol(split[i]);
		if (val < 0 || val > 255){
			ft_printf("Error\nInteger overflow!\n");
			return (free_map(split), -1);
		}
		rgb[i] = (int)val;
	}
	free_map(split);
	return (0);
}

int	parse_texture_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !game->tex.no_path)
		game->tex.no_path = texture_path(line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !game->tex.so_path)
		game->tex.so_path = texture_path(line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !game->tex.we_path)
		game->tex.we_path = texture_path(line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !game->tex.ea_path)
		game->tex.ea_path = texture_path(line, 3);
	else if (ft_strncmp(line, "F ", 2) == 0 && !game->tex.floor_flag)
	{
		if (parse_rgb(&line[2], game->tex.floor) < 0)
			return (-1);
		game->tex.floor_flag = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !game->tex.ceiling_flag)
	{
		if (parse_rgb(&line[2], game->tex.ceiling) < 0)
			return (-1);
		game->tex.ceiling_flag = 1;
	}
	else
		return (-1);
	return (0);
}

//xpm dosyasını yükleyip img ve data pointerlarını dolduruyor
static int	one_load_texture(t_game *game, t_tex_img *tex_img, char *path)
{
	tex_img->img = mlx_xpm_file_to_image(game->mlx, path, &tex_img->width,
			&tex_img->height);
	if (!tex_img->img)
		return (-1);
	//img in data adresini alıp int* a çeviriyor
	tex_img->data = (int *)mlx_get_data_addr(tex_img->img, &tex_img->bpp,
			&tex_img->size_line, &tex_img->endian);
	return (0);
}

//tüm textureları sırayla yüklüyor
int	load_textures(t_game *game)
{
	if (one_load_texture(game, &game->tex.no, game->tex.no_path) < 0)
		return (-1);
	if (one_load_texture(game, &game->tex.so, game->tex.so_path) < 0)
		return (-1);
	if (one_load_texture(game, &game->tex.we, game->tex.we_path) < 0)
		return (-1);
	if (one_load_texture(game, &game->tex.ea, game->tex.ea_path) < 0)
		return (-1);
	free(game->tex.no_path);
	game->tex.no_path = NULL;
	free(game->tex.so_path);
	game->tex.so_path = NULL;
	free(game->tex.we_path);
	game->tex.we_path = NULL;
	free(game->tex.ea_path);
	game->tex.ea_path = NULL;
	return (0);
}

t_tex_img	*get_texture(t_game *game, t_ray *ray)
{
	// X ekseninde bir duvara çarptıysa (Dikey çizgiler)
	if (ray->side == 0)
	{
		// Işın sağa gidiyorsa çarptığı yüzey Doğu (EA) texture'ını görmeli
		if (ray->dir_x > 0)
			return (&game->tex.ea);
		else
			return (&game->tex.we);
	}
	// Y ekseninde bir duvara çarptıysa (Yatay çizgiler)
	else
	{
		// Işın aşağı gidiyorsa çarptığı yüzey Güney (SO) texture'ını görmeli
		if (ray->dir_y > 0)
			return (&game->tex.so);
		else
			return (&game->tex.no);
	}
}