#pragma once

#include "vector.hpp"

namespace ft
{

    template<class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef Container	container_type;
            typedef typename Container::value_type	value_type;
            typedef typename Container::size_type	size_type;
            typedef typename Container::reference	reference;
            typedef typename Container::const_reference	const_reference;
        
        private:
            Container	c;

		public:
			explicit stack(const Container& cont = Container()) : c(cont) {}
			stack(const stack& other) : c(other.cont) {}
			~stack() {};

			stack& operator=( const stack& other )
			{
				c = other.c;
				return *this;
			}

			reference top() { return c.back(); }
			const_reference top() const { return c.back(); }
			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			void push( const value_type& value ) { c.push_back(value); }
			void pop() { c.pop_back(); }

			template <class Tx, class Cx>
			friend bool operator==(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);

    		template <class Tx, class Cx>
    		friend bool operator!=(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);

    		template <class Tx, class Cx>
    		friend bool operator<(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);
    
			template <class Tx, class Cx>
    		friend bool operator>(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);

    		template <class Tx, class Cx>
    		friend bool operator<=(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);

			template <class Tx, class Cx>
    		friend bool operator>=(const ft::stack<Tx,Cx>& lhs, const ft::stack<Tx,Cx>& rhs);
    };

	template <class T, class Container>
    bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.c == rhs.c; }

    template <class T, class Container>
    bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.c != rhs.c; }

    template <class T, class Container>
    bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.c < rhs.c; }
    
    template <class T, class Container>
    bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return  lhs.c > rhs.c; }

    template <class T, class Container>
    bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.c <= rhs.c; }

    template <class T, class Container>
    bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.c >= rhs.c; }


};