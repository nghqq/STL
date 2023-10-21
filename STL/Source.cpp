#include<iostream>
#include<array>
#include <vector>


#define tab "\t"
//#define STL_ARRAY
#define STL_VECTOR
template <typename T>
void vector_properties(const std::vector<T>& vec);
void main() 
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	const int N = 5;
	std::array<int, N> arr = { 3,5,8,13,21 };
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << tab;
	}
#endif // STL_ARRAY
#ifdef STL_VECTOR
	std::vector<double> vec = { 0,1,1,2,3,5,8,13,21,34 };
	for (int i = 0; i < vec.size(); i++) 
	{
		std::cout << vec[i] << tab;
	}
	std::cout << std::endl;
#endif // STL_VECTOR

	vector_properties(vec);
}
template<typename T>
void vector_properties(const std::vector<T>& vec) 
{
	std::cout << "Size:\t" << vec.size() << std::endl;
	std::cout << "Cpacity:\t" << vec.capacity() << std::endl;
	std::cout << "Max_size:\t" << vec.max_size() << std::endl;
}