CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror #-g -pthread -fsanitize=thread
SRCS		=	philo_bonus.c behavior_bonus.c ft_atoi_bonus.c process_bonus.c fork_bonus.c
OBJS		=	$(SRCS:.c=.o)
NAME		=	philo

all : $(NAME)

bonus : all

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

.PHONY : all clean fclean re bonus
