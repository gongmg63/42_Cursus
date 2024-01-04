CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
SRCS		=	ft_deque.c ft_deque_utils.c push_swap.c radix_sort.c operations.c
NAME		=	push_swap
SUB_LIB		=	libft.a
SUB_LIBDIR	=	./libft
SUB_PRI		=	libftprintf.a
SUB_PRIDIR	=	./ft_printf

all : $(NAME)

$(NAME) : $(SRCS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_PRIDIR)/$(SUB_PRI)
	cc $(CFLAGS) -o $(NAME) $(SRCS) -I$(SUB_LIBDIR) $(SUB_LIBDIR)/$(SUB_LIB) -I$(SUB_PRIDIR) $(SUB_PRIDIR)/$(SUB_PRI)

$(SUB_LIBDIR)/$(SUB_LIB) :
	make -C $(SUB_LIBDIR)

$(SUB_PRIDIR)/$(SUB_PRI) :
	make -C $(SUB_PRIDIR)

clean : 
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