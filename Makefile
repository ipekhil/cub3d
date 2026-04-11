NAME        = cub3d
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

SRC_DIR     = src
LIB_DIR     = libs

MLX_DIR     = $(LIB_DIR)/mlx
LIBFT_DIR   = $(LIB_DIR)/libft
GNL_DIR     = $(LIB_DIR)/get_next_line
PRINTF_DIR  = $(LIB_DIR)/printf

SRC         = $(SRC_DIR)/cub3d.c \
              $(SRC_DIR)/utils/utils.c \
              $(SRC_DIR)/input/movement.c \
              $(SRC_DIR)/input/input.c \
              $(SRC_DIR)/parser/map.c \
              $(SRC_DIR)/parser/parser.c \
              $(SRC_DIR)/parser/texture.c \
              $(SRC_DIR)/parser/texture_load.c \
              $(SRC_DIR)/parser/validation.c \
              $(SRC_DIR)/render/render.c \
              $(SRC_DIR)/render/ray.c \
              $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c \
              $(PRINTF_DIR)/ft_printf.c \
              $(PRINTF_DIR)/ft_printf_func.c

OBJS        = $(SRC:.c=.o)

INCLUDES    = -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR)

MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re