CC = gcc

CFLAGS = -Wall -Wextra -Werror

ENDFLAGS = -framework OpenGL -framework AppKit

NAME = rtv1

SRCS = main.c draw.c util.c sphere.c plane.c cyl.c cone.c \
	ft_atof.c load_scene.c generic_dists.c rotate.c rot_trans_input.c \
	vector_funs.c read_vec.c key_stuff.c color_conversion.c alt_cone.c

OBJ = $(SRCS:.c=.o)

LIBS = ./minilibx_macos/libmlx.a ./libft/libft.a

.PHONY: all comp clean fclean re

all: $(NAME)

$(OBJ): $(SRCS)
	$(CC) -c $(CFLAGS) $(SRCS)

$(LIBS): 
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx_macos

$(NAME): $(OBJ) $(LIBS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBS) $(ENDFLAGS)

clean:
	@rm -f $(OBJ)
	$(MAKE) -C ./libft/ clean
	$(MAKE) -C ./minilibx_macos/ clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./libft/ fclean
	$(MAKE) -C ./minilibx_macos/ clean

re: fclean all
