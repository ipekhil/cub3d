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

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	int		floor_flag;//renk kodu olarak 0 mı yoksa null olarak onun ayrımı için
	int		ceiling_flag;
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
}	t_game;


int		handle_exit(void *parameter);
void	exit_game(t_game *game);
void	free_map(char **map);


int		key_hook(int keycode, t_game *game);

//parse.c
int parse_file(char *filename, t_game *game);
int	map_line(char *line);
int	empty_line(char *line);


//texture.c
int	parse_texture_line(char *line, t_game *game);


//map.c
char	**read_map(char	*filename, int height);
int	map_height(char	*filename);
int	validate_map(t_game *game);
int	validate_walls(t_game *game);



#endif