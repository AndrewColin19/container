/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 06:03:50 by acolin            #+#    #+#             */
/*   Updated: 2022/08/28 06:17:07 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include "utils.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        protected:
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
			pointer			_begin;
        
        public:
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

        public:
            explicit vector (const allocator_type& alloc = allocator_type()): 
                _alloc(alloc), _capacity(0), _size(0), _begin(NULL)
            {}
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
                _alloc(alloc), _capacity(0), _size(0), _begin(NULL) 
            {
                size_type i = 0;
                while (i < n) 
                {
                    this.push_back(val);
                    i++;
                }
            }
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());	
            vector (const vector& x);

            ~vector(void)
			{
				clear();
				_alloc.deallocate(_begin, _capacity);
			}

            void assign (size_type n, const value_type& val);

            template <class InputIterator>
            void assign (InputIterator first, InputIterator last);

            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(begin + i);
                _size = 0;
                _capacity = 0;
            }
    }
} // namespace ft

#endif
