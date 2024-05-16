#include "AMateria.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

void	ck()
{
	system("leaks ex03");
}

int main()
{
	atexit(ck);
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	AMateria* tmp_ad[2];
	tmp = src->createMateria("ice");
	tmp_ad[0] = tmp;
	me->equip(tmp);
	tmp = src->createMateria("cure");
	tmp_ad[1] = tmp;
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	me->unequip(1);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;
	delete tmp_ad[0];
	delete tmp_ad[1];
	return 0;
}