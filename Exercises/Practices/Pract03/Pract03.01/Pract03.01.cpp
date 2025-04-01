#include <iostream>
#include <sstream>

int main()
{
	std::stringstream ss;

	ss << "Integer: " << 42 << ", Double: " << 3.14;

	std::cout << "ss' content: " << ss.str() << std::endl; 

	ss.str("123 45.67 example");

	int x;
	double y;
	char word[1024];

	ss >> x >> y >> word;

	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << word << std::endl;
}