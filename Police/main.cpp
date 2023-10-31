#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<map>
#include<ctime>

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0,"�� ����������"},
	{1, "���������� ��������"},
	{2, "�������� � ������������ �����"},
	{3,"������ �� ������� ���� ���������"},
	{4, "���� � ��������� ���������"},
	{5, "����������� �������"},
	{6, "������������ �������� �������"},
	{7, "����������� ��������"},
	{8, "���������� ����� ���"},
	{9, "������ ������������"}
};

class Crime 
{
	int id; // ����� ������
	std::string place; // ����� ���������
	time_t time;		// ����� ���������
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
	Crime(int id, const std::string& place, const std::string& time)
	{
		set_id(id);
		set_place(place);
		set_time(time.c_str());
	}
	~Crime(){}
	
};
	std::ostream& operator<<(std::ostream& os, const Crime& obj) 
	{
		const int SIZE = 32;
		char crime_time[32]{};
		strcpy(crime_time, obj.get_time());
		crime_time[strlen(crime_time) - 1] = 0;
		return os << crime_time << ": " << obj.get_place()<<", " << obj.get_violations();
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
		LicencePlate(const std::string& plate) 
		{
			set_plate(plate);
		}
		~LicencePlate(){}

		bool operator<(const LicencePlate& other)const 
		{
			return this->plate < other.plate;
		}
		bool operator>(const LicencePlate& other)const 
		{
			return this->plate > other.plate;
		}
	};
	std::ostream& operator <<(std::ostream& os, const LicencePlate& obj) 
	{
		return os << obj.get_plate();
	}

void main() 
{
	setlocale(LC_ALL, "");
	//Crime crime;
	//crime.set_time("16:20 24/10/2023");
	//std::cout << delimiter << std::endl;
	//crime.set_time("2023/10/24 4:20");

	//Crime crime(1, "��.������", "16:20 24/10/2023");
	//std::cout << crime << std::endl;

	//LicencePlate plate("m777ab"); std::cout << plate << std::endl;
	//LicencePlate plate_1("VasyaTupenko"); std::cout << plate_1 << std::endl;

	std::map < LicencePlate, std::list<Crime>> base
	{
		{LicencePlate("m777ab"),{Crime(1,"��.������","12:20 18.05.2023"),Crime(3,"��.������","12:20 18.05.2023")}},
		{LicencePlate("m001bb"),{Crime(4,"��.�����������","22:20 20.10.2023"),Crime(5,"��.�����������","22:30 18.05.2023"),Crime(6,"��.�����������","22:30 18.05.2023")}},
		{LicencePlate("a358nt"),{Crime(2,"��.�������","14:25 22.10.2023"),Crime(9,"��.�������","14:00 22.10.2023")}},
	};
	for (std::map<LicencePlate, std::list<Crime>>::iterator bIt = base.begin(); bIt != base.end(); bIt++) 
	{
		std::cout << bIt->first << ":\n";
		for (std::list<Crime>::iterator it = bIt->second.begin(); it != bIt->second.end(); it++)
		{
			std::cout << tab << *it << ":\n";
		}
		std::cout << std::endl;
	}
	
 }