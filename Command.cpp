#include "Command.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include <sstream>

Command::Command() {
	_cmdlist.push_back("PASS");//o
	_cmdlist.push_back("NICK");//o
	_cmdlist.push_back("USER");//0
	_cmdlist.push_back("JOIN");//o 아마
	_cmdlist.push_back("INVITE");//o
	_cmdlist.push_back("KICK");//o
	_cmdlist.push_back("TOPIC");//o
	_cmdlist.push_back("QUIT");//서버 나가면서 메세지 뱉기
	_cmdlist.push_back("PRIVMSG");//o
	_cmdlist.push_back("MODE");
}

void Command::handleCmd(Server& server, Client* client, const std::string& msg) {
//이 함수를 통해서 command 호출
	if (parseCmd(client, msg) == false)
		return ;
	//pass, nick, user 순서대로 됐는지 분기 쪼개야됨
	if (_cmd == "PASS")
		pass(server, client);
	if (client->getPass()) { //Pass true 여야 동작가능 
		if (_cmd == "NICK")
			nick(server, client);
		if (client->getNick()) {
			if (_cmd == "USER")
				user(client);
			else if (client->getNick()) {
				if (_cmd == "JOIN")
					join(server, client);
				else if (_cmd == "INVITE")
					invite(server, client);
				else if (_cmd == "KICK")
					kick(server, client);
				else if (_cmd == "TOPIC")
					topic(server, client);
				else if (_cmd == "QUIT")
					quit(server, client);
				else if (_cmd == "PRIVMSG")
					privmsg(server, client);
				else if (_cmd == "MODE")
					mode(server, client);
			}
			else {
				client->setMessage(handleResponse("*", 451));
				return ;
			}
		}
		else {
			// ERR_NOTREGISTERED (451)
			client->setMessage(handleResponse("*", 451));
			return ;
		}
	}
	else {// pass 필요
		//pass를 입력안해서nick이 없는데 어떻게 response?
		// 정보가 없을때 nickname 을 *로 표시
		client->setMessage(handleResponse("*", 451));
		return ;
	}
}

bool Command::parseCmd(Client* client, const std::string& msg) {
	_params.clear();
	std::istringstream ss(msg);
	std::string buf;

	std::getline(ss, _cmd, ' ');//command
	if (std::find(_cmdlist.begin(), _cmdlist.end(), _cmd) == _cmdlist.end()){
		//421
		if (client->getNick())
			client->setMessage(handleResponse(client->getNickname(), 421));
		else 
			client->setMessage(handleResponse("*", 421));//ERR_UNKNOWNCOMMAND
		return false;
	}
	while (std::getline(ss, buf)) {
		_params.push_back(buf);
	}
	return true;
}

void Command::pass(Server& server, Client* client) {
	//PASS <password>
	if (_params.empty()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "PASS"));
		return ;
	}
	if (client->getPass()) { //Pass 이미 쳤을때
		client->setMessage(handleResponse(client->getNickname(), ERR_ALREADYREGISTRED));
		return ;
	}
	if (_params[0] == server.getPassword())
		client->setPass(true);
}

void Command::nick(Server& server, Client* client) {
	//NICK <nickname>
	//want 코크풍선..
	//NICK 변경가능 

	if (_params.empty()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "NICK"));
		return ;
	}
	std::string nickname = _params[0];
	if (client->getNickname() == nickname)//같은닉네임으로 변경시도시 가만히
		return ;
	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#' || nickname[0] == '&') {
		client->setMessage(handleResponse("*", ERR_ERRONEUSNICKNAME, nickname));
		return ;
	}
	for (size_t i = 0; nickname.size(); ++i) {
		if (nickname[i] == ' ' || nickname[i] == ',' || nickname[i] == '.' || nickname[i] == '*' ||
			nickname[i] == '?' || nickname[i] == '!' || nickname[i] == '@') {
			client->setMessage(handleResponse("*", ERR_ERRONEUSNICKNAME, nickname));
			return ;
		}
	}
	//중복 닉네임 고려 어떻게?
	if (nickname.length() > 9)
		return ;
	if (!server.findClient(nickname)) {
		// 중복닉 433ERR_NICKNAMEINUSE
		client->setMessage(handleResponse("*", ERR_NICKNAMEINUSE, nickname));
	}
	client->setNick(true);
	client->setNickname(nickname);
	client->setMessage("Your nickname has been set to " + nickname);// <- 어떻게? 
}

void Command::user(Client* client) {
	//USER <username> <hostname> <servername> :<realname>
	if (_params.size() < 4) { //<= 4 ?
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "USER"));
		return ;
	}
	if (client->getUser()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_ALREADYREGISTRED));
		return ;
	}
	client->setUser(true);
	client->setUsername(_params[0]);
	client->setHostname(_params[1]);
	client->setServername(_params[2]);
	client->setRealname(_params[3]);
}

