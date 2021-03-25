SRCS	= 	parse/parse.c \
			parse/parse_resolution.c \
			parse/parse_ambient.c \
			parse/parse_cam.c \
			parse/parse_light.c \
			parse/parse_sp.c \
			parse/parse_pl.c \
			parse/parse_cy.c \
			parse/parse_sq.c \
			parse/parse_tr.c \
			raytrace/sphere.c \
			raytrace/plane.c \
			raytrace/triangle.c \
			raytrace/square.c \
			raytrace/cylinder.c \
			raytrace/lightning.c \
			raytrace/shadow_intersection.c \
			utils/vector_math.c \
			utils/color.c \
			utils/canvastoviewport.c \
			utils/init_img.c \
			utils/atort.c \
			utils/ft_double_list.c \
			utils/ft_error.c \
			utils/keyhooks.c \
			utils/ft_create_bmp.c \
			main.c

LIBFT	= libft/libft.a

MLX		= mlx/libmlx.dylib

MLX_FLAGS	= -lz -framework OpenGL -framework AppKit libmlx.dylib

HDRS	= includes

NAME	= miniRT

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(LIBFT) $(MLX) $(HDRS) $(SRCS)
			@cp $(LIBFT) .
			@cp $(MLX) .
			$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) -I./includes -I./mlx -I./libft libft.a libmlx.dylib  -o $(NAME)
			@echo "\033[36mminiRT is compiled successfully\n"
			@echo "Now you can run the program with \033[1;35m./miniRT {map to render of .rt extension}\n\033[0m"

$(LIBFT):	
			@$(MAKE) -C ./libft
			@echo "\033[36mlibft is compiled successfully\n\033[0m"

$(MLX):	
			@$(MAKE) -C ./mlx
			@echo "\033[36m\nMinilibX is compiled successfully\n\033[0m"
		
all:		$(NAME)

clean:	
			$(RM) $(NAME)

fclean:		clean
			make fclean -C libft/
			make clean -C mlx/
			$(RM) $(NAME) libft.a libmlx.dylib *.bmp
			@echo "\033[36mDone!\n\033[0m"

re:			fclean all

norm:
			norminette includes/ libft/ parse/ raytrace/ utils/

.PHONY:		all clean fclean re norm