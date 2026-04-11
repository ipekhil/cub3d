/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:46:29 by staylan           #+#    #+#             */
/*   Updated: 2026/04/11 12:31:56 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./printf/printf.h"

# define WIDTH 800
# define HEIGHT 600

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
	int			floor_flag;
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
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_texture	tex;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_game;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	double		side_x;
	double		side_y;
	int			map_x;
	int			map_y;
	int			side;
	double		perpendicular_dist;
}	t_ray;

typedef struct s_col
{
	int		wall_height;
	int		w_top;
	int		w_bottom;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_col;

//utils.c
int			handle_exit(void *parameter);
void		exit_game(t_game *game);
void		free_map(char **map);
void		put_pixel(t_game *game, int x, int y, int color);

//movement.c
int			game_loop(t_game *game);
void		update_dir(t_game *game);

//input.c
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

//parser.c
int			parse_file(char *filename, t_game *game);
int			map_line(char *line);
int			empty_line(char *line);

//texture.c
int			parse_texture_line(char *line, t_game *game);
t_tex_img	*get_texture(t_game *game, t_ray *ray);

//texture_load.c
int			load_textures(t_game *game);

//map.c
char		**read_map(char *filename, int height);
int			map_height(char *filename);
int			pad_map(t_game *game);

//validation.c
int			validate_map(t_game *game);
int			validate_walls(t_game *game);

//ray.c
void		init_ray(t_game *game, t_ray *ray, int x);
void		dda_alg(t_game *game, t_ray *ray);

//render.c
void		render(t_game *game);

#endif