void Command::join(Server& server, Client* client) {
	//JOIN <channel>{,<channel>} [<key>{,<key>}]
	//JOIN c1,c2,c3,c4 k1,k2 c4 = "hello,hi"
	//채널이름에 ',' , 7번, 공백 사용금지
	//JOIN 채널이름이 없으면 만들어서 server의 chanel
	if (_params.empty()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "JOIN"));
		return ;
	}
	std::map<std::string, std::string> key_map;
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	std::istringstream channel_ss(_params[0]);//channel 이름 만들때 확인필수
	// std::istringstream key_ss(_params[1]);//있을수도 있고 없을수도있음
	std::istringstream key_ss(_params.size() > 1 ? _params[1] : "");
	std::string channel_name;
	std::string key;

	//채널이름 #만있는거 안되게
	while (std::getline(channel_ss, channel_name, ',')) {
		if (channel_name[0] != '#'){
			client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, channel_name));
			std::getline(key_ss, key, ',');//이거 한번 밀리니까 해야될듯?
			continue ;
		}
		if (channel_name.find(6) != std::string::npos
			|| channel_name.find(':') != std::string::npos)//제어문자 6있을때
			client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, channel_name));
		if (!std::getline(key_ss, key, ','))
			key = "";
		key_map[channel_name] = key;
	}

	std::map<std::string, std::string>::iterator it = key_map.begin();
	for (; it != key_map.end(); ++it){
		std::string channel_name = it->first;
		std::string channel_key = it->second;
		if (channel_list.find(channel_name) != channel_list.end())
			channel_list[channel_name]->join(client, channel_key);
		else{
			server.createChannel(client, channel_name);//못찾으면 채널생성,
			channel_list[channel_name]->join(client, channel_key);
		}
	}
}

void	Command::invite(Server& server, Client* client){
	//INVITE <nickname> <channel>
	if (_params.size() < 2) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "INVITE"));
        return;
    }
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	//client_list를 std::string, Client *로 갖고있어야함

	if (!server.findClient(_params[0])){
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "INVITE"));
		return ;
	}
	if (channel_list.find(_params[1]) == channel_list.end()){
		client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, _params[1]));
		return ;
	}
	Client* invited_client = server.findClient(_params[0]);
	if (!invited_client) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHNICK, _params[0]));
		return ;
	}
	channel_list[_params[1]]->invite(client, server.findClient(_params[0]));
}

void	Command::kick(Server& server, Client* client){
	// KICK <channel> <user> [<comment>]
	std::map<std::string, Channel *> channel_list = server.getChannelList();

	if (_params.size() < 2) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "KICK"));
		return ;
	}
	std::string channel_name = _params[0];
	std::string target_name = _params[1];
	if (_params.size() >= 3) {
		std::string command = _params[2];
		channel_list[channel_name]->kick(client, server.findClient(target_name), command);
	}
	else
		channel_list[channel_name]->kick(client, server.findClient(target_name), "");
}

void	Command::topic(Server& server, Client* client) {
	//TOPIC <channel> [<topic>]
	//<topic>이 주어지지 않으면 topic 반환
	std::map<std::string, Channel *> channel_list = server.getChannelList();

	if (_params.size() < 1) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "TOPIC"));
		return ;
	}
	std::string channel_name = _params[0];
	if (_params.size() >= 2) {
		std::string topic = _params[1];
		channel_list[channel_name]->topic(client, topic);
	}
	else
		channel_list[channel_name]->topic(client, "");
}

void	Command::quit(Server& server, Client* client) {
	//QUIT <quit message>
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	std::vector<std::string> joined_channel = client->getJoinedChannel();
	if (_params.empty()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "QUIT"));
		return ;
	}
	for (unsigned int i = 0; i < joined_channel.size(); ++i)
		channel_list[joined_channel[i]]->quit(client);
	server.disconnectClient(client->getFd());// 이거맞아?
}

void	Command::privmsg(Server& server, Client* client) {
	//PRIVMSG <receiver>{,<receiver>} <text to be sent>
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	std::vector<std::string> joined_channel = client->getJoinedChannel();

	if (_params.size() < 2) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "PRIVMSG"));
		return ;
	}
	std::string receiver;
	std::string msg = _params[1];
	std::istringstream ss(_params[0]);
	while (std::getline(ss, receiver, ',')) {
		std::vector<std::string>::iterator it = std::find(joined_channel.begin(), joined_channel.end(), receiver);
		if (receiver[0] == '#') {//receiver가 채널일때
			if (channel_list.find(receiver) == channel_list.end())//채널이 존재하지 않을때
				client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, receiver));
			else if (it == joined_channel.end())//채널은 존재하는데, 참여하지 않은 상태에서
				client->setMessage(handleResponse(client->getNickname(), ERR_CANNOTSENDTOCHAN, receiver));
			else
				channel_list[receiver]->broadcast(messageFormat(PRIVMSG, client, receiver, msg));//여기에다가 포맷 맞춰서 보내기
		} else {//receiver가 client
			Client* receive_client = server.findClient(receiver);
			if (!receive_client)
				client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHNICK, receiver));
			else
				receive_client->setMessage(msg);
		}
	}
}

