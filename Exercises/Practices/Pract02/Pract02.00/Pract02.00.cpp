#include <iostream>
#include <fstream>

constexpr char SOURCE_FILE_NAME[] = "Pract02.00.cpp";
constexpr int BUFFER_SIZE = 1024;

size_t getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);

	size_t size = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);

	return size;
}

void selfPrint(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	char buffer[BUFFER_SIZE];

	while (!ifs.eof())
	{
		ifs.getline(buffer, BUFFER_SIZE);
		std::cout << buffer << std::endl;
	}
}

int main()
{
	std::ifstream ifs(SOURCE_FILE_NAME);

	std::cout << "The file has size of " << getFileSize(ifs) << "B." << std::endl;
	std::cout << std::endl;

	selfPrint(ifs);

	ifs.close();
}