#include<iostream>
#include<map>
#include<set>

#define tab "\t"
#define delimeter "\n------------------------------------\n"

//#define STL_SET
void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_SET
	std::set<int> set = { 50,25,75,16,32,64,80 };// set - обычное бинарное дерево;
	// multiset - уникальное бинарное дерево; Аналогично с map;
	for (std::set<int>::iterator it = set.begin(); it != set.end(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
#endif // STL_SET
	//std::pair<key,value>
	std::map<int, std::string> week =
	{
		std::pair<int,std::string>(0,"Sunday"),
		std::pair<int,std::string>(1,"Monday"),
		std::pair<int,std::string>(2,"Tuesday"),
		{3,"Wednesday"},
		{3,"Wednesday"},
		{3,"Wednesday"},
		{3,"Wednesday"},
		{3,"Wednesday"},
		std::pair<int,std::string>(4,"Thursday"),
		std::pair<int,std::string>(5,"Friday"),
		{6,"Saturday"},
		{6,"Saturday"},
		{6,"Saturday"},
		std::pair<int,std::string>(7,"Sunday"),
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); it++) 
	{
		std::cout << it->first << tab << it->second << std::endl;
	}
}