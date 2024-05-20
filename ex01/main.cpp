#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

// void	ck()
// {
// 	system("leaks ex01");
// }

int main()
{
	// atexit(ck);
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;//should not create a leak
	delete i;

	// Dog* dog = new Dog();
	// Dog* dog_copy = new Dog(*dog);
	// Cat* cat = new Cat();
	// Cat* cat_copy = new Cat(*cat);

	// std::cout << "Dog copy : " << dog->getDogIdea() << " " << dog_copy->getDogIdea() << std::endl;
	// std::cout << "Cat copy : " << cat->getCatIdea() << " " << cat_copy->getCatIdea() << std::endl;
	// dog->setDogIdea("Wolf");
	// cat->setCatIdea("Tiger");
	// std::cout << "Set Dog : " << dog->getDogIdea() << " " << dog_copy->getDogIdea() << std::endl;
	// std::cout << "Set Cat : " << cat->getCatIdea() << " " << cat_copy->getCatIdea() << std::endl;
	// delete dog;
	// delete cat;
	// delete dog_copy;
	// delete cat_copy;

	// Animal*	animals[4];
	// for (int k = 0; k < 4; ++k)
	// {
	// 	if (k % 2 == 0)
	// 		animals[k] = new Dog();
	// 	else
	// 		animals[k] = new Cat();
	// }
	// for (int i = 0; i < 4; ++i)
	// 	delete animals[i];

	return 0;
}