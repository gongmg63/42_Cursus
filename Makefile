CC			=	cc
CFLAGS		=	-g -Wall -Wextra -Werror
SUB_LIBDIR	=	./libft
SUB_LIB		=	libft.a
SUB_GNLDIR	=	./gnl
SUB_GNL		=	libgnl.a
BONUS_DIR	=	./bonus
SRCS_MAN	=	pipex.c pipex_utils.c exec_cmd.c
OBJS_MAN	=	$(SRCS_MAN:.c=.o)
SRCS_BONUS	=	$(BONUS_DIR)/here_doc_bonus.c $(BONUS_DIR)/pipex_bonus.c $(BONUS_DIR)/pipex_utils_bonus.c $(BONUS_DIR)/exec_cmd_bonus.c
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
SRCS_LIB	=	$(SUB_LIBDIR)/ft_isalpha.c $(SUB_LIBDIR)/ft_memcmp.c $(SUB_LIBDIR)/ft_strdup.c $(SUB_LIBDIR)/ft_strnstr.c $(SUB_LIBDIR)/ft_atoi.c $(SUB_LIBDIR)/ft_isascii.c $(SUB_LIBDIR)/ft_memcpy.c $(SUB_LIBDIR)/ft_strlcat.c $(SUB_LIBDIR)/ft_strrchr.c $(SUB_LIBDIR)/ft_bzero.c $(SUB_LIBDIR)/ft_isdigit.c $(SUB_LIBDIR)/ft_memmove.c $(SUB_LIBDIR)/ft_strlcpy.c $(SUB_LIBDIR)/ft_tolower.c $(SUB_LIBDIR)/ft_calloc.c $(SUB_LIBDIR)/ft_isprint.c $(SUB_LIBDIR)/ft_memset.c $(SUB_LIBDIR)/ft_strlen.c $(SUB_LIBDIR)/ft_toupper.c $(SUB_LIBDIR)/ft_isalnum.c $(SUB_LIBDIR)/ft_memchr.c $(SUB_LIBDIR)/ft_strchr.c $(SUB_LIBDIR)/ft_strncmp.c $(SUB_LIBDIR)/ft_substr.c $(SUB_LIBDIR)/ft_strjoin.c $(SUB_LIBDIR)/ft_strtrim.c $(SUB_LIBDIR)/ft_split.c $(SUB_LIBDIR)/ft_itoa.c $(SUB_LIBDIR)/ft_strmapi.c $(SUB_LIBDIR)/ft_striteri.c $(SUB_LIBDIR)/ft_putchar_fd.c $(SUB_LIBDIR)/ft_putstr_fd.c $(SUB_LIBDIR)/ft_putendl_fd.c $(SUB_LIBDIR)/ft_putnbr_fd.c
SRCS_GNL	=	$(SUB_GNLDIR)/get_next_line.c $(SUB_GNLDIR)/get_next_line_utils.c
NAME		=	pipex

all : $(NAME) LAST_ALL

bonus : LAST_BONUS

$(NAME) : $(OBJS_MAN) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_GNLDIR)/$(SUB_GNL) LAST_ALL
	$(CC) $(CFLAGS) $(OBJS_MAN) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_GNLDIR)/$(SUB_GNL) -o $(NAME)
	
LAST_ALL : 
	rm -rf LAST_BONUS
	rm -rf $(OBJS_BONUS)
	touch $@

LAST_BONUS : $(OBJS_BONUS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_GNLDIR)/$(SUB_GNL)
	rm -rf LAST_ALL
	rm -rf $(OBJS_MAN)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_GNLDIR)/$(SUB_GNL) -o $(NAME)
	touch $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

$(SUB_GNLDIR)/$(SUB_GNL) : $(SRCS_GNL)
	make -C $(SUB_GNLDIR)

clean : 
	rm -rf $(OBJS_MAN)
	rm -rf $(OBJS_BONUS)
	make -C $(SUB_LIBDIR) clean
	make -C $(SUB_GNLDIR) clean

fclean : 
	make clean
	rm -rf $(NAME)
	rm -rf LAST_ALL LAST_BONUS
	make -C $(SUB_LIBDIR) fclean
	make -C $(SUB_GNLDIR) fclean

re :
	make fclean
	make all

.PHONY : all clean fclean re bonus
