#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./printf/printf.h"

#include <stdio.h>///////

#define WIDTH 400
#define HEIGHT 300

typedef struct s_tex_img
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex_img;

typedef struct s_texture
{
	t_tex_img	no;
	t_tex_img	so;
	t_tex_img	we;
	t_tex_img	ea;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor[3];
	int			ceiling[3];
	int			floor_flag;//renk kodu olarak 0 mı yoksa null olarak onun ayrımı için
	int			ceiling_flag;
}	t_texture;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			height;
	int			width;
	double		player_x;
	double		player_y;
	double		angle;
	int			moves;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	t_texture	tex;
	void	*img;
	char	*img_data;//img dizisi
	int		bpp;//bit per pixel
	int		size_line;//bir satırın tuttuğu byte
	int		endian;
}	t_game;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		side;
	double	perpendicular_dist;
}	t_ray;


//utils.c
int		handle_exit(void *parameter);
void	exit_game(t_game *game);
void	free_map(char **map);
void	put_pixel(t_game *game, int x, int y, int color);

//movement.c
int		key_hook(int keycode, t_game *game);
void	update_dir(t_game *game);


//parse.c
int parse_file(char *filename, t_game *game);
int	map_line(char *line);
int	empty_line(char *line);


//texture.c
int	parse_texture_line(char *line, t_game *game);
int load_textures(t_game *game);
t_tex_img *get_texture(t_game *game, t_ray *ray);


//map.c
char	**read_map(char	*filename, int height);
int	map_height(char	*filename);
int	validate_map(t_game *game);
int	validate_walls(t_game *game);

//render.c
void	render(t_game *game);

#endif