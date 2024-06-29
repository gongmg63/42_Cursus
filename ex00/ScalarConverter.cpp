#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& copy) 
{
	(void)copy;
}

const ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& copy)
{
	(void)copy;
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

void	ScalarConverter::convert(const std::string& str)
{
	Checker check = checkInput(str);
	switch (check.type)
	{
	case CHAR:
		charPrint(check);
		break;
	case INT:
		intPrint(check);
		break;
	case FLOAT:
		floatPrint(check);
		break;
	case DOUBLE:
		doublePrint(check);
		break;
	case NONE:
		nonePrint();
		break;
	}
}

void	charPrint(Checker check)
{
	char c = check.input[0];

	if (!std::isprint(c))
		std::cout << "char : Non displayable\n";
	else
		std::cout << "char : '" << c << "'\n";
	std::cout << "int : " << static_cast<int>(c) << "\n";
	std::cout << "float : " << static_cast<float>(c) << ".0f\n";
	std::cout << "double : " << static_cast<double>(c) << ".0\n";
}

void	intPrint(Checker check)
{
	int		i = static_cast<int>(std::strtol(check.input.c_str(), &check.end, 10));
	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);

	if (static_cast<int>(c) != i)
		std::cout << "char : impossible\n";
	else if (!std::isprint(c))
		std::cout << "char : Non displayable\n";
	else
		std::cout << "char : '" << c << "'\n";
	if (check.overflow)
		std::cout << "int : impossible\n";
	else
		std::cout << "int : " << i << "\n";
	if (static_cast<int>(f) != i)
		std::cout << "float : impossible\n";
	else
		std::cout << "float : " << f << ".0f\n";
	if (static_cast<int>(d) != i)
		std::cout << "double : impossible\n";
	else
		std::cout << "double : " << d << ".0\n";
}

void	floatPrint(Checker check)
{
	float	f = std::strtof(check.input.c_str(), &check.end);
	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);

	if (check.input == "nan" || check.input.find("inf") != std::string::npos)
	{
		std::cout << "char : impossible\n";
		std::cout << "int : impossible\n";
	}
	else
	{
		if (static_cast<float>(c) != f)
			std::cout << "char : impossible\n";
		else if (!std::isprint(c))
			std::cout << "char : Non displayable\n";
		else
			std::cout << "char : '" << c << "'\n";
		if (static_cast<float>(i) != f)
			std::cout << "int : impossible\n";
		else
			std::cout << "int : " << i << "\n";
	}
	if (check.overflow)
	{
		std::cout << "float : impossible\n";
		std::cout << "hihi\n";
	}
	else
		std::cout << "float : " << std::fixed << std::setprecision(check.precision) << f << "f\n";
	std::cout << std::fixed << std::setprecision(check.precision) << "double : " << d << "\n";
}

void	doublePrint(Checker check)
{
	double	d = std::strtod(check.input.c_str(), &check.end);
	float	f = static_cast<float>(d);
	int		i = static_cast<int>(d);
	char	c = static_cast<char>(d);

	if (check.input == "nan" || check.input.find("inf") != std::string::npos)
	{
		std::cout << "char : impossible\n";
		std::cout << "int : impossible\n";
	}
	else
	{
		if (static_cast<double>(c) != d)
			std::cout << "char : impossible\n";
		else if (!std::isprint(c))
			std::cout << "char : Non displayable\n";
		else
			std::cout << "char : '" << c << "'\n";
		if (static_cast<double>(i) != d)
			std::cout << "int : impossible\n";
		else
			std::cout << "int : " << i << "\n";	
	}
	if (check.overflow)
	{
		std::cout << "float : impossible\n";
		std::cout << "double : impossible\n";
	}
	else
	{
		std::cout << "float : " << std::fixed << std::setprecision(check.precision) << f << "f\n";
		std::cout << "double : " << std::fixed << std::setprecision(check.precision) << d << "\n";
	}
}

void	nonePrint()
{
	std::cout << "char : I don't know..\n";
	std::cout << "int : I don't know..\n";
	std::cout << "float : I don't know..\n";
	std::cout << "double : I don't know..\n";
}

const Checker checkInput(const std::string& str)
{
	Checker checker;

	checker.input = str;
	checker.overflow = false;
	if (str.length() == 1 && !std::isdigit(str[0]))
	{
		checker.type = CHAR;
		return (checker);
	}
	if (str[0] == '.')
	{
		checker.type = NONE;
		return (checker);
	}
	if (str[str.length() - 1] == '.' || (str[str.length() - 1] == 'f' && str[str.length() - 2] == '.'))
	{
		checker.type = NONE;
		return (checker);
	}
	std::strtol(str.c_str(), &checker.end, 10);
	if (*checker.end == 0)
	{
		checker.type = INT;
		if (std::atoi(str.c_str()) != std::strtol(str.c_str(), &checker.end, 10))
			checker.overflow = true;
		return (checker);
	}
	errno = 0;
	if (str[str.size() - 1] == 'f')
	{
		std::string tmp = str.substr(0, str.length() - 1);

		checker.precision = (tmp.find('.') != std::string::npos) ? tmp.length() - tmp.find('.') - 1 : 1;
		std::strtof(tmp.c_str(), &checker.end);
		if (*checker.end == 0)
		{
			checker.type = FLOAT;
			if (errno == ERANGE)
				checker.overflow = true;
			checker.input = tmp;
			return (checker);
		}
	}
	errno = 0;
	std::strtod(str.c_str(), &checker.end);
	if (*checker.end == 0)
	{
		checker.type = DOUBLE;
		checker.precision = (str.find('.') != std::string::npos) ? str.length() - str.find('.') - 1 : 1;
		if (errno == ERANGE)
			checker.overflow = true;
		return (checker);
	}
	checker.type = NONE;
	return (checker);
}