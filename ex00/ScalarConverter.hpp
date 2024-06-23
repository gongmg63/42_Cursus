#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cerrno>

enum Type
{
	CHAR, 
	INT,
	FLOAT,
	DOUBLE,
	NONE
};

struct	Checker
{
	Type type;
	std::string	input;	
	int			precision;
	bool		overflow;
	char *		end;
};

class ScalarConverter
{
public:
	~ScalarConverter ();

	static void convert(const std::string& str);
private:

	//forbidden constructor, operator
	ScalarConverter	();
	ScalarConverter	(const ScalarConverter& copy);
	const ScalarConverter&	operator=(const ScalarConverter& copy);
};

const Checker checkInput(const std::string& str);
void	charPrint(Checker check);
void	intPrint(Checker check);
void	floatPrint(Checker check);
void	doublePrint(Checker check);
void	nonePrint(Checker check);