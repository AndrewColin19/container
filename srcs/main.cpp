#include "../includes/vector.hpp"
#include "../includes/iterator.hpp"
#include <iostream>
#include <vector>
#include <string>

#define LIB ft
#define TYPE std::string

void printv(ft::vector<int> vct)
{
  std::cout << " /////////////////////////////////// \n";
  std::cout << vct.size() << " ------- \n\n";
  unsigned long i = 0;
  while (i < vct.size())
  {
    std::cout << vct[i++] << " ------- \n";
  }
  std::cout << " /////////////////////////////////// \n";
}

void printv(std::vector<int> vct)
{
  std::cout << " /////////////////////////////////// \n";
  std::cout << vct.size() << " ------- \n\n";
  unsigned long i = 0;
  while (i < vct.size())
  {
    std::cout << vct[i++] << " ------- \n";
  }
  std::cout << " /////////////////////////////////// \n";
}

int main() 
{
  /*
  ft::vector<int> toto = ft::vector<int>();
  std::vector<int> tata = std::vector<int>();

  tata.push_back(42);
  tata.push_back(82);
  tata.push_back(92);
  tata.push_back(28);
  tata.push_back(998);

  toto.push_back(42);
  toto.push_back(82);
  toto.push_back(92);
  toto.push_back(28);
  toto.push_back(998);

	std::cout << *toto.erase(toto.end() - 1) << " ------- 3\n";
	std::cout << *tata.erase(tata.end() - 1) << " ------- 3\n";

	std::cout << *(toto.end()) << " ------- 2\n";
	std::cout << *(tata.end()) << " ------- 2\n";

  ft::miterator<ft::vector<int>::value_type > it = toto.begin();
  it++;

  std::cout << *toto.erase(toto.end() - 3, toto.end() - 1) << " ------- \n";
  std::cout << *tata.erase(tata.end() - 3, tata.end() - 1) << " ------- \n";
  printv(toto);
  printv(tata);*/

  /*toto.insert(it, tata.begin(), tata.end());

  ft::miterator<ft::vector<int>::value_type > it2 = toto.begin();
  it2++;

  ft::miterator<ft::vector<int>::value_type > it3 = toto.begin();
  it3 += 4;*/
  /*
	LIB::vector<TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
  printv(vct);

	std::cout << *vct.erase(vct.begin() + 2) << " ------- 1\n";
  printv(vct);
  
	std::cout << *vct.end() << " ------- \n";

	std::cout << *vct.erase(vct.begin()) << " ------- 2\n";
  printv(vct);
	std::cout << *vct.erase(vct.end() - 1) << " ------- 3\n";
  printv(vct);

	std::cout << *vct.erase(vct.begin(), vct.begin() + 3) << " ------- 4\n";
  printv(vct);
	std::cout << *vct.erase(vct.end() - 3, vct.end() - 1) << " ------- 5\n";
  printv(vct);

	vct.push_back("Hello");
	vct.push_back("Hi there");
  printv(vct);
	std::cout << *vct.erase(vct.end() - 3, vct.end()) << " ------- 6\n";
  printv(vct);

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
  printv(vct);

	std::cout << *vct.erase(vct.begin(), vct.end()) << " ------- \n";
  printv(vct);*/
  ft::vector<int> vct(5);
  ft::vector<int>::reverse_iterator it = vct.rbegin();
	//std::vector<int>::const_reverse_iterator ite = vct.rbegin();


  printv(vct);

	for (int i = 0; i < 5; ++i)
		it[i] = (5 - i) * 5;
  
  printv(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

}