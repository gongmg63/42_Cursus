#include "Phone.hpp"
#include "Phonebook.hpp"
#include "Contact.hpp"

int	main()
{
	std::string	cmd;
	Phonebook	pb;
	// Contact		contacts[8];
	// Contact		contact("a", "a", "a", "a", "a");
	// Contact		contact1("bb", "bb", "bb", "bb", "bb");
	// Contact		contact2("ccc", "ccc", "ccc", "ccc", "ccc");
	// Contact		contact3("dddd", "dddd", "dddd", "dddd", "dddd");
	// Contact		contact4("eeeee", "eeeee", "eeeee", "eeeee", "eeeee");
	// Contact		contact5("fffffffff", "fffffffff", "fffffffff", "fffffffff", "fffffffff");
	// Contact		contact6("gggggggggg", "gggggggggg", "gggggggggg", "gggggggggg", "gggggggggg");
	// Contact		contact7("hhhhhhhhhhh", "hhhhhhhhhhh", "hhhhhhhhhhh", "hhhhhhhhhhh", "hhhhhhhhhhh");

	// contacts[0] = contact;
	// contacts[1] = contact1;
	// contacts[2] = contact2;
	// contacts[3] = contact3;
	// contacts[4] = contact4;
	// contacts[5] = contact5;
	// contacts[6] = contact6;
	// contacts[7] = contact7;
	// Phonebook	sample(contacts, 8);
	while(1)
	{
		std::cout << "Enter the command : ";
		std::getline(std::cin, cmd);
		if (std::cin.eof())
		{
			pb.eof_clear();
			continue;
		}
		if (cmd == "ADD")
			pb.add_contact();
		else if (cmd == "SEARCH")
			pb.search_contact();
		else if (cmd == "EXIT")
			return (0);
		else
			std::cout << "Please enter the valid command." << std::endl;
	}
}