#include "cub3d.h"

//mapin uzunluğunu buluyor
int	map_height(char	*filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	line = get_next_line(fd, 0);
	while (line)
	{	
		//dosyadaki sadece map olan kısımları sayıyor
		if (map_line(line))
			height++;
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	close(fd);
	return (height);
}
//uzunluğuna göre yer açıp oluşturduğu map dizisine atıyor
char	**read_map(char	*filename, int height)
{
	int		i;
	int		fd;
	char	**map;
	char	*line;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	line = get_next_line(fd, 0);
	i = 0;
	while (line && (i < height))
	{
		//dosyadaki sadece map olan kısımları alıyor
		if (map_line(line))
			map[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd, 0);
	}
	map[i] = NULL;
	get_next_line(fd, 1);
	close(fd);
	return (map);
}

static int	check_map_cell(t_game *game, int row, int col, int *player_count)
{
	//yönünü belirliyor
	if (game -> map[row][col] == 'N' || game -> map[row][col] == 'S' || \
		game -> map[row][col] == 'E' || game -> map[row][col] == 'W')
	{
		(*player_count)++;
		game->player_x = col + 0.5;
		game->player_y = row + 0.5;
		if (game->map[row][col] == 'N')
			game->angle = -M_PI / 2;
		else if (game->map[row][col] == 'S')
			game->angle = M_PI / 2;	
		else if (game->map[row][col] == 'E')
			game->angle = 0;
		else if (game->map[row][col] == 'W')
			game->angle = M_PI;
	}
	//map 0 1 ve boşluk içerebilir
	else if (game -> map[row][col] != '0' && game -> map[row][col] != '1' && \
			game -> map[row][col] != ' ')
		return (0);
	return (1);
}
//her bir birimde geziyor ve sadece 1 oyuncu olabilir
int	validate_map(t_game *game)
{
	int	row;
	int	col;
	int	player_count;

	player_count = 0;
	row = -1;
	while (game -> map[++row])
	{
		col = -1;
		while (game -> map[row][++col])
		{
			if (!check_map_cell(game, row, col, &player_count))
				return (0);
		}
	}
	if (player_count != 1)
	{
		ft_printf("Error\nOyuncu sayısı 1 değil");
		return (0);
	}
	return (1);
}

static int	is_surrounded(t_game *game, int row, int col)
{
	//ilk satır     en alt satır           en sol hücre
	if (row == 0 || !game->map[row + 1] || col == 0)
		return (0);
	//  sağdaki hücrenin null    veya  boşluk olması
	if (!game->map[row][col + 1] || game->map[row][col + 1] == ' ')
		return (0);
	// solundaki hücre null veyda boşluksa
	if (!game->map[row][col - 1] || game->map[row][col - 1] == ' ')
		return (0);
	//   üst satırın uzunluğu kısaysa              bir üst satırı null veya boşluksa
	if ((int)ft_strlen(game->map[row - 1]) < col || !game->map[row - 1][col] \
		|| game->map[row - 1][col] == ' ')
		return (0);
	// alt satır verisyonu
	if ((int)ft_strlen(game->map[row + 1]) < col || !game->map[row + 1][col] \
		|| game->map[row + 1][col] == ' ')
		return (0);
	return (1);
}

int validate_walls(t_game *game)
{
	int	row;
	int	col;

	row = -1;
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			// 0 n s e w ise
			if (game->map[row][col] != '1' && game->map[row][col] != ' ')
			{
				if (!is_surrounded(game, row, col))
				{
					ft_printf("Error\nMap not closed\n");
					return (0);
				}
			}
		}
	}
	return (1);
}
