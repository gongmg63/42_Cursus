CC			=	cc
CFLAGS		=	-g -Wall -Wextra -Werror -pthread -fsanitize=thread
SRCS		=	philo.c philo_behavior.c ft_atoi.c thread.c thread_utils.c
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
