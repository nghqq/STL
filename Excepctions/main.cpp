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
		throw std::exception("throwing exception from main()"); // Конструктор этого класса принимает сообщение об ошибке "...";
		int a, b;
		std::cout << "Введите два числа: "; std::cin >> a >> b;
		std::cout << a / b << std::endl;
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		// Универсальный обработчик, который выполняется, если не подошёл ни один другой обработчик;
		// Универсальный обработчик не распознает типы исключений;
		std::cerr << "Error: Что-то пошло не так...." << std::endl;
	}
}