#include "../includes/vector.hpp"
#include "../includes/map.hpp"
#include "../includes/iterator.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>

#define LIB ft
#define TYPE std::string
#define T1 std::string
#define T2 int
/*
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
}*/

/*void printm(ft::map<T1, T2> m)
{
  std::cout << " /////////////////////////////////// \n";
  //std::cout << m.size() << " ------- \n\n";
  ft::map<T1, T2>::iterator it = m.begin();
  //ite = m.end();
  while (it != m.end())
  {
    std::cout << " - " << it->first << " - " << it->second << std::endl;
    it++;
  }
  std::cout << " /////////////////////////////////// \n";
}

void printm(std::map<T1, T2> m)
{
  std::cout << " /////////////////////////////////// \n";
  //std::cout << m.size() << " ------- \n\n";
  std::map<T1, T2>::iterator it = m.begin();
  //ite = m.end();
  while (it != m.end())
  {
    std::cout << " - " << it->first << " - " << it->second << std::endl;
    it++;
  }
  std::cout << " /////////////////////////////////// \n";
}*/

int main() 
{

    ft::map<T1, T2> list;
    std::map<T1, T2> list2;

    list2.insert(std::make_pair("COUCOU", 42));
    list2.insert(std::make_pair("COCO", 500));
    list2.insert(std::make_pair("x", 85));

    list.insert(ft::make_pair("COUCOU", 42));
    //list.insert(ft::make_pair("COCO", 500));
    //list.insert(ft::make_pair("x", 85));

    std::cout << " FT : - " << list.max_size() << " - \n";
    std::cout << " ST : - " << list2.max_size() << " - \n";
    /*std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    std::map<T1, T2> list;

    list.insert(std::make_pair("COUCOU", 42));
    list.insert(std::make_pair("COCO", 500));
    list.insert(std::make_pair("x", 85));

    list.erase(++list.begin());

    printm(list);

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;*/
  /*std::map<T1, T2> list2;

  list2.insert(std::make_pair("COUCOU", 42));
  list2.insert(std::make_pair("COCO", 500));
  list2.insert(std::make_pair("x", 85));

  std::cout << " FT : - " << list.max_size() << " - \n";
  std::cout << " ST : - " << list2.max_size() << " - \n";*/

  //printm(list);

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
  //ft::vector<int> vct(5);
  //ft::vector<int>::reverse_iterator it = vct.rbegin();
	//std::vector<int>::const_reverse_iterator ite = vct.rbegin();

/*
  printv(vct);

	for (int i = 0; i < 5; ++i)
		it[i] = (5 - i) * 5;
  
  printv(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;*/

}