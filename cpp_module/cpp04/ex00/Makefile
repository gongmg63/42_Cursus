CXX		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98 #-fsanitize=address
SRCS	=	main.cpp Animal.cpp Cat.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp WrongDog.cpp
OBJS	=	$(SRCS:.cpp=.o)
HEADER	=	Animal.hpp Cat.hpp Dog.hpp WrongAnimal.hpp WrongCat.hpp WrongDog.hpp
NAME	=	ex00

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
