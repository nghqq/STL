#include<iostream>
#include <exception>


void main() 
{
	setlocale(LC_ALL, "");

	/*try
	{
		throw 0;
	}
	catch (int e)
	{
		std::cerr << "Error# " << e << std::endl;
	}*/

	try
	{
		throw std::exception("throwing exception from main()"); // ����������� ����� ������ ��������� ��������� �� ������ "...";
		int a, b;
		std::cout << "������� ��� �����: "; std::cin >> a >> b;
		std::cout << a / b << std::endl;
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		// ������������� ����������, ������� �����������, ���� �� ������� �� ���� ������ ����������;
		// ������������� ���������� �� ���������� ���� ����������;
		std::cerr << "Error: ���-�� ����� �� ���...." << std::endl;
	}
}