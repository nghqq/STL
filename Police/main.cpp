#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<map>
#include<ctime>
#include<conio.h>

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0,"Не определено"},
	{1, "Превышение скорости"},
	{2, "Парковка в неположенном месте"},
	{3,"Проезд на красный свет светофора"},
	{4, "Езда в нетрезвом состояние"},
	{5, "Оскорбление офицера"},
	{6, "Неподчинение приказам офицера"},
	{7, "Пересечение сплошной"},
	{8, "Оставление места ДТП"},
	{9, "Ремень безопасности"}
};

class Crime 
{
	int id; // номер статьи
	std::string place; // место нарушения
	time_t time;		// время нарушения
public:
	int get_id()const 
	{
		return id;
	}
	const std::string& get_violations()const 
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const 
	{
		return place;
	}
	const char* get_time()const 
	{
		return ctime(&time);
	}
	const time_t get_timestamp()const
	{
		return time;
	}
	void set_id(int id) 
	{
		if (id >= VIOLATIONS.size())id = 0;
		this->id = id;
	}
	void set_place(const std::string& place) 
	{
		this->place = place;
	}
	void set_time(time_t time) 
	{
		this->time = time;
	}
	void set_time(const char time_str[])
	{
		const int SIZE = 20;
		char time_str_buffer[SIZE] = {};
		strcpy(time_str_buffer, time_str);
		int units[5] = {};
		char* sz_units[5] = {};
		const char delimiters[] = ":./ ";
		int n = 0;
	
		for (char* pch = strtok(time_str_buffer,delimiters); pch; pch=strtok(NULL,delimiters))
			units[n++] = std::atoi(pch);
			//for (int i : units)std::cout << i << tab; std::cout << std::endl;
			//for (char* i : sz_units)std::cout << i << tab; std::cout << std::endl;
			int colon_position = strchr(time_str, ':') - time_str;
			if (colon_position > 2)
			{
				std::reverse(units, units + 5);
				std::swap(units[0], units[1]);
			}
			//for (int i : units)std::cout << i << tab; std::cout << std::endl;
			//for (char* i : sz_units)std::cout << i << tab; std::cout << std::endl;
			std::tm tm{};
			//std::time(&time);
			//tm = *localtime(&time);
			tm.tm_hour = units[0];
			tm.tm_min = units[1];
			tm.tm_mday = units[2];
			tm.tm_mon = units[3]-1;
			tm.tm_year = units[4] - 1900;
			this->time = std::mktime(&tm);
	}
	Crime() 
	{
		id = 0;
		place = "undefined";
		time = 0;

	}
	Crime(int id, const std::string& place, const std::string& time)
	{
		set_id(id);
		set_place(place);
		set_time(time.c_str());
	}
	Crime(int id, const std::string& place, std::time_t time)
	{
		set_id(id);
		set_place(place);
		set_time(time);
	}
	~Crime(){}
	
};
/*std::istream& operator >>(std::istream& is, Crime& obj)
	{
	char sz_buffer[_MAX_PATH]{};
	is.getline(sz_buffer, _MAX_PATH);
	obj.set_time(atoi(sz_buffer));
	obj.set_id(atoi(strrchr(sz_buffer, ' ') + 1));
	*strrchr(sz_buffer, ' ') = 0;
	char* psz_place = strchr(sz_buffer, ' ') + 1;
	obj.set_place(psz_place);
	return is;
	}*/
	std::ostream& operator<<(std::ostream& os, const Crime& obj) 
	{
		const int SIZE = 32;
		char crime_time[SIZE]{};
		strcpy(crime_time, obj.get_time());
		crime_time[strlen(crime_time) - 1] = 0;
		return os << crime_time << ": " << obj.get_place()<<", " << obj.get_violations();
	}
	std::ofstream& operator <<(std::ofstream& ofs, const Crime& obj)
	{
		ofs << obj.get_timestamp() << " " << obj.get_place() << " " << obj.get_id();
		return ofs;
	}
	class LicencePlate
	{
		std::string plate;
	public:
		const std::string& get_plate()const
		{
			return plate;
		}
		void set_plate(const std::string& plate)
		{
			if (plate.size() < 10)this->plate = plate;
			else this->plate = "Error Format ";
		}
		LicencePlate() {}
		LicencePlate(const std::string& plate) 
		{
			set_plate(plate);
		}
		~LicencePlate(){}

		bool operator==(const LicencePlate& other)const
		{
			return this->plate == other.plate;
		}
		bool operator!=(const LicencePlate& other)const
		{
			return this->plate != other.plate;
		}

		bool operator<(const LicencePlate& other)const 
		{
			return this->plate < other.plate;
		}
		bool operator>(const LicencePlate& other)const 
		{
			return this->plate > other.plate;
		}
	};
	std::istream& operator >>(std::istream& is, LicencePlate& obj) 
	{
		std::string plate;
		is >> plate;
		obj.set_plate(plate);
		return is;
	}
	std::ostream& operator <<(std::ostream& os, const LicencePlate& obj) 
	{
		return os << obj.get_plate();
	}
	std::ifstream& getline(std::ifstream& ifs, LicencePlate& obj, const char delim) 
	{
		std::string plate;
std::getline(ifs, plate, delim);
obj.set_plate(plate);
return ifs;
	}



	void print(const std::map<LicencePlate, std::list<Crime>>& base);
	void print(const std::map<LicencePlate, std::list<Crime>>& base, LicencePlate plate);
	void print(const std::map<LicencePlate, std::list<Crime>>& base, LicencePlate start_plate, LicencePlate end_plate);
	void save(const std::map<LicencePlate, std::list<Crime>>& base, const std::string& filename);
	std::map<LicencePlate, std::list<Crime>>load(const std::string& filename);




	void main()
	{
		setlocale(LC_ALL, "");
		//Crime crime;
		//crime.set_time("16:20 24/10/2023");
		//std::cout << delimiter << std::endl;
		//crime.set_time("2023/10/24 4:20");

		//Crime crime(1, "ул.Ленина", "16:20 24/10/2023");
		//std::cout << crime << std::endl;

		//LicencePlate plate("m777ab"); std::cout << plate << std::endl;
		//LicencePlate plate_1("VasyaTupenko"); std::cout << plate_1 << std::endl;

		/*std::map < LicencePlate, std::list<Crime>> base
		{
			{LicencePlate("m777ab"),{Crime(1,"ул.Ленина","12:20 18.05.2023"),Crime(3,"ул.Ленина","12:20 18.05.2023")}},
			{LicencePlate("m001bb"),{Crime(4,"ул.Космонавтов","22:20 20.10.2023"),Crime(5,"ул.Космонавтов","22:30 18.05.2023"),Crime(6,"ул.Космонавтов","22:30 18.05.2023")}},
			{LicencePlate("a358nt"),{Crime(2,"ул.Пушкина","14:25 22.10.2023"),Crime(9,"ул.Пушкина","14:00 22.10.2023")}},
		};
		print(base);
		save(base, "base.txt");*/
		std::map<LicencePlate, std::list<Crime>> base = load("base.txt");
		print(base);

		/*LicencePlate plate;
		std::cout << "Введите номер: "; std::cin >> plate;
		print(base, plate);*/
		/*LicencePlate start_plate, end_plate;
		std::cout << "Введите начальный номер: "; std::cin >> start_plate;
		std::cout << "Введите конечный номер номер: "; std::cin >> end_plate;
		print(base, start_plate, end_plate);*/
		//system("PAUSE");
		//system("CLS");
		//main();

		char key;
		do
		{
			system("CLS");
			std::cout << "1.Вывод всей базы ;" << std::endl;
			std::cout << "2.Вывод информации по номеру ;" << std::endl;
			std::cout << "3.Вывод информации по диапазону номеров ;" << std::endl;
			std::cout << "4.Добавить нарушение ;" << std::endl;
			std::cout << "5.Сохранить базу в файл ;" << std::endl;
			std::cout << "6.Загрузить базу из файла ;" << std::endl;
			key = _getch();
			switch (key)
			{
			case '1': print(base); break;
			case '2':
			{
				LicencePlate plate;
				std::cout << "Введите номер: "; std::cin >> plate;
				print(base, plate);
				break;
			}
			case '3':
			{
				LicencePlate start_plate;
				LicencePlate end_plate;
				std::cout << "Введите начальный номер: "; std::cin >> start_plate;
				std::cout << "Введите конечный номер: "; std::cin >> end_plate;
				print(base, start_plate, end_plate);
			}
				break;
			case '4':
			{
				LicencePlate plate;
				std::string place;
				int id;
				std::cout << "Введите номер: "; std::cin >> plate;
				std::cout << "Введите место: ";
				std::cin.clear();
				std::cin.ignore();
				SetConsoleCP(1251);
				std::getline(std::cin, place);
				SetConsoleCP(866);
				std::cout << "Выберите совершенное нарушение:\n";
				for (std::pair<int, std::string>i : VIOLATIONS)std::cout << i.first << ". " << i.second << std::endl;
				std::cin >> id;
				Crime crime(id, place, time(NULL));
				base[plate].push_back(crime);
				std::cout << plate << ":\n";
				for (Crime i : base[plate])std::cout << i << ";\n";
				
			}
			case'5':
				save(base, "base.txt"); break;

			case'6':

				std::map<LicencePlate, std::list<Crime>> base = load("base.txt");
				print(base); break;
			}

			system("PAUSE");
			
		} while (key != 27);
 }

