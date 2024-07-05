#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	parseDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
	: _database(copy._database) {}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& copy)
{
	_database = copy._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::stringTrim(std::string& str)
{
	while (str[0] == ' ')
		str.erase(0, 1);
	while (str[str.size() - 1] == ' ')
		str.erase(str.size() - 1);
}

void	BitcoinExchange::checkFirstLine(const std::string& first_line, int type)
{
	std::istringstream	istrs(first_line);
	std::string 	tmp;
	bool	check_data = false;
	bool	check_value = false;
	int	count = 0;

	if (type == DATA)
	{
		while (std::getline(istrs, tmp, ',') && count < 3)
		{
			if (tmp == "date")
				check_data = true;
			else if (tmp == "exchange_rate")
				check_value = true;
			++count;
		}
	}
	else
	{
		while (std::getline(istrs, tmp, '|') && count < 3)
		{
			stringTrim(tmp);
			if (tmp == "date")
				check_data = true;
			else if (tmp == "value")
				check_value = true;
			++count;
		}
	}
	if (count != 2 || !check_data || !check_value)
		throw std::runtime_error("Error: invalid file value");
}

bool	BitcoinExchange::checkLeapYear(const long& year)
{
	if (!(year % 4))
	{
		if (!(year % 100))
		{
			if (year % 400 == 0)
				return true;
		}
		else
			return true;
	}
	return false;
}

float	BitcoinExchange::findExchange(const std::string& date)
{
	if (_database.find(date) != _database.end())
		return _database[date];
	std::map<std::string, float>::reverse_iterator it;
	for (it = _database.rbegin(); it != _database.rend(); ++it)
	{
		if (it->first < date)
			return it->second;
	}
	throw std::runtime_error("Error: couldn't find previous exchange rate ");
}

const std::string&	BitcoinExchange::checkDate(const std::string& date)
{
	std::istringstream	istrs(date);
	std::string	tmp;
	long	tmp_num;
	long	year;
	long	month;
	char*	end;
	int	count = 0;
	int	month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	while (std::getline(istrs, tmp, '-') && count < 4)
	{
		tmp_num = std::strtol(tmp.c_str(), &end, 10);
		if (*end)
			throw std::runtime_error("Error: bad input => " + date);
		if (count == 0)
		{
			if (tmp_num < 0 || tmp_num > 2024)
				throw std::runtime_error("Error: bad input => " + date);
			year = tmp_num;
		}
		else if (count == 1)
		{
			if (tmp_num < 1 || tmp_num > 12)
				throw std::runtime_error("Error: bad input => " + date);
			month = tmp_num;
		}
		else if (count == 2)
		{
			if (checkLeapYear(year))
				month_day[1] += 1;
			if (tmp_num < 1 || tmp_num > month_day[month - 1])
				throw std::runtime_error("Error: bad input => " + date);
		}
		count++;
	}
	if (count != 3)
		throw std::runtime_error("Error: bad input => " + date);
	return date;
}

float	BitcoinExchange::checkValue(const std::string& value, int type)
{
	char*	end;
	float	value_f = std::strtof(value.c_str(), &end);

	errno = 0;
	if (*end || errno == EOVERFLOW)
		throw std::runtime_error("Error: bad input => " + value);
	if (value_f < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (type == VALUE)
	{
		if (value_f > 1000)
			throw std::runtime_error("Error: too large a number.");
	}
	return value_f;
}

void	BitcoinExchange::parseDatabase()
{
	std::fstream	fs("data.csv");

	if (!fs.is_open())
		throw std::runtime_error("Error: could not open data file");
	std::string tmp_line;
	std::getline(fs, tmp_line);
	checkFirstLine(tmp_line, DATA);
	while (std::getline(fs, tmp_line))
	{
		std::istringstream	istrs(tmp_line);
		std::string tmp_data;
		std::string	date;
		float	value;
		int	flag = 0;
		try
		{
			while (std::getline(istrs, tmp_data, ',') && flag < 3)
			{
				if (flag % 2 == 0)
					date = checkDate(tmp_data);
				else
					value = checkValue(tmp_data, DATA);
				++flag;
			}
			if (flag != 2)
				throw std::runtime_error("Error: bad input => " + tmp_line);
			_database[date] = value;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

void	BitcoinExchange::calculateExchange(const char* input)
{
	std::fstream	fs(input);

	if (!fs.is_open())
		throw std::runtime_error("Error: could not open input file");
	std::string tmp_line;
	std::getline(fs, tmp_line);
	checkFirstLine(tmp_line, VALUE);
	while (std::getline(fs, tmp_line))
	{
		std::istringstream istrs(tmp_line);
		std::string tmp_data;
		std::string date;
		float	value;
		int	flag = 0;
		try
		{
			while (std::getline(istrs, tmp_data, '|') && flag < 3)
			{
				stringTrim(tmp_data);
				if (flag % 2 == 0)
					date = checkDate(tmp_data);
				else
					value = checkValue(tmp_data, VALUE);
				++flag;
			}
			if (flag != 2 || tmp_data.size() == 0)
				throw std::runtime_error("Error: bad input => " + tmp_line);
			value *= findExchange(date);
			std::cout << date << " => " << value << " = " << value << "\n";
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
}