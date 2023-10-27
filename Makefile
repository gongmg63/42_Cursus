CFLAGS = -Wall -Wextra -Werror
SRCS_MANDATORY = ft_isalpha.c ft_memcmp.c ft_strdup.c ft_strnstr.c ft_atoi.c ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrchr.c ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c ft_calloc.c ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = libft.a
HEADER = libft.h

all : $(NAME)

$(NAME) : $(OBJS_MANDATORY)
	ar -rc $(NAME) $(OBJS_MANDATORY) $(HEADER)

%.o : %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean : 
	make clean
	rm -f $(NAME)

re : 
	make fclean 
	make all

bonus : $(OBJS_MANDATORY) $(OBJS_BONUS)
	ar -rc $(NAME) $(OBJS_MANDATORY) $(OBJS_BONUS) $(HEADER)

%.o : %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re bonus
