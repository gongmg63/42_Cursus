NAME        = .inception

all     : $(NAME)

$(NAME) :
	@touch $(NAME)
	mkdir -p /home/mkong/data/wp
	mkdir -p /home/mkong/data/db
	cd ./srcs && docker-compose up --build -d

down    : 
	cd ./srcs && docker-compose down
	@rm -rf $(NAME)

clean   :
	make down
	docker system prune -a

fclean  :
	make clean
	docker volume rm -f srcs_db srcs_wp
	sudo rm -rf /home/mkong/data/wp/*
	sudo rm -rf /home/mkong/data/db/*

re      :
	make fclean
	make all

em  :
	@cd ./srcs && docker-compose exec mariadb bash

en  :
	@cd ./srcs && docker-compose exec nginx bash

ew  :
	@cd ./srcs && docker-compose exec wordpress bash

lm :
	@cd ./srcs && docker-compose logs mariadb

lw :
	@cd ./srcs && docker-compose logs wordpress

ln :
	@cd ./srcs && docker-compose logs nginx

ps	:
	@cd ./srcs && docker-compose ps


.PHONY  : all down clean fclean re em en ew ps