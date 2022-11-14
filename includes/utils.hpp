#pragma once

namespace ft
{
    template<bool Cond, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <bool is_inte> 
    struct is_integral_type
    {
        static const bool value = is_inte;
    };

	template <typename T>	struct is_integral							: is_integral_type<false> {};

    // ------------------------ Base type for integral types ------------------------
	template <>	struct is_integral <bool>							    : is_integral_type<true> {};
	template <>	struct is_integral <char>						    	: is_integral_type<true> {};
	template <>	struct is_integral <char16_t>					    	: is_integral_type<true> {};
	template <>	struct is_integral <char32_t>					    	: is_integral_type<true> {};
	template <>	struct is_integral <wchar_t>					    	: is_integral_type<true> {};
	template <>	struct is_integral <signed char>					    : is_integral_type<true> {};
	template <>	struct is_integral <short int>						    : is_integral_type<true> {};
	template <>	struct is_integral <int>							    : is_integral_type<true> {};
	template <>	struct is_integral <long int>						    : is_integral_type<true> {};
	template <>	struct is_integral <long long int>					    : is_integral_type<true> {};
	template <>	struct is_integral <unsigned char>					    : is_integral_type<true> {};
	template <>	struct is_integral <unsigned short int>			        : is_integral_type<true> {};
	template <>	struct is_integral <unsigned int>					    : is_integral_type<true> {};
	template <>	struct is_integral <unsigned long int>				    : is_integral_type<true> {};
	template <>	struct is_integral <unsigned long long int>		        : is_integral_type<true> {};

    // ------------------------ Const type for integral types ------------------------
	template <>	struct is_integral <const bool>					        : is_integral_type<true> {};
	template <>	struct is_integral <const char>					        : is_integral_type<true> {};
	template <>	struct is_integral <const wchar_t>					    : is_integral_type<true> {};
	template <>	struct is_integral <const char16_t>				        : is_integral_type<true> {};
	template <>	struct is_integral <const char32_t>				        : is_integral_type<true> {};
	template <>	struct is_integral <const signed char>				    : is_integral_type<true> {};
	template <>	struct is_integral <const short int>				    : is_integral_type<true> {};
	template <>	struct is_integral <const int>						    : is_integral_type<true> {};
	template <>	struct is_integral <const long int>				        : is_integral_type<true> {};
	template <>	struct is_integral <const long long int>			    : is_integral_type<true> {};
	template <>	struct is_integral <const unsigned char>			    : is_integral_type<true> {};
	template <>	struct is_integral <const unsigned short int>		    : is_integral_type<true> {};
	template <>	struct is_integral <const unsigned int>			        : is_integral_type<true> {};
	template <>	struct is_integral <const unsigned long int>		    : is_integral_type<true> {};
	template <>	struct is_integral <const unsigned long long int>	    : is_integral_type<true> {};

    // ------------------------ Volatile type for integral types ------------------------
    template <>	struct is_integral <volatile bool>					    : is_integral_type<true> {};
	template <>	struct is_integral <volatile char>					    : is_integral_type<true> {};
	template <>	struct is_integral <volatile wchar_t>					: is_integral_type<true> {};
	template <>	struct is_integral <volatile char16_t>				    : is_integral_type<true> {};
	template <>	struct is_integral <volatile char32_t>				    : is_integral_type<true> {};
	template <>	struct is_integral <volatile signed char>				: is_integral_type<true> {};
	template <>	struct is_integral <volatile short int>				    : is_integral_type<true> {};
	template <>	struct is_integral <volatile int>						: is_integral_type<true> {};
	template <>	struct is_integral <volatile long int>				    : is_integral_type<true> {};
	template <>	struct is_integral <volatile long long int>			    : is_integral_type<true> {};
	template <>	struct is_integral <volatile unsigned char>			    : is_integral_type<true> {};
	template <>	struct is_integral <volatile unsigned short int>		: is_integral_type<true> {};
	template <>	struct is_integral <volatile unsigned int>			    : is_integral_type<true> {};
	template <>	struct is_integral <volatile unsigned long int>		    : is_integral_type<true> {};
	template <>	struct is_integral <volatile unsigned long long int>    : is_integral_type<true> {};


    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
            if (!(*first1 == *first2))
                return false;
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred)
    {
        for (; first1 != last1; ++first1, ++first2)
            if (!binary_pred(*first1, *first2))
                return false;
        return true;
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            if (*first1 < *first2)
                return true;
            else if (*first2 < *first1)
                return false;
        return first1 == last1 && first2 != last2;
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            if (comp(*first1, *first2))
                return true;
            else if (comp(*first2, *first1))
                return false;
        return first1 == last1 && first2 != last2;
    }

    template <class T1, class T2> 
    struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;
        
            first_type       first;
            second_type       second;

            pair() {}
            pair(const T1& a, const T2& b) : first(a), second(b) {}
            template <class U, class V>
            pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
    };
    
    template <class T1, class T2> 
	bool operator==( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <class T1, class T2> 
	bool operator!=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return !(lhs == rhs); }

    template <class T1, class T2> 
	bool operator<( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return lhs.first < rhs.first && lhs.second < rhs.second; }

    template <class T1, class T2> 
	bool operator<=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return lhs < rhs || lhs == rhs; }

    template <class T1, class T2> 
	bool operator>( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return lhs.first > rhs.first && lhs.second > rhs.second; }

    template <class T1, class T2> 
	bool operator>=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs )
    { return lhs > rhs || lhs == rhs; }

    template<class T1, class T2>
    ft::pair<T1,T2> make_pair(T1 t, T2 u)
    {
        return ft::pair<T1, T2>(t, u);
    }

    template<class Key, class Value>
    struct node
    {
        ft::pair<Key, Value>    data;
        node                    *parent;
        node					*left;
        node    				*right;

		node(ft::pair<Key, Value> d) : data(d), parent(NULL), left(NULL), right(NULL) {}
    };
}