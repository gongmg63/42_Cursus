#pragma once

#include <iostream>
#include <cstring>

typedef unsigned long uintptr_t;

struct Data
{
	std::string content;
	int			number;
};


class Serializer
{
public:
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(uintptr_t raw);
private:
	//forbidden constructor, operator
	Serializer ();
	Serializer (const Serializer& copy);
	~Serializer ();
	const Serializer operator=(const Serializer& copy);
};