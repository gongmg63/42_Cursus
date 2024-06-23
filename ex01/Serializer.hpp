#pragma once

#include <iostream>
#include <cstring>

typedef unsigned long unitptr_t;

struct Data
{
	std::string content;
	int			number;
};


class Serializer
{
public:
	~Serializer ();
	
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(unitptr_t raw);
private:

	//forbidden constructor, operator
	Serializer ();
	Serializer (const Serializer& copy);
	const Serializer operator=(const Serializer& copy);
};