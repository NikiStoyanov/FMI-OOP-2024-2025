#include <iostream>
#include <fstream>

constexpr char FILE_NAME[] = "test.txt";

size_t getCharOccurencies(std::ifstream& ifs, char ch)
{
	if (!ifs.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return -1;
	}

	int count = 0;
	size_t currPos = ifs.tellg();

	while (!ifs.eof())
	{

		char currChar = ifs.get();

		if (currChar == ch)
		{
			count++;
		}
	}

	return count;
}

int main()
{
	std::ifstream ifs(FILE_NAME);

	std::cout << getCharOccurencies(ifs, 'a') << std::endl;

	ifs.close();
}