NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT = $(LIBFT_DIR)/libft.a

SRC = cub3d.c utils.c movement.c input.c map.c parser.c texture.c \
	texture_load.c validation.c render.c ray.c \
	$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	printf/ft_printf.c printf/ft_printf_func.c

OBJS = $(SRC:.c=.o)

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
