#include "easyfind.hpp"
#include <vector>
#include <deque>

int main()
{
	// std::deque<int> vec;
	std::vector<int> vec;
	vec.push_back(1); 
	vec.push_back(2); 
	vec.push_back(3); 
	vec.push_back(4); 
	vec.push_back(5);
	
	try
	{
		int num = easyfind(vec, 3);
		std::cout << "Num : " << num << "\n\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception : " << e.what() << "\n";
	}

	try
	{
		int num = easyfind(vec, 6);
		std::cout << "Num : " << num << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception : " << e.what() << "\n";
	}
}