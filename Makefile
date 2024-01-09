CFLAGS		=	-Wall -Wextra -Werror
SRCS_PS		=	ft_deque.c ft_deque_utils.c push_swap.c radix_sort.c op_p.c op_r.c op_rr.c op_s.c normalization.c and_under_five.c
SRCS_LIB	=	$(SUB_LIBDIR)/ft_isalpha.c $(SUB_LIBDIR)/ft_memcmp.c $(SUB_LIBDIR)/ft_strdup.c $(SUB_LIBDIR)/ft_strnstr.c $(SUB_LIBDIR)/ft_atoi.c $(SUB_LIBDIR)/ft_isascii.c $(SUB_LIBDIR)/ft_memcpy.c $(SUB_LIBDIR)/ft_strlcat.c $(SUB_LIBDIR)/ft_strrchr.c $(SUB_LIBDIR)/ft_bzero.c $(SUB_LIBDIR)/ft_isdigit.c $(SUB_LIBDIR)/ft_memmove.c $(SUB_LIBDIR)/ft_strlcpy.c $(SUB_LIBDIR)/ft_tolower.c $(SUB_LIBDIR)/ft_calloc.c $(SUB_LIBDIR)/ft_isprint.c $(SUB_LIBDIR)/ft_memset.c $(SUB_LIBDIR)/ft_strlen.c $(SUB_LIBDIR)/ft_toupper.c $(SUB_LIBDIR)/ft_isalnum.c $(SUB_LIBDIR)/ft_memchr.c $(SUB_LIBDIR)/ft_strchr.c $(SUB_LIBDIR)/ft_strncmp.c $(SUB_LIBDIR)/ft_substr.c $(SUB_LIBDIR)/ft_strjoin.c $(SUB_LIBDIR)/ft_strtrim.c $(SUB_LIBDIR)/ft_split.c $(SUB_LIBDIR)/ft_itoa.c $(SUB_LIBDIR)/ft_strmapi.c $(SUB_LIBDIR)/ft_striteri.c $(SUB_LIBDIR)/ft_putchar_fd.c $(SUB_LIBDIR)/ft_putstr_fd.c $(SUB_LIBDIR)/ft_putendl_fd.c $(SUB_LIBDIR)/ft_putnbr_fd.c
SRCS_PF		=	$(SUB_PRIDIR)/ft_printf.c $(SUB_PRIDIR)/ft_putchar_va.c $(SUB_PRIDIR)/ft_putstr_va.c $(SUB_PRIDIR)/ft_putnbr_va.c $(SUB_PRIDIR)/ft_puthex_va.c $(SUB_PRIDIR)/ft_putadd_va.c $(SUB_PRIDIR)/ft_strlen.c $(SUB_PRIDIR)/ft_itohex.c
NAME		=	push_swap
SUB_LIB		=	libft.a
SUB_LIBDIR	=	./libft
SUB_PRI		=	libftprintf.a
SUB_PRIDIR	=	./ft_printf

all : $(NAME)

$(NAME) : $(SRCS_PS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_PRIDIR)/$(SUB_PRI)
	cc $(CFLAGS) -o $(NAME) $(SRCS_PS) -I$(SUB_LIBDIR) $(SUB_LIBDIR)/$(SUB_LIB) -I$(SUB_PRIDIR) $(SUB_PRIDIR)/$(SUB_PRI)

$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

$(SUB_PRIDIR)/$(SUB_PRI) : $(SRCS_PF)
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
