#include "Contact.hpp"

Contact::Contact(void) {}

Contact::Contact(std::string l_name, std::string f_name, std::string nickname, \
			std::string phone_number, std::string darkest_secret)
{
	this->l_name = l_name;
	this->f_name = f_name;
	this->nickname = nickname;
	this->phone_number = phone_number;
	this->darkest_secret = darkest_secret;	
}

void	Contact::print_info(std::string info)
{
	std::string	str;

	for (int i = 0; i < (int)info.size(); ++i)
	{
		if (i == 9 && info.size() > 10)
		{
			str += ".";
			break;
		}
		str += info[i];
	}
	std::cout << str;
}

std::string	Contact::get_l_name(void)
{
	return (this->l_name);
}

std::string	Contact::get_f_name(void)
{
	return (this->f_name);
}

std::string	Contact::get_nickname(void)
{
	return (this->nickname);
}

std::string Contact::get_phone_number(void)
{
	return (this->nickname);
}

std::string	Contact::get_darkest_secret(void)
{
	return (this->darkest_secret);
}

void	Contact::set_l_name(std::string l_name)
{
	this->l_name = l_name;
}

void	Contact::set_f_name(std::string f_name)
{
	this->f_name = f_name;
}

void	Contact::set_nickname(std::string nickname)
{
	this->nickname = nickname;
}

void	Contact::set_phone_number(std::string phone_number)
{
	this->phone_number = phone_number;
}

void	Contact::set_darkest_secret(std::string darkest_secret)
{
	this->darkest_secret = darkest_secret;
}
