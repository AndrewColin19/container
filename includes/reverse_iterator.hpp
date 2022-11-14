#pragma once

#include "iterator_traits.hpp"

namespace ft
{
    template <class Iter>
    class reverse_iterator
    {
        public:
            typedef Iter     iterator_type;
            typedef typename iterator_traits<Iter>::value_type         value_type;
            typedef typename iterator_traits<Iter>::difference_type  difference_type;
            typedef typename iterator_traits<Iter>::pointer   pointer;
            typedef typename iterator_traits<Iter>::reference reference;
            typedef typename iterator_traits<Iter>::iterator_category  iterator_category;
        private:
            iterator_type current;
        public:
            reverse_iterator() {}
            explicit reverse_iterator( iterator_type x ) : current(x) {}

            template< class U >
            reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}

            template< class U >
            reverse_iterator& operator=( const reverse_iterator<U>& other )
            {
                current = other.base();
                return *this;
            }

            iterator_type base() const { return current; }

            reverse_iterator& operator++()
            { 
                current--; 
                return *this; 
            }

            reverse_iterator operator++(int) 
            { 
                reverse_iterator tmp(*this); 
                current--; 
                return tmp; 
            }

            reverse_iterator& operator--() 
            { 
                current++; 
                return *this; 
            }

            reverse_iterator operator--(int) 
            { 
                reverse_iterator tmp(*this); 
                current++; 
                return tmp;
            }

            reverse_iterator operator+( difference_type n ) const { return reverse_iterator(current - n); }
            reverse_iterator operator-( difference_type n ) const { return reverse_iterator(current + n); }
            difference_type operator-(reverse_iterator x) { return x.base() - base(); }

            reverse_iterator& operator+=( difference_type n )
            {
                current -= n;
                return *this;
            }

            reverse_iterator& operator-=( difference_type n ) 
            {
                current += n;
                return *this;
            }
            
            reference operator*() const
            {
                Iter tmp = current;
                return *--tmp;
            }
        
            pointer operator->() const
            {
                Iter tmp = current;
                return (--tmp).base();
            }

            reference operator[]( difference_type n ) const 
            { 
                iterator_type val = current - n - 1;
                return *(val); 
            }
    };

    template< class Iter >
    reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
    {
        return it + n;
    }

    template< class Iterator >
    typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
    { 
        return rhs.base() - lhs.base();
    }

    template<class T, class T2>
    bool operator==(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() == x2.base();
    }

    template<class T, class T2>
    bool operator!=(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() != x2.base();
    }

    template<class T, class T2>
    bool operator>=(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() <= x2.base();
    }

    template<class T, class T2>
    bool operator<=(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() >= x2.base();
    }

    template<class T, class T2>
    bool operator>(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() < x2.base();
    }

    template<class T, class T2>
    bool operator<(const reverse_iterator<T> &x, const reverse_iterator<T2> &x2)
    {
        return x.base() > x2.base();
    }
}