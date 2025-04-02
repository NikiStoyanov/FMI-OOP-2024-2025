#include <iostream>
#include <fstream>

namespace Constants
{
	constexpr char FILE_NAME[] = "data.dat";
}

int main()
{
	int n;
	std::cin >> n;

	int* numbers = new int[n];

	for (int i = 0; i < n; ++i)
	{
		std::cin >> numbers[i];
	}

	std::ofstream ofs(Constants::FILE_NAME, std::ios::binary);

	ofs.write((const char*)&n, sizeof(n));
	ofs.write((const char*)numbers, n * sizeof(int));

	delete[] numbers;
	ofs.close();

	std::ifstream ifs(Constants::FILE_NAME, std::ios::binary);

	int size;
	ifs.read((char*)&size, sizeof(size));

	int* numbersFromFile = new int[size];
	ifs.read((char*)numbersFromFile, size * sizeof(int));

	for (int i = 2; i < size; i += 3)
	{
		std::cout << numbersFromFile[i] << " ";
	}
}
