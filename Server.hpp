#pragma once

#include "essential.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Client;
class Channel;

class Server {
public :
	Server	(const char* port, const char* password);

	const std::map<std::string, Channel *>&	getChannelList() const;
	const std::map<int, Client *>&			getClientList() const;
	const std::string&		getPassword() const;
	const int getPort() const;
	const int getFd() const;
	const int getKq() const;

	void	setServer(std::vector<struct kevent>& change_list);
	void	addClient(std::vector<struct kevent>& change_list);
	void	disconnectClient(int client_fd);

	void	createChannel(Client* first_client, std::string ch_name);
private :
	std::map<std::string, Channel *>	_channel_list;
	std::map<std::string, Client *>		_client_list;
	struct sockaddr_in	_server_addr;
	std::string	_password;
	int	_port;
	int	_fd;
	int	_kq;
};

void	exitMsg(const std::string& msg) {
	std::cerr << msg << "\n";
	exit(EXIT_FAILURE);
}

void changeEvents(std::vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    change_list.push_back(temp_event);	
}

const std::map<std::string, Channel *>&	Server::getChannelList() const { return (_channel_list); }
const std::map<int, Client *>&			Server::getClientList() const { return (_client_list); }
const std::string&		Server::getPassword() const { return (_password); }
const int Server::getPort() const { return (_port); }
const int Server::getFd() const { return (_fd); }
const int Server::getKq() const { return (_kq); }

Server::Server(const char* port, const char* password) {
	for (int i = 0; port[i]; ++i)
		if (!isdigit(port[i]))
			exitMsg("port number error");
	_port = atoi(port);
	_password = password;
}

void	Server::disconnectClient(int client_fd) {
	std::cout << "client disconnected: " << client_fd << "\n";
	close(client_fd);
	delete _client_list[client_fd];
	_client_list.erase(client_fd);
}

void	Server::setServer(std::vector<struct kevent>& change_list) {
	_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		exitMsg("socket error\n" + std::string(strerror(errno)));
	memset(&_server_addr, 0, sizeof(_server_addr));
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_server_addr.sin_port = htons(_port);
	if (bind(_fd, (struct sockaddr *)(&_server_addr), sizeof(_server_addr)) == -1)
		exitMsg("bind error\n" + std::string(strerror(errno)));
	if (listen(_fd, 10) == -1) //최대연결 요청 수를 몇으로 해야할 지..?
		exitMsg("listen error\n" + std::string(strerror(errno)));
	fcntl(_fd, F_SETFL, O_NONBLOCK);
	
	_kq = kqueue();
	if (_kq == -1)
		exitMsg("kqueue error\n" + std::string(strerror(errno)));
	changeEvents(change_list, _fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

void	Server::addClient(std::vector<struct kevent>& change_list) {
	int	client_fd;

	client_fd == accept(_fd, NULL, NULL);
	if (client_fd == -1)
		exitMsg("accept error\n" + std::string(strerror(errno)));
	std::cout << "accept new clinet: " << client_fd << "\n";
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	changeEvents(change_list, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	changeEvents(change_list, client_fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);

	Client *new_client = new Client(client_fd);
	_client_list[client_fd] = new_client;
}
