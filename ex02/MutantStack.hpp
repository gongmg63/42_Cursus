#ifndef __MUTANTSTACK_HPP__
#define __MUTANTSTACK_HPP__

#include <stack>
#include <string>

template<typename T>
class MutantStack : public std::stack<T>
{
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

	MutantStack();
	MutantStack(const MutantStack& copy);
	MutantStack&	operator=(const MutantStack& copy);
	~MutantStack();

	iterator	begin();
	iterator	end();
	reverse_iterator	rbegin();
	reverse_iterator	rend();
};

#include "MutantStack.tpp"

#endif