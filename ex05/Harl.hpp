#ifndef __HARL_HPP__
#define __HARL_HPP__
#include <iostream>
#include <string>
#include <map>

class Harl
{
private:
	std::map<std::string, int> level_map;
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
public:
	Harl	(void);
	void	complain(std::string level);
};

#endif