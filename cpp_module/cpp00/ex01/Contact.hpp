#ifndef __CONTACT_HPP__
#define __CONTACT_HPP__
#include "Phone.hpp"

class Contact
{
private:
	std::string	l_name;
	std::string	f_name;
	std::string	nickname;
	std::string	phone_number;
	std::string	darkest_secret;
public:
	Contact(void);
	Contact(std::string l_name, std::string f_name, std::string nickname, \
			std::string phone_number, std::string darkest_secret);
	std::string	get_l_name(void);
	std::string	get_f_name(void);
	std::string	get_nickname(void);
	std::string	get_darkest_secret(void);
	std::string get_phone_number(void);
	void		set_l_name(std::string l_name);
	void		set_f_name(std::string f_name);
	void		set_nickname(std::string nickname);
	void		set_phone_number(std::string phone_number);
	void		set_darkest_secret(std::string darkest_secret);
	void		print_info(std::string info);
};

#endif