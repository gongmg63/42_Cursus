#include "Harl.hpp"

Harl::Harl(void)
{
	this->level_str[0] = "DEBUG";
	this->level_str[1] = "INFO";
	this->level_str[2] = "WARNING";
	this->level_str[3] = "ERROR";
}

void	Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger." <<std::endl;
	std::cout << "I really do!" << std::endl;
	std::cout << std::endl;
}

void	Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
	std::cout << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I’ve been coming for years whereas you started working here since last month." << std::endl;
	std::cout << std::endl;
}

void	Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
	std::cout << std::endl;
}

void	Harl::complain(std::string level)
{
	int	level_idx = -1;

	void (Harl::*harl[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	for (int i = 0; i < 4; ++i)
	{
		if (this->level_str[i] == level)
			level_idx = i;
	}
	switch (level_idx)
	{
	case -1:
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	case 0:
		(this->*harl[0])();
	case 1:
		(this->*harl[1])();
	case 2:
		(this->*harl[2])();
	case 3:
		(this->*harl[3])();
	}
}
