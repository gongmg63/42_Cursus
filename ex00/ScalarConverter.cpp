#include "ScalarConverter.hpp"

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
		nonePrint(check);
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
	int	i = static_cast<int>(std::strtol(check.input.c_str(), &check.end, 10));
	if (!std::isprint(i))
		std::cout << "char : Non displayable\n";
	else
		std::cout << "char : '" << static_cast<char>(i) << "'\n";
	if (check.overflow)
		std::cout << "int : overflow\n";
	else
		std::cout << "int : " << i << "\n";
	std::cout << "float : " << static_cast<float>(i) << ".0f\n";
	std::cout << "double : " << static_cast<double>(i) << ".0\n";
}

void	floatPrint(Checker check)
{
	float f = static_cast<float>(std::strtod(check.input.c_str(), &check.end));
	
	if (check.input == "nan" || check.input.find("inf") != std::string::npos)
	{
		std::cout << "char : impossible\n";
		std::cout << "int : impossible\n";
	}
	else
	{
		if (!std::isprint(f))
			std::cout << "char : Non displayable\n";
		else
			std::cout << "char : '" << static_cast<char>(f) << "'\n";
		std::cout << "int : " << static_cast<int>(f) << "\n";
	}
	if (check.overflow)
		std::cout << "float : overflow\n";
	else
		std::cout << "float : " << std::fixed << std::setprecision(check.precision) << f << "f\n";
	std::cout << "double : " << static_cast<double>(f) << "\n";
}

void	doublePrint(Checker check)
{
	double d = std::strtod(check.input.c_str(), &check.end);

	if (check.input == "nan" || check.input.find("inf") == std::string::npos)
	{
		std::cout << "char : impossible\n";
		std::cout << "int : impossible\n";
	}
	else
	{
		if (!std::isprint(d))
			std::cout << "char : Non displayable\n";
		else
			std::cout << "char : '" << static_cast<char>(d) << "'\n";
		std::cout << "int : " << static_cast<int>(d) << "\n";	
	}
	std::cout << "float : " << std::fixed << std::setprecision(check.precision) << static_cast<float>(d) << "f\n";
	if (check.overflow)
		std::cout << "double : overflow\n";
	else
		std::cout << "double : " << d << "\n";
}

void	nonePrint(Checker check)
{
	(void)check;
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
	if (str[str.length() - 1] == '.' || (str[str.length() - 1] == 'f' && str[str.length() - 2] == '.'))
	{
		checker.type = NONE;
		return (checker);
	}
	errno = 0;
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
		std::strtod(tmp.c_str(), &checker.end);
		if (*checker.end == 0)
		{
			checker.type = FLOAT;
			if (errno == ERANGE)
				checker.overflow = true;
			checker.input = tmp;
			return (checker);
		}
	}
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