#pragma once

#include <cstddef>
#include "utils.hpp"

namespace ft 
{
    class input_iterator_tag {};
    class output_iterator_tag {};
    class forward_iterator_tag : public input_iterator_tag {};
    class bidirectional_iterator_tag : public forward_iterator_tag {};
    class random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
    class iterator
    {
        public:
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
        protected:
            pointer value;
    };

    template <class T>
    class miterator : public iterator<random_access_iterator_tag, T>
    {
        public:
            typedef typename iterator<random_access_iterator_tag, T>::value_type         value_type;
            typedef typename iterator<random_access_iterator_tag, T>::difference_type  difference_type;
            typedef typename iterator<random_access_iterator_tag, T>::pointer   pointer;
            typedef typename iterator<random_access_iterator_tag, T>::reference reference;
            typedef typename iterator<random_access_iterator_tag, T>::iterator_category  iterator_category;

            miterator(const miterator& x) { this->value = x.value; }
            miterator(T* x) { this->value = x; }
            miterator() { this->value = NULL; }
            ~miterator() {}

            pointer   operator->() { return this->value; }
            reference operator*() { return *this->value; }
            reference operator*() const { return *this->value; }

            miterator &operator=(const miterator &x)
            {
                this->value = x.value;
                return *this;
            }

            bool operator==(const miterator &x) const
            {
                if (this->value == x.value)
                    return true;
                return false;
            }

            bool operator!=(const miterator &x) const
            {
                if (this->value == x.value)
                    return false;
                return true;
            }

            miterator operator++(int)
            {
                miterator copy(*this);
                ++this->value;
                return copy;
            }

            miterator &operator++()
            {
                ++this->value;
                return *this;
            }

            miterator operator--(int)
            {
                miterator copy(*this);
                --this->value;
                return copy;
            }

            miterator &operator--()
            {
                --this->value;
                return *this;
            }
            
            miterator operator+(difference_type n) const
            {
                miterator tmp(*this);

                tmp += n;
                return tmp;
            }

            friend miterator operator+(difference_type n, const miterator &x)
            {
                miterator tmp(x);

                tmp += n;
                return tmp;   
            }

            pointer base() const
            {
                return this->value;
            }

            miterator operator-(difference_type n) const
            {                 
                miterator tmp(*this);

                tmp -= n;
                return tmp;
            }
            
            difference_type operator-(const miterator &x) const { return this->value - x.value; }

            bool operator>(const miterator &x) const { return this->value > x.value; }
            bool operator<(const miterator &x) const { return this->value < x.value; }
            bool operator>=(const miterator &x) const { return this->value >= x.value; }
            bool operator<=(const miterator &x) const { return this->value <= x.value; }

            miterator &operator+=(difference_type n)
            {
                this->value += n;
                return *this;
            }

            miterator &operator-=(difference_type n)
            {
                this->value -= n;
                return *this;
            }

            T &operator[](difference_type n) { return this->value[n]; } 

            operator miterator<const T>() const { return miterator<const T>(this->value); }
    };

    template<class T, class T2>
    bool operator==(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() == x2.base();
    }

    template<class T, class T2>
    bool operator!=(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() != x2.base();
    }

    template<class T, class T2>
    bool operator>=(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() >= x2.base();
    }

    template<class T, class T2>
    bool operator<=(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() <= x2.base();
    }

    template<class T, class T2>
    bool operator>(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() > x2.base();
    }

    template<class T, class T2>
    bool operator<(const miterator<T> &x, const miterator<T2> &x2)
    {
        return x.base() < x2.base();
    }

    template <class T, class N>
    class map_iterator : public iterator<bidirectional_iterator_tag, T>
    {
        public:
            typedef typename iterator<bidirectional_iterator_tag, T>::value_type		value_type;
            typedef typename iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
            typedef typename iterator<bidirectional_iterator_tag, T>::pointer			pointer;
            typedef typename iterator<bidirectional_iterator_tag, T>::reference			reference;
            typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
        
        private:

            N *root;
            N *cur;
            N *tend;

            N *get_max(N *x)
            {
                while (x->right != tend)
                    x = x->right;
                return x;
            }

            N *get_min(N *x)
            {
                while (x->left != this->tend)
                {
                    x = x->left;
                }
                return x;
            }
    
            N *get_previous(N *x)
            {
                if (x == tend)
                    return get_max(root);
                if ((x->left) != tend)
                    return get_max(x->left);
                N *start = x->parent;
                while (start != tend && x == start->left)
                {
                    x = start;
                    start = start->parent;
                }
                return start;
            }

            N *get_next(N *x)
            {
                if (x == tend)
                    return tend;
                if ((x->right) != tend)
                    return get_min(x->right);
                N *start = x->parent;
                while (start != tend && x == start->right)
                {
                    x = start;
                    start = start->parent;
                }
                return start;
            }

        public:
            map_iterator() : root(NULL), cur(NULL), tend(NULL) {}
            map_iterator(const map_iterator& x) : root(x.root), cur(x.cur), tend(x.tend) {}
            map_iterator(N *root, N *cur, N *tend) : root(root), cur(cur), tend(tend) {}
            ~map_iterator() {}

            pointer   operator->() const { return &(cur->data); }
            reference operator*() { return this->cur->data; }
            reference operator*() const { return this->cur->data; }

            map_iterator &operator=(const map_iterator &x)
            {
                root = x.root;
                cur = x.cur;
                tend = x.tend;
                return *this;
            }

            bool operator==(const map_iterator &x) const
            {
                if (this->cur == x.cur)
                    return true;
                return false;
            }

            bool operator!=(const map_iterator &x) const
            {
                if (this->cur == x.cur)
                    return false;
                return true;
            }

            map_iterator operator++(int)
            {
                map_iterator copy(*this);
                ++(*this);
                return copy;
            }

            map_iterator &operator++()
            {
                cur = get_next(cur);
                return *this;
            }

            map_iterator operator--(int)
            {
                map_iterator copy(*this);
                --(*this);
                return copy;
            }

            map_iterator &operator--()
            {
                cur = get_previous(cur);
                return *this;
            }

            pointer base() const
            {
                return &cur->data;
            }

            operator map_iterator<const T, N>() const { return map_iterator<const T, N>(root, cur, tend); }
    };

    template<class T, class Node>
    bool operator==(const map_iterator<T, Node> &x, const map_iterator<T, Node> &x2)
    {
        return x.base() == x2.base();
    }

    template<class T, class Node>
    bool operator!=(const map_iterator<T, Node> &x, const map_iterator<T, Node> &x2)
    {
        return x.base() != x2.base();
    }
}