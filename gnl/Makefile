CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	get_next_line.c get_next_line_utils.c
OBJS		=	$(SRCS:.c=.o)
NAME		=	libgnl.a
HEADER		=	get_next_line.h

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $(NAME) $(OBJS) $(HEADER)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : 
	make clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
