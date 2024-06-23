#include "Serializer.hpp"

uintptr_t	Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serializer::deserialize(unitptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}