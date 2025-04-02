#include <iostream>
#include <fstream>

namespace Constants
{
	constexpr int MAX_TITLE_LENGTH = 20;
	constexpr int MAX_AUTHOR_NAME_LENGTH = 20;
	constexpr int MAX_CATALOG_CAPACITY = 1024;
	constexpr char INPUT_FILE_NAME[] = "input.dat";
	constexpr char OUTPUT_FILE_NAME[] = "output.dat";
}

struct Book
{
	char title[Constants::MAX_TITLE_LENGTH];
	char authorName[Constants::MAX_AUTHOR_NAME_LENGTH];
	uint16_t year;
	uint16_t availableCopies;
};

struct Catalog
{
	uint16_t size = 0;
	Book books[Constants::MAX_CATALOG_CAPACITY];
};

size_t getFileSize(std::ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);

	size_t size = ifs.tellg();
	ifs.seekg(0, currPos);

	return size;
}

bool searchBookByTitle(const char* title, const Catalog& catalog)
{
	for (int i = 0; i < catalog.size; ++i)
	{
		if (strcmp(catalog.books[i].title, title) == 0)
		{
			return true;
		}
	}
	
	return false;
}

bool addBookToCatalog(const Book& book, Catalog& catalog)
{
	if (catalog.size == Constants::MAX_CATALOG_CAPACITY)
	{
		std::cout << "No space left in the catalog." << std::endl;
		return false;
	}

	if (searchBookByTitle(book.title, catalog))
	{
		std::cout << "There is already a book with this title." << std::endl;
		return false;
	}

	catalog.books[catalog.size] = book;
	catalog.size++;

	return true;
}

void printAllBooks(const Catalog& catalog)
{
	for (int i = 0; i < catalog.size; ++i)
	{
		std::cout << catalog.books[i].title << " " << catalog.books[i].authorName << " ";
		std::cout << catalog.books[i].year << " " << catalog.books[i].availableCopies;
		std::cout << std::endl;
	}
}

bool saveCatalogToFile(const char* filename, const Catalog& catalog)
{
	std::ofstream ofs(filename, std::ios::binary);

	if (!ofs.is_open())
	{
		return false;
	}

	ofs.write((const char*)catalog.books, catalog.size * sizeof(Book));

	ofs.close();
}

void readBooksFromFile(const char* filename, Catalog& catalog)
{
	std::ifstream ifs(filename, std::ios::binary);


	if (!ifs.is_open())
	{
		return;
	}

	size_t fileSize = getFileSize(ifs);
	catalog.size = fileSize / sizeof(Book);

	for (int i = 0; i < catalog.size; ++i)
	{
		ifs.read((char*)&catalog.books[i], sizeof(Book));
	}

	ifs.close();
}
	
int main()
{
	Catalog catalog{ 3, {
	{"Test", "Test", 10, 10},
	{"Tes2", "Test2", 10, 10},
	{"Tes3t", "Test3", 10, 10},
	} };

	addBookToCatalog({ "4", "4", 1, 1 }, catalog);
	printAllBooks(catalog);

	saveCatalogToFile(Constants::OUTPUT_FILE_NAME, catalog);

	Catalog catalog2;
	readBooksFromFile(Constants::OUTPUT_FILE_NAME, catalog2);
	printAllBooks(catalog2);
}