void print(const std::map<LicencePlate, std::list<Crime>>& base) 
{
	for (std::map<LicencePlate, std::list<Crime>>:: const_iterator bIt = base.begin(); bIt != base.end(); bIt++)
	{
		std::cout << bIt->first << ":\n";
		for (std::list<Crime>::const_iterator it = bIt->second.begin(); it != bIt->second.end(); it++)
		{
			std::cout <<  *it << ":\n";
		}
		std::cout << std::endl;
	}
}

void print(const std::map<LicencePlate, std::list<Crime>>& base, LicencePlate plate) 
{
	try
	{
		std::cout << "Base size: " << base.size() << std::endl;
		std::cout << "Plate: " << plate << std::endl << "violations: \n";
		for (std::list<Crime>::const_iterator it = base.at(plate).cbegin(); it != base.at(plate).cend(); it++)
		{
			std::cout << tab << *it << ";\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "В базе нет такого номера. " << std::endl;
	}
}
void print(const std::map<LicencePlate, std::list<Crime>>& base, LicencePlate start_plate, LicencePlate end_plate) 
{
	for (std::map<LicencePlate, std::list<Crime>>::const_iterator bit = base.lower_bound(start_plate); bit != base.upper_bound(end_plate); ++bit) 
	{
		std::cout << bit->first << ":\n";
		for (std::list<Crime>::const_iterator it = bit->second.begin(); it != bit->second.end(); ++it) 
		{
			std::cout << tab << *it << ":\n";
		}
		std::cout << std::endl;
	}
}

void save(const std::map<LicencePlate, std::list<Crime>>& base, const std::string& filename) 
{
	std::ofstream fout(filename);
	for (std::map<LicencePlate, std::list<Crime>>::const_iterator bIt = base.begin(); bIt != base.end(); bIt++)
	{
		fout << bIt->first << ":";
		for (std::list<Crime>::const_iterator it = bIt->second.begin(); it != bIt->second.end(); it++)
		{
			fout<< *it << ", ";
		}
		int position = fout.tellp();
		fout.seekp(position - 2);
		fout << ";\n";
	}
	fout.close();
	std::string command = "start notepad " + filename;
	system(command.c_str());
}

std::map<LicencePlate, std::list<Crime>>load(const std::string& filename) 
{
	std::map<LicencePlate, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open()) 
	{
		while (!fin.eof()) 
		{
			LicencePlate plate;
			getline(fin, plate, ':');
			std::string all_crimes;
			std::getline(fin, all_crimes);
			//std::cout << plate << tab << all_crimes << std::endl;
			char* all_crimes_buffer = new char[all_crimes.size() + 1] {};
			strcpy(all_crimes_buffer, all_crimes.c_str());
			char delimiters[] = ":,;";
			for (char* pch = strtok(all_crimes_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				Crime crime;
				crime.set_time(atoi(pch));
				crime.set_id(atoi(strrchr(pch, ' ') + 1));
				while (pch[0] == ' ')pch = strchr(pch, ' ') + 1;
				pch = strchr(pch, ' ') + 1;
				*strrchr(pch, ' ') = 0;
				crime.set_place(pch);
				base[plate].push_back(crime);
			}
			delete[]all_crimes_buffer;
		}
		fin.close();
	}
	else 
	{
		std::cerr << "Error: File not found" << std::endl;
	}
	return base;
}

