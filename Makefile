VPATH = %.c parse:utils

SRCS	= 	init.c atort.c ft_double_list.c ft_error.c \
			parse.c parse_resolution.c parse_ambient.c \
			parse_cam.c parse_light.c parse_sp.c parse_pl.c \
			parse_cy.c parse_sq.c parse_tr.c

TEST	= test.c

LIBFT	= libft/libft.a

MLX		= mlx/libmlx.a



HDRS	= includes/

OBJS	= $(SRCS:c=o)

NAME	= miniRT

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

#comp init.c parse/parse* libft/ft* libft/get_next_line* utils/* test.c  -Iincludes -framework OpenGL -framework AppKit libmlx.a

$(NAME):	$(OBJS) $(HDRS) $(LIBFT) $(MLX)
			@cp $(LIBFT) .
			@cp $(MLX) .
			ar rc $(NAME) $(OBJS) $(HDR)
			@echo "\033[32m||miniRT is compiled sucsessfully||\033[0m"

$(LIBFT):	
			@$(MAKE) -C libft
			@echo "\033[1;32m||libft is compiled sucsessfully||\033[0m"

$(MLX):	
			@$(MAKE) -C mlx
			@echo "\033[1;32m||libmlx is compiled sucsessfully||\033[0m"

%.o:		%.c $(HDRS) Makefile 
			$(CC) $(CFLAGS) -c -I$(HDRS) $<
		
all:		$(LIBFT) $(MLX) $(NAME)

clean:	
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norm:
			norminette *

.PHONY:		all clean fclean re norm