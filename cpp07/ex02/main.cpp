#include <iostream>
#include "Array.hpp"
#include <vector>

template<typename T>
void printArray(const Array<T>& arr) {
    std::cout << "Array contents: ";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
	std::cout << "Testing default constructor" << std::endl;
	Array<int> defaultArray;
	std::cout << "Default array size: " << defaultArray.size() << std::endl;
	Array<std::string> defaultArray2;
	std::cout << "Default array2 size: " << defaultArray2.size() << std::endl;
	
	std::cout << "\nTesting parameterized constructor with size 5" << std::endl;
	Array<int> paramArray(5);
	printArray(paramArray);
	Array<std::string> paramArray2(5);
	printArray(paramArray2);
	
	std::cout << "\nTesting element access and modification" << std::endl;
	for (std::size_t i = 0; i < paramArray.size(); ++i)
	    paramArray[i] = i * 10;
	printArray(paramArray);
	for (std::size_t i = 0; i < paramArray2.size(); ++i)
	    paramArray2[i] = i + 'a';
	printArray(paramArray2);

	std::cout << "\nTesting copy constructor" << std::endl;
	Array<int> copyArray(paramArray);
	printArray(copyArray);
	for (std::size_t i = 0; i < copyArray.size(); ++i)
		copyArray[i] = i * 20;
	printArray(copyArray);
	printArray(paramArray);
	Array<std::string> copyArray2(paramArray2);
	printArray(copyArray2);
	for (std::size_t i = 0; i < copyArray2.size(); ++i)
		copyArray2[i] = i + 'a' + 1;
	printArray(copyArray2);
	printArray(paramArray2);
	
	std::cout << "\nTesting assignment operator" << std::endl;
	Array<int> assignArray = paramArray;
	printArray(assignArray);
	Array<std::string> assignArray2 = paramArray2;
	printArray(assignArray2);
	std::cout << "size : " << assignArray2.size() << "\n";
	
	std::cout << "\nTesting out of range access" << std::endl;
	try 
	{
	    std::cout << paramArray[10] << std::endl;
	}
	catch (const std::exception& e) 
	{
	    std::cerr << e.what() << std::endl;
	}
	system("leaks ex02");
    return 0;
}