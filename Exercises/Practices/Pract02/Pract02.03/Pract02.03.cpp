#include <iostream>
#include <fstream>

namespace CONSTANTS
{
    constexpr char INPUT_FILE_NAME[] = "input.txt";
    constexpr char ASCENDING_FILE_NAME[] = "ascending.txt";
    constexpr char DESCENDING_FILE_NAME[] = "descending.txt";
}

size_t getFileSize(std::ifstream& ifs)
{
    size_t currPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);

    size_t size = ifs.tellg();
    ifs.seekg(currPos, std::ios::beg);

    return size;
}

size_t getArraySize(std::ifstream& ifs)
{
    int size = 0;
    ifs >> size;

    return size;
}

void getNumbersFromFile(std::ifstream& ifs, int* numbers, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
        ifs >> numbers[i];
	}
}

void sortArray(int* arr, size_t arraySize, bool(*predicate)(int, int))
{
	for (size_t i = 0; i < arraySize - 1; i++)
	{
        size_t currIndex = i;
		for (size_t j = i + 1; j < arraySize; j++)
		{
			if (!predicate(arr[currIndex], arr[j]))
			{
                currIndex = j;
			}
		}

        if (currIndex != i)
        {
            std::swap(arr[i], arr[currIndex]);
        }
	}
}

bool ascending(int a, int b)
{
    return b > a;
}

bool descending(int a, int b)
{
    return b < a;
}

void writeArrayToFile(const int* numbers, size_t arraySize, const char* fileName)
{
    std::ofstream ofs(fileName);

    ofs << arraySize << std::endl;

    for (size_t i = 0; i < arraySize; i++)
    {
        ofs << numbers[i] << ' ';
    }

    ofs.close();
}

int main()
{
    std::ifstream ifs(CONSTANTS::INPUT_FILE_NAME);

    if (!ifs.is_open())
    {
        return -1;
    }

    if (getFileSize(ifs) == 0)
    {
        ifs.close();
        return -1;
    }

    int arraySize = getArraySize(ifs);

    int* numbers = new int[arraySize];

    getNumbersFromFile(ifs, numbers, arraySize);

    ifs.close();

    sortArray(numbers, arraySize, ascending);
    writeArrayToFile(numbers, arraySize, CONSTANTS::ASCENDING_FILE_NAME);

    sortArray(numbers, arraySize, descending);
    writeArrayToFile(numbers, arraySize, CONSTANTS::DESCENDING_FILE_NAME);

    delete[] numbers;
}