CXX		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98 # -g3 -fsanitize=address
SRCS	=	$(wildcard *.cpp)
OBJS	=	$(SRCS:.cpp=.o)
HEADER	=	$(wildcard *.hpp)
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
