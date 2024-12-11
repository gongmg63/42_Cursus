#include "AMateria.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

// void	ck()
// {
// 	system("leaks ex03");
// }

int main()
{
	// atexit(ck);

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");
	
	AMateria* tmp;
	AMateria* tmp_arr[2];
	tmp = src->createMateria("ice");
	tmp_arr[0] = tmp;
	me->equip(tmp);
	tmp = src->createMateria("cure");
	tmp_arr[1] = tmp;
	me->equip(tmp);
	
	ICharacter* bob = new Character("bob");
	
	me->use(0, *bob);
	me->use(1, *bob);

	// me->unequip(0);
	// me->unequip(1);
	// me->use(1, *bob); //Can't use
	// me->unequip(1); //Can't unequip

	// me->equip(tmp);
	// me->equip(tmp);
	// me->equip(tmp);
	// me->equip(tmp);
	// me->equip(tmp); // Can't equip
	// me->unequip(0);
	// me->unequip(1);
	// me->unequip(2);
	// me->unequip(3);

	// delete tmp_arr[0];
	// delete tmp_arr[1];

	// Character* one = new Character("one");
	// tmp = src->createMateria("ice");
	// one->equip(tmp);
	// one->use(0, *bob);

	// Character* two = new Character(*one);
	// tmp->setType("cure");
	// one->use(0, *bob);
	// two->use(0, *bob);

	// delete one;
	// delete two;
	delete bob;
	delete me;
	delete src;
	return 0;
}