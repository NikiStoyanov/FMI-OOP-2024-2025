#include <iostream>
#include <fstream>

namespace Constants
{
	constexpr int MAX_NAME_LENGTH = 50;
	constexpr int MAX_GRADES_COUNT = 100;
	constexpr char DESTINATION_FILE_NAME[] = "output.txt";
	constexpr char ORIGIN_FILE_NAME[] = "input.txt";
}

enum class Speciality
{
	SE = 0,
	CS = 1,
	IS = 2,
	I = 3
};

struct Student
{
	char name[Constants::MAX_NAME_LENGTH];
	uint16_t age;
	Speciality speciality;
	double grades[Constants::MAX_GRADES_COUNT];
};

void initializeArray(double* arr)
{
	for (int i = 0; i < Constants::MAX_GRADES_COUNT; ++i)
	{
		*arr = 0;
		arr++;
	}
}

bool saveStudentToFile(const Student& s, std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << s.name << '\n';
	ofs << s.age << '\n';
	ofs << (int)s.speciality << '\n';

	int index = 0;

	while (s.grades[index] != 0)
	{
		ofs << s.grades[index] << " ";

		index++;
	}

	ofs << '\n';

	return true;
}

bool writeStudentArrayToFile(const char* filename, const Student* students, size_t size)
{
	std::ofstream ofs(filename);

	if (!ofs.is_open())
	{
		return false;
	}

	for (size_t i = 0; i < size; ++i)
	{
		bool result = saveStudentToFile(students[i], ofs);

		if (!result)
		{
			return false;
		}
	}

	ofs.close();

	return true;
}

bool readStudentFromFile(Student& s, std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		return false;
	}

	ifs >> s.name >> s.age;
	int speciality;
	ifs >> speciality;

	ifs >> std::ws;

	s.speciality = (Speciality)speciality;

	initializeArray(s.grades);

	int index = 0;
	while (true)
	{
		ifs >> s.grades[index];
		index++;

		ifs.seekg(1, std::ios::cur);
		if (ifs.peek() == '\n' || ifs.eof())
		{
			break;
		}
	}

	return true;
}

Student* readStudentArrayFromFile(const char* filename, size_t& size)
{
	std::ifstream ifs(filename);
	Student* students = new Student[size];


	if (!ifs.is_open())
	{
		return nullptr;
	}

	for (size_t i = 0; i < size; ++i)
	{
		readStudentFromFile(students[i], ifs);
	}

	ifs.close();

	return students;
}

int main()
{
	size_t studentsCount = 2;

	Student* students = readStudentArrayFromFile(Constants::ORIGIN_FILE_NAME, studentsCount);

	writeStudentArrayToFile(Constants::DESTINATION_FILE_NAME, students, studentsCount);

	delete[] students;
}
