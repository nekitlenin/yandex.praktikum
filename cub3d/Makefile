CC=gcc
# CFLAGS= -Wall -Werror -Wextra -Ilibft -Imlx -I.
CFLAGS= -g -Ilibft -Imlx -I.
MLX= -Lmlx -Llibft -lft -lmlx -framework OpenGL -framework AppKit 
SRCS=main.c src/check_map.c src/parser.c src/takepic.c src/sprites.c src/init.c \
		src/manipulation.c src/rendering.c src/drawing.c src/vectors.c src/cast.c\
		src/check_add.c
	
OBJ=$(SRCS:.c=.o)
NAME=cub3D

all: mlx libft $(NAME)

mlx:
	@make -C ./mlx

libft: 
	@make -C ./libft

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MLX)

$(OBJ): cub.h

clean:
	rm -rf $(OBJ) 
	@make clean -C ./libft
	@make clean -C ./mlx

fclean: clean
	rm -rf $(NAME)
	@make fclean -C ./libft

re: fclean libft all

.PHONY: all mlx libft clean fclean re
