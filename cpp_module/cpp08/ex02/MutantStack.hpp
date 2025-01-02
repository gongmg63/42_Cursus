#ifndef __MUTANTSTACK_HPP__
#define __MUTANTSTACK_HPP__

#include <stack>
#include <string>

template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
public:
    typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;
	typedef typename Container::reverse_iterator reverse_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;

	MutantStack();
	MutantStack(const MutantStack& copy);
	MutantStack&	operator=(const MutantStack& copy);
	~MutantStack();

	iterator	begin();
	iterator	end();
	reverse_iterator	rbegin();
	reverse_iterator	rend();
	const_iterator	begin() const;
	const_iterator	end() const;
	const_reverse_iterator	rbegin() const;
	const_reverse_iterator	rend() const;
};

#include "MutantStack.tpp"

#endif