void	Command::mode(Server& server, Client* client) {
	//MODE <channel> {[+|-]|i|t|k|o|l} [<limit>] [<user>]
	//1. + - 인식 없으면 에러
	//2 + or - 둘중 하나만 받고 이후에 있는 옵션들 다적용
	//파라미터 없는 모드 : i, t
	//파라미터 있는 모드 : k, o, l
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	if (_params.size() < 1)
		std::cerr << "invalid numbers of params\n";
	//MODE <channel>일떄 answerMode()
	if (_params.size() == 2) {
		if (channel_list.find(_params[1]) != channel_list.end())
			channel_list[_params[1]]->answerMode(client);
		else {
			//NOSUCHCHANNEL 403 <-맞나?
			client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, _params[1]));
			return ;
		}
	}
	std::string	channel_name = _params[0];
	if (channel_list.find(channel_name) == channel_list.end()) {
		client->setMessage(handleResponse(client->getNickname(), ERR_NOSUCHCHANNEL, _params[1]));
		return ;
	}
	std::string opt = _params[1];
	size_t pos = std::min(opt.find('+'), opt.find('-'));//둘중 작은값으로 시작
	if (pos == std::string::npos) {
		// UNKNOWNMODE 472
		client->setMessage(handleResponse(client->getNickname(), ERR_UNKNOWNMODE, opt));
		return ;
	}
	bool sign = opt[pos] == '+' ? true : false;
	std::size_t	order_params = 2;
	for (size_t i = pos; i < opt.size(); ++i) {
		if (!(opt[i] == 'i' || opt[i] == 't' || opt[i] == 'k' 
			|| opt[i] == 'o' || opt[i] == 'l')) {
				client->setMessage(handleResponse(client->getNickname(), ERR_UNKNOWNMODE, std::string(1,opt[i])));
				return ;
			}
		if (sign == true) {
			if (opt[i] == 'i') {
				channel_list[channel_name]->plusOptI(client);
			} else if (opt[i] == 't') {
				channel_list[channel_name]->plusOptT(client);
			} else if (opt[i] == 'k') {
				//KEYSET, NEEDMOREPARAMS
				//여기서 KEYSET을 어떻게 호출?
				if (order_params == _params.size()) {
					client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "MODE"));//여기의 target에 뭐가 들어가야 할지 모르겠음
					continue ;
				}
				channel_list[channel_name]->plusOptK(client, _params[order_params]);
				++order_params;//이게 받은 인자 개수 넘으면?
			} else if (opt[i] == 'o') {
				//NOSUCHNICK, NEEDMOREPARAMS
				if (order_params == _params.size()) {
					client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "MODE"));
					continue ;
				}
				if (!server.findClient(_params[order_params])) {
					//??///
					//
				}
				channel_list[channel_name]->plusOptO(client, server.findClient(_params[order_params]));
				++order_params;
			} else if (opt[i] == 'l') {
				//NEEDMOREPARAMS
				if (order_params == _params.size()) {
					client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "MODE"));
					continue ;
				}
				long nb = std::atoi(_params[order_params].c_str());
				channel_list[channel_name]->plusOptL(client, nb);
				++order_params;
			} else {
				// ERR_UNKNOWNMODE
				client->setMessage(handleResponse(client->getNickname(), ERR_UNKNOWNMODE, std::string(1, opt[i])));
				return ;
			}
		} else { //minus
			if (opt[i] == 'i') {
				channel_list[channel_name]->minusOptI(client);
			} else if (opt[i] == 't') {
				channel_list[channel_name]->minusOptT(client);
			} else if (opt[i] == 'k') {
				channel_list[channel_name]->minusOptK(client);
			} else if (opt[i] == 'o') {
				//NOSUCHNICK, NEEDMOREPARAMS
				if (_params.size() < 3) {
					client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "MODE"));
					return ;
				}
				server.findClient(_params[2]);
				channel_list[channel_name]->minusOptO(client, server.findClient(_params[order_params]));
			} else if (opt[i] == 'l') {
				//NEEDMOREPARAMS
				if (order_params == _params.size()) {
					client->setMessage(handleResponse(client->getNickname(), ERR_NEEDMOREPARAMS, "MODE"));
					continue ;
				}
				else
					channel_list[channel_name]->minusOptL(client);
			} else {
				// ERR_UNKNOWNMODE
				client->setMessage(handleResponse(client->getNickname(), ERR_UNKNOWNMODE, opt));
				return ;
			}
		}
	}
}