#pragma once

#include <memory>
#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                             					key_type;
            typedef T                                               					mapped_type;
            typedef ft::pair<const Key, T>                 		    					value_type;
            typedef typename std::size_t                            					size_type;
            typedef typename std::ptrdiff_t                         					difference_type;
            typedef Compare                                         					key_compare;
            typedef Allocator                                       					allocator_type;
            typedef typename allocator_type::reference				            		reference;
            typedef typename allocator_type::const_reference      						const_reference;
            typedef typename Allocator::pointer                							pointer;
            typedef typename Allocator::const_pointer          							const_pointer;
            typedef typename ft::map_iterator<value_type, ft::node<value_type> >		iterator;
            typedef typename ft::map_iterator<const value_type, ft::node<value_type> >	const_iterator;
            typedef typename ft::reverse_iterator<iterator>         					reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   					const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
				protected:
					Compare comp;
				public:
					value_compare(const Compare& c) { comp = c; }
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};

        private:
			typedef typename ft::node<value_type> node;
			typedef typename std::allocator<node> node_allocator_type;

            node_allocator_type		alloc;
			allocator_type			_alloc;
			Compare					comp_key;
			value_compare			comp_value;
			node					*tree;
			node					*tend;
			size_type				csize;

			node		*create_node(value_type pair)
			{
				node	*node = alloc.allocate(1);
				alloc.construct(node, pair);
				node->parent = tend;
				node->right = tend;
				node->left = tend;
				return node;
			}

			node		*create_tree()
			{
				create_end();
				tree = tend;
				csize = 0;
				return tree;
			}

			node	 *add_node(node *n, node *root)
			{
				(void) root;
				node *x = tree;
				node *y = tend;
				while (x != tend)
				{
					y = x;
					if (comp_key(n->data.first, x->data.first))
						x = x->left;
					else
						x = x->right;
				}
				n->parent = y;
				if (y == tend)
					tree = n;
				else if (comp_key(n->data.first, y->data.first))
					y->left = n;
				else
					y->right = n;
				csize++;
				return n;
			}

			node		*find(key_type key, node *root) const
			{
				if (root == tend || root->data.first == key)
					return root;
				else if (comp_key(key, root->data.first))
					return find(key, root->left);
				else
					return find(key, root->right);
			}

			void	dmove_nodes(node *oldn, node *newn)
			{
				if (oldn->parent == tend)
					tree = newn;
				else if (oldn == oldn->parent->left)
					oldn->parent->left = newn;
				else
					oldn->parent->right = newn;
				if (newn != tend)
					newn->parent = oldn->parent;
			}

			void create_end()
			{
				tend = alloc.allocate(1);
				tend->right = tend;
				tend->left = tend;
				tend->parent = tend;
			}

			node *get_min() const
			{
				node *x = tree;
				while (x->left != tend)
					x = x->left;
				return x;
			}

			key_type get_min_key() const { return get_min()->data.first; }

        public:
 
			// ----------------- Base -----------------

			explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : alloc(node_allocator_type()), _alloc(alloc),  comp_key(comp), comp_value(value_compare(comp)), tree(create_tree()) {}

			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : alloc(node_allocator_type()), _alloc(alloc), comp_key(comp), comp_value(value_compare(comp))
			{
				tree = create_tree();
				insert(first, last);
			}

			map(const map& other) : alloc(node_allocator_type()), _alloc(allocator_type()),  comp_key(key_compare()), comp_value(value_compare(key_compare()))
			{ 
				tree = create_tree();
				insert(other.begin(), other.end());
			}

            ~map()
			{
				clear();
				alloc.deallocate(tend, 1);
			}

            map&	operator=(const map& x)
            {
				_alloc = x._alloc;
				comp_key = x.comp_key;
				comp_value = x.comp_value;
                clear();
				tree = tend;
				insert(x.begin(), x.end());
            	return *this;
            }	

            Allocator get_allocator() const { return _alloc; }

			// ----------------- Element access  -----------------
			
            T& operator[]( const Key& key )
			{
				node		*n = find(key, tree);
				if (n != tend)
					return n->data.second;
				return add_node(create_node(ft::make_pair(key, mapped_type())), tree)->data.second;
			}

            T& at( const Key& key )
            {
				node		*n = find(key);
				if (n != tend)
					return n->data.second;
                throw std::out_of_range("map");
            }

			// ----------------- Iterators -----------------

            iterator begin() { return iterator(tree, get_min(), tend); }
            const_iterator begin() const { return const_iterator(tree, get_min(), tend); }
            iterator end() { return iterator(tree, tend, tend); }
            const_iterator end() const { return  const_iterator(tree, tend, tend); }
            reverse_iterator rbegin() { return reverse_iterator(end()); }
            reverse_iterator rend() { return reverse_iterator(begin()); }

			// ----------------- Capacity -----------------

            size_type size() const { return csize; }
            size_type max_size() const { return alloc.max_size(); }
            bool empty() const { return csize == 0; }

			// ----------------- Modifiers -----------------

			void clear() { erase(begin(), end()); }

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				node *exist = find(value.first, tree);
				if (exist != tend)
					return ft::make_pair(iterator(tree, exist, tend), false);
				node *new_node = add_node(create_node(value), tree);
				return ft::make_pair(iterator(tree, new_node, tend), true);
			}

			iterator insert( iterator pos, const value_type& value )
			{ 
				(void) pos;
				return insert(value).first;
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}

			void erase(iterator pos)
			{
				node *n = find(pos.base()->first, tree);
				if (n->left == tend)
					dmove_nodes(n, n->right);
				else if (n->right == tend)
					dmove_nodes(n, n->left);
				else
				{
					node *tmp = find(((++iterator(pos)).base())->first, tree);
					if (tmp->parent != n)
					{
						dmove_nodes(tmp, tmp->right);
						tmp->right = n->right;
						tmp->right->parent = tmp;
					}
					dmove_nodes(n, tmp);
					tmp->left = n->left;
					tmp->left->parent = tmp;
				}
				csize--;
				alloc.destroy(n);
				alloc.deallocate(n, 1);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
				{
					iterator save = first;
					first++;
					erase(save);
				}
			}

			size_type erase(const Key& key)
			{
				node *n = find(key, tree);
				if (n == tend)
					return (0);
				erase(iterator(tree, n, tend));
				return (1);
			}

			void swap(map& other)
			{
            	allocator_type  					tmp_alloc(_alloc);
				node_allocator_type 					tmp_nalloc(alloc);
				Compare								tmp_ckey(comp_key);
				value_compare								tmp_cvalue(comp_value);
				node		*tmp_tree(tree);
				size_type							tmp_size(csize);
				node							*tmp_tend(tend);

				alloc = other.alloc;
				_alloc = other._alloc;
				comp_key = other.comp_key;
				comp_value = other.comp_value;
				tree = other.tree;
				csize = other.csize;
				tend = other.tend;

				other.alloc = tmp_nalloc;
				other._alloc = tmp_alloc;
				other.comp_key = tmp_ckey;
				other.comp_value = tmp_cvalue;
				other.tree = tmp_tree;
				other.csize = tmp_size;
				other.tend = tmp_tend;
			}

			// ----------------- Lookup -----------------

			size_type count( const Key& key ) const { return find(key, tree) == tend ? 0 : 1; }

			iterator find( const Key& key )
			{
				node *n = find(key, tree);
				return n == tend ? end() : iterator(tree, n, tend);
			}

			const_iterator find( const Key& key ) const
			{
				node *n = find(key, tree);
				return n == tend ? end() : const_iterator(tree, n, tend);
			}

			ft::pair<iterator,iterator> equal_range( const Key& key ) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const { return ft::make_pair(lower_bound(key), upper_bound(key)); }

			iterator lower_bound( const Key& key ) { return find(comp_key(key, get_min_key()) ? get_min_key() : key); }
			const_iterator lower_bound( const Key& key ) const { return find(comp_key(key, get_min_key()) ? get_min_key() : key); }

			iterator upper_bound( const Key& key ) { return comp_key(key, get_min_key()) ? find(get_min_key()) : ++find(key); }
			const_iterator upper_bound( const Key& key ) const { return comp_key(key, get_min_key()) ? find(get_min_key()) : ++find(key); }

			key_compare key_comp() const  { return comp_key; }
			value_compare value_comp() const { return comp_value; }
    };
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return !(lhs == rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !(lhs == rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return lhs < rhs || lhs == rhs; }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !(lhs == rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return lhs > rhs || lhs == rhs; }

	template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
};