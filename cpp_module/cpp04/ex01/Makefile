CXX		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
SRCS	=	main.cpp Animal.cpp Dog.cpp Cat.cpp Brain.cpp
OBJS	=	$(SRCS:.cpp=.o)
HEADER	=	Animal.hpp Dog.hpp Cat.hpp Brain.hpp
NAME	=	ex01

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp $(HEADER)
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
