SRCS	= ft_strlen.c ft_strdup.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_itoa.c ft_putnbr_fd.c ft_split.c


HDRS	= libft.h

BSRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BOBJS	= ${BSRCS:c=o}

OBJS	= ${SRCS:c=o}

NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror


${NAME}:	${OBJS} ${HDRS}
			ar rs ${NAME} ${OBJS} ${HDRS}

%.o:		%.c Makefile libft.h
			$(CC) $(CFLAGS) -I $(HDRS) -c $<
		
all:		${NAME}

clean:	
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS} ${BOBJS}
			ar rs ${NAME} ${OBJS} ${BOBJS} ${HDRS}

norm:
			norminette *

.PHONY:		all clean fclean re norm bonus

