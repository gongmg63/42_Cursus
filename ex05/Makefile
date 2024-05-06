CXX		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
SRCS	=	main.cpp Harl.cpp
OBJS	=	$(SRCS:.cpp=.o)
NAME	=	ex04

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : 
	make clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
