NAME        = .inception

all     : $(NAME)

$(NAME) :
	@touch $(NAME)
	cd ./srcs && docker-compose up --build

down    : 
	cd ./srcs && docker-compose down
	@rm -rf $(NAME)

clean   :
	make down
	docker system prune -a

fclean  :
	make clean

re      :
	make fclean
	make all

em  :
	@cd ./srcs && docker-compose exec mariadb bash

en  :
	@cd ./srcs && docker-compose exec nginx bash

ew  :
	@cd ./srcs && docker-compose exec wordpress bash

ps	:
	@cd ./srcs && docker-compose ps


.PHONY  : all down clean fclean re em en ew ps