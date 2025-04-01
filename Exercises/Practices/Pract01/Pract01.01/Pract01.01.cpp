#include <iostream>

struct Point
{
    int X;
    int Y;
};

void readPoint(Point& point)
{
    std::cin >> point.X >> point.Y;
}

void printPoint(const Point& point)
{
    std::cout << "(" << point.X << ", " << point.Y << ")";
}

double getDistanceFromPointToStart(const Point& point)
{
    return sqrt(pow(point.X, 2) + pow(point.Y, 2));
}

double getDistanceBetweenTwoPoints(const Point& firstPoint, const Point& secondPoint)
{
    return sqrt(pow(secondPoint.X - firstPoint.X, 2) + pow(secondPoint.Y - firstPoint.Y, 2));
}

int main()
{
    std::cout << "Test";
}