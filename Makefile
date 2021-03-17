VPATH = %.c parse:utils

SRCS	= 	utils/atort.c utils/ft_double_list.c utils/ft_error.c \
			parse/parse.c parse/parse_resolution.c parse/parse_ambient.c \
			parse/parse_cam.c parse/parse_light.c parse/parse_sp.c parse/parse_pl.c \
			parse/parse_cy.c parse/parse_sq.c parse/parse_tr.c \
			utils/canvastoviewport.c init_img.c raytrace/sphere.c raytrace/plane.c \
			raytrace/lightning.c raytrace/triangle.c raytrace/square.c raytrace/shadow_intersection.c \
			utils/vector_math.c utils/color.c raytrace/cylinder.c keyhooks/keyhooks.c \
			keyhooks/actions.c

TEST	= test.c

LIBFT	= libft/libft.a

MLX		= mlx/libmlx.dylib

MLX_FLAGS	= -lz -framework OpenGL -framework AppKit libmlx.dylib

HDRS	= includes

NAME	= miniRT

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g

$(NAME):	$(LIBFT) $(MLX) $(HDRS) $(SRCS)
			@cp $(LIBFT) .
			@cp $(MLX) .
			$(CC) $(CFLAGS) $(SRCS) init.c $(MLX_FLAGS) -Iincludes -I./mlx libft.a libmlx.dylib  -o $(NAME)
			@echo "\033[32mminiRT is compiled sucsessfully\033[0m"

$(LIBFT):	
			@$(MAKE) -C ./libft
			@echo "\033[32mlibft is compiled sucsessfully\033[0m"

$(MLX):	
			@$(MAKE) -C ./mlx
			@echo "\033[32m\nlibmlx is compiled sucsessfully\033[0m"
		
all:		$(LIBFT) $(MLX) $(SRCS)
			$(NAME)

clean:	
			$(RM) $(NAME) 

fclean:		clean
			make fclean -C libft/
			make clean -C mlx/
			$(RM) $(NAME) libft.a libmlx.dylib

re:			fclean all

norm:
			norminette *

.PHONY:		all clean fclean re norm