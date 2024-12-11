#include "Phonebook.hpp"

Phonebook::Phonebook(void)
{
	this->pb_size = 0;
}

Phonebook::Phonebook(Contact *contact, int size)
{
	if (size > 8)
		size = 8;
	for (int i = 0; i < size; ++i)
		this->contacts[i] = contact[i];
	this->pb_size = size;
}

void	Phonebook::eof_clear(void)
{
	std::cout << "Can't enter the EOF.." << std::endl;
	clearerr(stdin);
	std::cin.clear();
}

void	Phonebook::add_contact(void)
{
	Contact new_contact;
	std::string	l_name;
	std::string	f_name;
	std::string	nickname;
	std::string	phone_number;
	std::string	darkest_secret;

	std::cout << "Enter your last name : ";
	std::getline(std::cin, l_name);
	if (std::cin.eof())
		return (eof_clear());
	std::cout << "Enter your first name : ";
	std::getline(std::cin, f_name);
	if (std::cin.eof())
		return (eof_clear());
	std::cout << "Enter your nickname : ";
	std::getline(std::cin, nickname);
	if (std::cin.eof())
		return (eof_clear());
	std::cout << "Enter your phone number : ";
	std::getline(std::cin, phone_number);
	if (std::cin.eof())
		return (eof_clear());
	std::cout << "Enter your darkest  secret : ";
	std::getline(std::cin, darkest_secret);
	if (std::cin.eof())
		return (eof_clear());
	new_contact.set_l_name(l_name);
	new_contact.set_f_name(f_name);
	new_contact.set_nickname(nickname);
	new_contact.set_phone_number(phone_number);
	new_contact.set_darkest_secret(darkest_secret);
	for (int i = 7; i > 0; --i)
		this->contacts[i] = this->contacts[i - 1];
	if (this->pb_size < 8)
		this->pb_size++;
	this->contacts[0] = new_contact;
}

void	Phonebook::search_contact(void)
{
	std::string	idx;

	if (this->pb_size == 0)
	{
		std::cout << "There is no contact.." << std::endl;
		return ;
	}
	this->display_contact();
	std::cout << "Enter the index : ";
	std::getline(std::cin, idx);
	while (!std::cin.good() || idx.size() > 1 || idx[0] - '0' > this->pb_size - 1 || idx[0] - '0' < 0)
	{
		if (std::cin.eof())
			return (eof_clear());
		std::cout << "Please enter the valid index : ";
		std::getline(std::cin, idx);
	}
	this->display_contact(idx[0] - '0');
}

void	Phonebook::display_contact(void)
{
	for (int i = 0; i < this->pb_size; ++i)
	{
		std::cout << std::setfill(' ') << std::setw(10);
		std::cout << i;
		std::cout << "|";
		std::cout << std::setfill(' ') << std::setw(10);
		this->contacts[i].print_info(this->contacts[i].get_l_name());
		std::cout << "|";
		std::cout << std::setfill(' ') << std::setw(10);
		this->contacts[i].print_info(this->contacts[i].get_f_name());
		std::cout << "|";
		std::cout << std::setfill(' ') << std::setw(10);
		this->contacts[i].print_info(this->contacts[i].get_nickname());
		std::cout << "|" << std::endl;
	}
}

void	Phonebook::display_contact(int idx)
{
	std::cout << std::setfill(' ') << std::setw(10);
	std::cout << idx;
	std::cout << "|";
	std::cout << std::setfill(' ') << std::setw(10);
	this->contacts[idx].print_info(this->contacts[idx].get_l_name());
	std::cout << "|";
	std::cout << std::setfill(' ') << std::setw(10);
	this->contacts[idx].print_info(this->contacts[idx].get_f_name());
	std::cout << "|";
	std::cout << std::setfill(' ') << std::setw(10);
	this->contacts[idx].print_info(this->contacts[idx].get_nickname());
	std::cout << std::endl;
}
