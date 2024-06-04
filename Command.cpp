
#include "Command.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include <sstream>

Command::Command() {
	_cmdlist.push_back("/join");
	_cmdlist.push_back("/pass");
	_cmdlist.push_back("/user");
	_cmdlist.push_back("/nick");
	_cmdlist.push_back("/quit");//서버 나가면서 메세지 뱉기 
	_cmdlist.push_back("/part");//leave channel
//==============CHANNEL===========
	_cmdlist.push_back("/topic");
	_cmdlist.push_back("/invite");
	_cmdlist.push_back("/kick");
	_cmdlist.push_back("/mode");
	_cmdlist.push_back("/dcc");//파일전송
//===============SERVER===========
	_cmdlist.push_back("/list");
	_cmdlist.push_back("/names");
	_cmdlist.push_back("/privmsg");
	_cmdlist.push_back("/notice");
}

void Command::handleCmd(Client* client, const std::string& msg) {
//msg  512자 넘으면 거절
//이 함수를 통해서 command 호출
	if (parseCmd(msg) == false)
		return ;
	if (_cmd == "/user")
		user(client);
	//work
}
void Command::handleCmd(Client* client, Channel* channel, const std::string& msg) {
//msg  512자 넘으면 거절
//이 함수를 통해서 command 호출
	if (parseCmd(msg) == false)
		return ;
	//work
}

void Command::handleCmd(Server& server, Client* client, const std::string& msg) {
//이 함수를 통해서 command 호출
	if (parseCmd(msg) == false)
		return ;
	if (_cmd == "/pass")
		pass(server, client);
	else if (_cmd == "/join")
		join(server, client);
	else if (_cmd == "/invite")
		invite(server, client);
	else if (_cmd == "/nick")
		nick(server, client);
	//work
}

bool Command::parseCmd(const std::string& msg) {
	_params.clear();
	std::istringstream ss(msg);
	std::string buf;
	std::getline(ss, _cmd, ' ');//command
	if (std::find(_cmdlist.begin(), _cmdlist.end(), _cmd) == _cmdlist.end()){
		std::cerr << "wrong cmd\n";
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
		std::cerr << "pass : empty params\n";
		return ;
	}
	if (_params[0] == server.getPassword())
		client->setPass(true);
}

void Command::nick(Server& server, Client* client) {
	//NICK <nickname>
	//want 코크풍선..
	//nick 변경가능 

	if (_params.empty()) {
		std::cerr << "nick : empty params\n";
		return ;
	}
	std::string nickname = _params[0];

	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#' || nickname[0] == '&') {
		std::cerr << "nick wrong start nickname\n";
		return ;
	}
	for (size_t i = 0; nickname.size(); ++i) {
		if (nickname[i] == ' ' || nickname[i] == ',' || nickname[i] == '.' || nickname[i] == '*' ||
			nickname[i] == '?' || nickname[i] == '!' || nickname[i] == '@') {
			std::cerr << "nick wrong nickname\n";
			return ;
		}
	}
	//중복 닉네임 고려 어떻게?
	if (nickname.length() > 9)
		return ;
	if (server.findClient(nickname)) {
		std::cerr << "nick : nickname already taken\n";
	}
	client->setNickname(nickname);
}

void Command::user(Client* client) {
	if (_params.size() < 4) { //<= 4 ?
		std::cerr << " user : invilid numbers of params\n";
		return ;
	}
	client->setUsername(_params[0]);
	client->setHostname(_params[1]);
	client->setServername(_params[2]);
	client->setRealname(_params[3]);
	//USER <username> <hostname> <servername> :<realname>
}

void Command::join(Server& server, Client* client) {
	//JOIN <channel>{,<channel>} [<key>{,<key>}]
	//JOIN c1,c2,c3,c4 k1,k2 c4 = "hello,hi"
	//채널이름에 ',' , 7번, 공백 사용금지
	if (_params.empty()) {
		std::cerr << "join : empty params\n";
		return ;
	}
	std::map<std::string, std::string> key_map;
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	std::istringstream channel_ss(_params[0]);//channel 이름 만들때 확인필수
	// std::istringstream key_ss(_params[1]);//있을수도 있고 없을수도있음
	std::istringstream key_ss(_params.size() > 1 ? _params[1] : "");
	std::string buf1;
	std::string buf2;

	while (std::getline(channel_ss, buf1, ',')) {
		if (buf1[0] != '#'){
			std::cerr << "Wrong channel name\n";
			std::getline(key_ss, buf2, ',');
			continue ;
		}
		if (!std::getline(key_ss, buf2, ','))
			buf2 = "";
		else
			key_map[buf1] = buf2;
	}

	std::map<std::string, std::string>::iterator it = key_map.begin();
	for (; it != key_map.end(); ++it){
		std::string channel_name = it->first;
		std::string channel_key = it->second;
		if (channel_list.find(channel_name) != channel_list.end())
			channel_list[channel_name]->join(client, channel_key);
		else{
			server.createChannel(client, channel_name);//못찾으면 채널생성,
			channel_list[channel_name]->join(client, channel_key);//join
		}
	}
}

void	Command::invite(Server& server, Client* client){
	///invite <nickname> <channel>
	if (_params.size() < 2) {
        std::cerr << "invite : invaild number of params\n";
        return;
    }
	std::map<std::string, Channel *> channel_list = server.getChannelList();
	//client_list를 std::string, Client *로 갖고있어야함

	if (client_list.find(_params[0]) == client_list.end()){
		std::cerr << "can't found client\n";
		return ;
	}
	if (channel_list.find(_params[1]) == channel_list.end()){
		std::cerr << "can't found channel\n";
		return ;
	}
	channel_list[_params[1]]->invite(client, client_list[_params[0]]);
}

void	Command::kick(Server& server, Client* client){
	// KICK <channel> <user> [<comment>]
	std::map<std::string, Channel *> channel_list = server.getChannelList();

	if (_params.size() < 2) {
		std::cerr << "kick : invaild number of params\n";
		return ;
	}
	std::string channel_name = _params[0];
	std::string target_name = _params[1];
	if (_params.size() >= 3) {
		std::string command = _params[2];
		channel_list[channel_name]->kick(client, server.findClient(target_name), command);
	} else {
		channel_list[channel_name]->kick(client, server.findClient(target_name), "");
	}
}

void	Command::topic(Server& server, Client* client) {
	//TOPIC <channel> [<topic>]
	//<topic>이 주어지지 않으면 topic 반환
	std::map<std::string, Channel *> channel_list = server.getChannelList();

	if (_params.size() < 1) {
		std::cerr << "topic : invaild number of params\n";
		return ;
	}
	std::string channel_name = _params[0];
	if (_params.size() >= 2) {
		std::string topic = _params[1];
		if (topic == "") {
			std::cerr << "topic : empty string can't be set as a topic\n";
			return ;
		}
		channel_list[channel_name]->topic(client, topic);
	} else {
		channel_list[channel_name]->topic(client, "");
	}
}

void	Command::part(Server& server, Client* client) {
	//PART <channel>{,<channel>}
	std::map<std::string, Channel *> channel_list = server.getChannelList();

	if (_params.empty()) {
		std::cerr << "part : invaild number of params\n";
		return ;
	}
	std::istringstream	ss(_params[0]);
	std::string			channel_name;
	while (std::getline(ss, channel_name, ',')) {
		if (channel_list.find(channel_name) == channel_list.end()) {
			std::cerr << "part : can't find channel\n";
			continue ;
		}
		channel_list[channel_name]->part(client);
	}
}