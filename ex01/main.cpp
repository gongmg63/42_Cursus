#include "Serializer.hpp"

int main()
{
	Data*	test = new Data;
	uintptr_t raw;
	Data*	deserial_test;

	test->content = "hihi";
	test->number = 42;

	std::cout << "before : " << test->content << " / " << test->number << "\n";
	raw = Serializer::serialize(test);
	deserial_test = Serializer::deserialize(raw);
	std::cout << "after : " << deserial_test->content << " / " << deserial_test->number << "\n";

	delete test;
}