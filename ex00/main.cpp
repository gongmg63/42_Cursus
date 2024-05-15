#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "WrongDog.hpp"

// void	ck()
// {
// 	system("leaks ex00");
// }

int main()
{
	// atexit(ck);
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	// Animal* copy = new Animal();
	// *copy = *j;
	// // *j = *copy;
	// copy->makeSound();
	// std::cout << copy->getType() << std::endl;
	// *copy = *i;
	// copy->makeSound();
	// std::cout << copy->getType() << std::endl;
	// std::cout << j->getType() << std::endl;

	// Animal* copy2 = new Animal(*j);
	// copy2->makeSound();
	// *copy2 = *i;
	// copy2->makeSound();
	// std::cout << copy->getType() << std::endl;
	// std::cout << j->getType() << std::endl;
	
	// const WrongAnimal	*wa = new WrongAnimal();
	// const WrongAnimal	*wc = new WrongCat();
	// const WrongCat		*wc2 = new WrongCat();
	// const WrongAnimal	*wd = new WrongDog();
	// const WrongDog		*wd2 = new WrongDog();

	// std::cout << wc->getType() << " " << std::endl;
	// std::cout << wc2->getType() << " " << std::endl;
	// std::cout << wd->getType() << " " << std::endl;
	// std::cout << wd2->getType() << " " << std::endl;
	// wa->makeSound();
	// wc->makeSound();
	// wc2->makeSound();
	// wd->makeSound();
	// wd2->makeSound();
	// delete wa;
	// delete wc;
	// delete wc2;
	// delete wd;
	// delete wd2;
	// delete copy;
	// delete copy2;
	delete meta;
	delete j;
	delete i;
	return 0;
}