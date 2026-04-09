#include "cub3d.h"

static int	one_load_texture(t_game *game, t_tex_img *tex_img, char *path)
{
	tex_img->img = mlx_xpm_file_to_image(game->mlx, path, &tex_img->width,
			&tex_img->height);
	if (!tex_img->img)
		return (-1);
	tex_img->data = (int *)mlx_get_data_addr(tex_img->img, &tex_img->bpp,
			&tex_img->size_line, &tex_img->endian);
	return (0);
}

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
