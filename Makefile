VPATH = %.c parse:utils

SRCS	= 	utils/atort.c utils/ft_double_list.c utils/ft_error.c \
			parse/parse.c parse/parse_resolution.c parse/parse_ambient.c \
			parse/parse_cam.c parse/parse_light.c parse/parse_sp.c parse/parse_pl.c \
			parse/parse_cy.c parse/parse_sq.c parse/parse_tr.c \
			raytrace/canvastoviewport.c init_img.c

TEST	= test.c

LIBFT	= libft/libft.a

MLX		= mlx/libmlx.a

MLX_FLAGS	= -framework OpenGL -framework AppKit

HDRS	= includes

NAME	= miniRT

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(LIBFT) $(MLX) $(HDRS) $(SRCS)
			@cp $(LIBFT) .
			@cp $(MLX) .
			$(CC) $(CFLAGS) $(SRCS) init.c $(MLX_FLAGS) -Iincludes libft.a libmlx.a  -o $(NAME)
			@echo "\033[32m||miniRT is compiled sucsessfully||\033[0m"

$(LIBFT):	
			@$(MAKE) -C ./libft
			@echo "\033[32m||libft is compiled sucsessfully||\033[0m"

$(MLX):	
			@$(MAKE) -C mlx
			@echo "\033[32m\n||libmlx is compiled sucsessfully||\033[0m"
		
all:		$(LIBFT) $(MLX) $(SRCS)
			$(NAME)

clean:	
			$(RM) $(NAME) 

fclean:		clean
			make fclean -C libft/
			make clean -C mlx/
			$(RM) $(NAME) libft.a libmlx.a

re:			fclean all

norm:
			norminette *

.PHONY:		all clean fclean re norm