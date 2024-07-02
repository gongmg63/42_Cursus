#include "Span.hpp"

int main()
{
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	Span sp2(10000);
	for (int i = 0; i < 10000; ++i)
		sp2.addNumber(i);
	std::cout << sp2.shortestSpan() << std::endl;
	std::cout << sp2.longestSpan() << std::endl;

	std::vector<int> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(i);
	Span sp3(10);
	sp3.addNumbers(vec.begin(), vec.end());
	std::cout << sp3.shortestSpan() << std::endl;
	std::cout << sp3.longestSpan() << std::endl;
	std::cout << sp3.size() << std::endl;
	try
	{
		sp3.addNumber(3);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	Span sp4(1);
	sp4.addNumber(1);
	try
	{
		sp4.shortestSpan();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		sp4.longestSpan();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return 0;
}