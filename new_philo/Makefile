CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror #-g -pthread -fsanitize=thread
SRCS		=	philo.c behavior.c ft_atoi.c thread.c fork.c
OBJS		=	$(SRCS:.c=.o)
NAME		=	philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : 
	make clean
	rm -rf $(NAME)
	
re :
	make fclean
	make all

.PHONY : all clean fclean re
