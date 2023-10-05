CFLAGS = -Wall -Wextra -Werror
SRCS = ft_*.c
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
