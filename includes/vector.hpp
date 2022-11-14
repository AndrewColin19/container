#pragma once

#include <memory>
#include "iterator.hpp"
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <typename T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                               value_type;
            typedef Allocator                                       allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::difference_type        difference_type;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename ft::miterator<value_type>              iterator;
            typedef typename ft::miterator<const value_type>        const_iterator;
            typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

        private:
            allocator_type  alloc;
            pointer         ptr;
            size_type       csize;
            size_type       total_size;

        public:
            explicit vector(const allocator_type& alloc = allocator_type()) : alloc(alloc), ptr(nullptr), csize(0), total_size(0) {}
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc(alloc), ptr(nullptr), csize(0), total_size(0)
            {
                while (n--)
                    push_back(val);
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :  alloc(alloc), ptr(nullptr), csize(0), total_size(0)
            {
                assign(first, last);
            }

            vector (const vector& x) : alloc(allocator_type()), ptr(nullptr), csize(0), total_size(0)
            {
                assign(x.begin(), x.end());
            }

            ~vector()
            {
                while (csize)
                {
                    alloc.destroy(ptr + csize);
                    csize--;
                }
                alloc.deallocate(ptr, total_size);
            }

            vector&     operator=(const vector& x)
            {
                clear();
                assign(x.begin(), x.end());
                return *this;
            }

            iterator begin() { return iterator(ptr); }
            const_iterator begin() const { return const_iterator(ptr); }
            iterator end() { return ptr == NULL ? iterator(ptr) : iterator(ptr + csize); }
            const_iterator end() const { return ptr == NULL ? const_iterator(ptr) : const_iterator(ptr + csize); }
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }
            size_type size() const { return csize; }
            size_type max_size() const { return alloc.max_size(); }

            void resize (size_type n, value_type val = value_type())
            {
                while (n != csize)
                {
                    if (n < csize)
                        pop_back();
                    else
                        push_back(val);
                }
            }

            size_type capacity() const { return total_size; }
            bool empty() const { return csize == 0; }

            void reserve (size_type n)
            {
                if (n <= total_size)
                    return ;
                pointer     ptr_tmp = ptr;
                size_type   size_tmp = total_size;

                ptr = alloc.allocate(n);
                total_size = n;
                for (size_t i = 0; i < csize; i++)
                    alloc.construct(ptr + i, ptr_tmp[i]);
                for (size_t i = 0; i < csize; i++)
                    alloc.destroy( ptr_tmp + i);
                alloc.deallocate(ptr_tmp, size_tmp);
            }

            reference operator[](size_type n) { return ptr[n]; }

            reference at(size_type n)
            {
                if (n < csize)
                    return ptr[n];
                throw std::out_of_range("vector");
            }

            const_reference at(size_type n) const
            {
                if (n < csize)
                    return ptr[n];
                throw std::out_of_range("vector");
            }

            reference front() { return *ptr; }
            const_reference front() const { return *ptr; };
            reference back() { return ptr[csize - 1]; }
            const_reference back() const { return ptr[csize - 1]; };

            void assign(size_type n, const value_type& val)
            {
                clear();
                while (csize < n)
                    push_back(val);
            }

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, typename ft::enable_if<!(ft::is_integral<InputIterator>::value) >::type* = NULL)
            {
                clear();
                while (first != last)
                {
                    push_back(*first);
                    first++;
                }
            }

            void push_back (const value_type& val)
            {
                if (csize >= total_size)
                {
                    pointer     ptr_tmp = ptr;
                    size_type   size_tmp = total_size;
                    
                    total_size = total_size == 0 ? 1 : total_size * 2;
                    ptr = alloc.allocate(total_size);

                    for (size_t i = 0; i < csize; i++)
                        alloc.construct(ptr + i, ptr_tmp[i]);
                    for (size_t i = 0; i < csize; i++)
                        alloc.destroy(ptr_tmp + i);
                    alloc.deallocate(ptr_tmp, size_tmp);
                }
                alloc.construct(ptr + csize, val);
                csize++;
            }

            void pop_back()
            {
                if (csize == 0)
                    return;
                csize--;
                alloc.destroy(ptr + csize);
            }

            iterator insert(iterator position, const value_type& val)
            {
                if(csize == 0)
                {
                    push_back(val);
                    return begin();
                }
                vector tmp(position, end());
                while (end() != position)
                    pop_back();
                push_back(val);
                iterator return_val = end() - 1;
                insert(end(), tmp.begin(), tmp.end());
                return return_val;
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                if (csize == 0)
                {
                    while (n--)
                        push_back(val);
                    return ;
                }
                vector tmp(position, end());
                while (end() != position)
                    pop_back();
                while (n--)
                    push_back(val);
                insert(end(), tmp.begin(), tmp.end());
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!(ft::is_integral<InputIterator>::value) >::type* = NULL)
            {
                if (csize == 0)
                {
                    while (first != last)
                    {
                        push_back(*first);
                        first++;
                    }
                    return ;
                }
                vector tmp(position, end());
                while (end() != position)
                    pop_back();
                while (first != last)
                {
                    push_back(*first);
                    first++;
                }
                iterator i = tmp.begin();
                iterator j = tmp.end();
                while (i != j)
                {
                    push_back(*i);
                    i++;
                }
            }

            iterator erase(iterator position)
            {
                if (position == end() - 1)
                {
                    pop_back();
                    return end();
                }
                vector tmp(position, end());
                while (end() != position)
                    pop_back();
                size_type i = csize;
                insert(end(), tmp.begin() + 1, tmp.end());
                return begin() + i;
            }

            iterator erase(iterator first, iterator last)
            {
                while (--last != first)
                    erase(last);
                return erase(first);
            }

            void swap(vector& x)
            {
                allocator_type  tmp_alloc(alloc);
                pointer         tmp_ptr(ptr);
                size_type       tmp_size(csize);
                size_type       tmp_total_size(total_size);

                alloc = x.alloc;
                ptr = x.ptr;
                csize = x.csize;
                total_size = x.total_size;

                x.alloc = tmp_alloc;
                x.ptr = tmp_ptr;
                x.csize = tmp_size;
                x.total_size = tmp_total_size;
            }

            void clear()
            {
                while (csize)
                {
                    alloc.destroy(ptr + csize);
                    csize--;
                }
            }

            Allocator get_allocator() const { return alloc; }
    };

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !(lhs == rhs); }
    
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !(lhs == rhs); }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return lhs < rhs || lhs == rhs; }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return lhs > rhs || lhs == rhs; }

    template <class T, class Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {x.swap(y); }
}