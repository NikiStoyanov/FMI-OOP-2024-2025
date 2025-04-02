#include <iostream>
#include <sstream>

namespace Constants
{
	constexpr int MAX_INPUT_LENGTH = 2048;
	constexpr int MAX_NUMBERS_COUNT = 1024;
}


int getSum(std::stringstream& ss)
{
	int sum = 0;
	while (!ss.eof())
	{
		int number;
		ss >> number;
		sum += number;
	}

	ss.clear();
	ss.seekg(0, std::ios::beg);

	return sum;
}

int getMinElement(std::stringstream& ss)
{
	int min = INT_MAX;
	while (!ss.eof())
	{
		int number;
		ss >> number;
		if (number < min)
		{
			min = number;
		}
	}

	ss.clear();
	ss.seekg(0, std::ios::beg);

	return min;
}

int getMaxElement(std::stringstream& ss)
{
	int max = INT_MIN;
	while (!ss.eof())
	{
		int number;
		ss >> number;
		if (number > max)
		{
			max = number;
		}
	}

	ss.clear();
	ss.seekg(0, std::ios::beg);

	return max;
}

double getAverage(std::stringstream& ss)
{
	int count = 0;
	double average = getSum(ss);

	while (!ss.eof())
	{
		count++;
		int number;
		ss >> number;
	}

	ss.clear();
	ss.seekg(0, std::ios::beg);

	return average / count;
}

int main()
{
	char input[Constants::MAX_INPUT_LENGTH];

	std::cin.getline(input, Constants::MAX_INPUT_LENGTH);

	std::stringstream ss(input);

	std::cout << getSum(ss) << std::endl;
	std::cout << getMinElement(ss) << std::endl;
	std::cout << getMaxElement(ss) << std::endl;
	std::cout << getAverage(ss) << std::endl;
}