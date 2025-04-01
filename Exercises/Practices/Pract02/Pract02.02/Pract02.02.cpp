#include <iostream>
#include <fstream>

constexpr char FILE_NAME[] = "result.txt";

void writeSumAndProductInFile(int a, int b, int c)
{
	std::ofstream ofs(FILE_NAME);

	if (!ofs.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	int sum = a + b + c;
	int product = a * b * c;

	ofs << sum << std::endl;
	ofs << product << std::endl;

	ofs.close();
}

void getSumAndProductFromFile(int& sum, int& product)
{
	std::ifstream ifs(FILE_NAME);

	if (!ifs.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	ifs >> sum;
	ifs >> product;

	ifs.close();
}

int main()
{
	int a, b, c;
	std::cin >> a >> b >> c;

	writeSumAndProductInFile(a, b, c);

	int sum, product;

	getSumAndProductFromFile(sum, product);

	std::cout << "Sum: " << sum << std::endl;
	std::cout << "Product: " << product << std::endl;
}