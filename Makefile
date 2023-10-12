CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isalpha.c ft_memcmp.c ft_strdup.c ft_strnstr.c ft_atoi.c ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrchr.c ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c ft_calloc.c ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c
OBJS = $(SRCS:.c = .o)
NAME = libft.a
HEADER = libft.h

$(NAME) : $(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o : %.c $(HEADER)
	cc -c $(CFLAGS) $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : 
	rm -rf $(NAME)

re : fclean all

all : $(NAME)

.PHONY : all clean fclean re
