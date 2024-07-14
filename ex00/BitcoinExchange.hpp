#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include <exception>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <map>

enum
{
	DATA,
	VALUE
};

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange&	operator=(const BitcoinExchange& copy);
	~BitcoinExchange();

	void calculateExchange(const char* input);
private:
	std::map<std::string, float>	_database;
	
	void	stringTrim(std::string& str);
	void	checkFirstLine(const std::string& first_line, int type);
	bool	checkLeapYear(const long& year);
	float	findExchange(const std::string& date);

	const std::string&	checkDate(const std::string& date);
	float				checkValue(const std::string& value, int type);

	void	parseDatabase();
};

#endif