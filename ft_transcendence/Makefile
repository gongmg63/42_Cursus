NAME        = .be

all     : $(NAME)

$(NAME) :
	@touch $(NAME)
	cd ./res && docker compose up --build -d

down    : 
	cd ./res && docker compose down
	@rm -rf $(NAME)

restart    : 
	cd ./res && docker compose restart
clean   :
	make down
	docker system prune -af

fclean  :
	make clean
	cd ./res && docker compose down -v
	rm -rf ./res/requirements/postgresql/volumes/*

re      :
	make fclean
	make all

ed  :
	@cd ./res && docker-compose exec django /bin/sh 

en  :
	@cd ./res && docker-compose exec nginx /bin/sh 

ep  :
	@cd ./res && docker-compose exec postgres /bin/sh

ld :
	@cd ./res && docker-compose logs django

ln :
	@cd ./res && docker-compose logs nginx

lp :
	@cd ./res && docker-compose logs postgres

ps	:
	@cd ./res && docker-compose ps


.PHONY  : all down clean fclean ed ep ld lp ps