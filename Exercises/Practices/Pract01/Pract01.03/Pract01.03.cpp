#include <iostream>

constexpr int NAME_SIZE = 50;
constexpr int EGN_SIZE = 10;

struct Student
{
    char name[NAME_SIZE];
    char surname[NAME_SIZE];
    char egn[EGN_SIZE];
};

int main()
{
    std::cout << "Hello World!\n";
}