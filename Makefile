CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
SRCS_SO		=	ft_stack.c get_next_line_utils.c get_next_line.c map_checker_utils.c map_checker.c map_maker.c so_long.c
OBJS_SO		=	$(SRCS_SO:.c=.o)
NAME		=	so_long
SUB_LIB		=	libft.a
SUB_LIBDIR	=	./libft

all : $(NAME)

$(NAME): $(OBJ_SO)
	$(CC) $(OBJ_SO) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	
$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

%.o : %.c
	$(CC)  $(CFLAGS) -Imlx -c $< -o $@

clean : 
	make -C $(SUB_LIBDIR) clean

fclean : 
	make clean
	rm -rf $(NAME)
	make -C $(SUB_LIBDIR) fclean

re :
	make fclean
	make all

.PHONY : all clean fclean re
