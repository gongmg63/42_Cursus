CFLAGS = -Wall -Wextra -Werror
SRCS_MANDATORY = ft_printf.c ft_putchar_va.c ft_putstr_va.c ft_putnbr_va.c ft_putunnbr_va.c ft_puthex_va.c ft_putadd_va.c ft_printf_util.c
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
NAME = libftprintf.a
HEADER = ft_printf.h

all : $(NAME)

$(NAME) : $(OBJS_MANDATORY)
	ar -rc $(NAME) $(OBJS_MANDATORY) $(HEADER)

%.o : %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(OBJS_MANDATORY)

fclean : 
	make clean
	rm -f $(NAME)

re : 
	make fclean 
	make all

.PHONY : all clean fclean re
