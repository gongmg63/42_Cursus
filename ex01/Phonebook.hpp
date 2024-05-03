#ifndef __Phonebook_HPP__
#define __Phonebook_HPP__
#include "Contact.hpp"
#include "Phone.hpp"

class Phonebook
{
private:
	Contact contacts[8];
	int		pb_size;
public:
	Phonebook(void);
	Phonebook(Contact *contact, int size);
	void	eof_clear(void);
	void	add_contact(void);
	void	search_contact(void);
	void	display_contact(void);
	void	display_contact(int idx);
};

#endif