CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
SRCS_CUB	=	cub3d.c \
				event.c \
				draw.c \
				calc_ray.c
OBJS_CUB	=	$(SRCS_CUB:.c=.o)
SRCS_LIB	=	$(SUB_LIBDIR)/ft_isalpha.c $(SUB_LIBDIR)/ft_memcmp.c $(SUB_LIBDIR)/ft_strdup.c $(SUB_LIBDIR)/ft_strnstr.c $(SUB_LIBDIR)/ft_atoi.c $(SUB_LIBDIR)/ft_isascii.c $(SUB_LIBDIR)/ft_memcpy.c $(SUB_LIBDIR)/ft_strlcat.c $(SUB_LIBDIR)/ft_strrchr.c $(SUB_LIBDIR)/ft_bzero.c $(SUB_LIBDIR)/ft_isdigit.c $(SUB_LIBDIR)/ft_memmove.c $(SUB_LIBDIR)/ft_strlcpy.c $(SUB_LIBDIR)/ft_tolower.c $(SUB_LIBDIR)/ft_calloc.c $(SUB_LIBDIR)/ft_isprint.c $(SUB_LIBDIR)/ft_memset.c $(SUB_LIBDIR)/ft_strlen.c $(SUB_LIBDIR)/ft_toupper.c $(SUB_LIBDIR)/ft_isalnum.c $(SUB_LIBDIR)/ft_memchr.c $(SUB_LIBDIR)/ft_strchr.c $(SUB_LIBDIR)/ft_strncmp.c $(SUB_LIBDIR)/ft_substr.c $(SUB_LIBDIR)/ft_strjoin.c $(SUB_LIBDIR)/ft_strtrim.c $(SUB_LIBDIR)/ft_split.c $(SUB_LIBDIR)/ft_itoa.c $(SUB_LIBDIR)/ft_strmapi.c $(SUB_LIBDIR)/ft_striteri.c $(SUB_LIBDIR)/ft_putchar_fd.c $(SUB_LIBDIR)/ft_putstr_fd.c $(SUB_LIBDIR)/ft_putendl_fd.c $(SUB_LIBDIR)/ft_putnbr_fd.c
NAME		=	cub3D
SUB_LIB		=	libft.a
SUB_LIBDIR	=	./libft
MLX_LIBDIR	=	./mlx
MLX_LIB		=	libmlx.dylib

all : $(NAME)

$(NAME) : $(OBJS_CUB) $(SUB_LIBDIR)/$(SUB_LIB) $(MLX_LIBDIR)/$(MLX_LIB)
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit $(OBJS_CUB) -Lmlx -lmlx $(SUB_LIBDIR)/$(SUB_LIB) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	
$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

$(MLX_LIBDIR)/$(MLX_LIB) : 
	make -C $(MLX_LIBDIR)

%.o : %.c
	$(CC) $(CFLAGS) -I./mlx -c $< -o $@

clean : 
	rm -rf $(OBJS_CUB)
	make -C $(SUB_LIBDIR) clean

fclean : 
	make clean
	rm -rf $(NAME)
	make -C $(SUB_LIBDIR) fclean
	make -C $(MLX_LIBDIR) clean

re :
	make fclean
	make all

.PHONY : all clean fclean re
