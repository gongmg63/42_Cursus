CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	ft_deque.c ft_deque.utils.c
OBJS		=	$(SRC:.c=.o)
NAME		=	push_swap
SUB_LIB		=	libft.a
SUB_LIBDIR	=	./libft
SUB_PRI		=	libftprintf.a
SUB_PRIDIR	=	./ft_printf

all : $(NAME)

$(NAME) : $(OBJS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_PRIDIR)/$(SUB_PRI)
	cc $(CFLAGS) -o $(NAME) -I$(SUB_LIBDIR) $(SUB_LIBDIR)/$(SUB_LIB) -I$(SUB_PRIDIR) $(SUB_PRIDIR)/$(SUB_PRI)

$(SUB_LIBDIR)/$(SUB_LIB) :
	make -C $(SUB_LIBDIR)

$(SUB_PRIDIR)/$(SUB_PRI) :
	make -C $(SUB_PRIDIR)

$(OBJS) : $(SRCS)
	cc $(CFLAGS) -c $(SRCS)

clean : 
	rm -rf $(OBJS)
	make -C $(SUB_LIBDIR) clean
	make -C $(SUB_PRIDIR) clean

fclean : 
	make clean
	rm -rf $(NAME)
	make -C $(SUB_LIBDIR) fclean
	make -C $(SUB_PRIDIR) fclean

re :
	make fclean
	make all

.PHONY : all clean fclean re