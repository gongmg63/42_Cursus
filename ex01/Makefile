CXX		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
SRCS	=	phone.cpp \
			Phonebook.cpp \
			Contact.cpp
OBJS	=	$(SRCS:.cpp=.o)
NAME	=	phonebook

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean : 
	@rm -rf $(OBJS)

fclean : 
	@make clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make all

.PHONY : all clean fclean re
