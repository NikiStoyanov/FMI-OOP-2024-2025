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

struct Triangle
{
    Point A;
    Point B;
    Point C;
};

void readTriangle(Triangle& triangle)
{
    readPoint(triangle.A);
    readPoint(triangle.B);
    readPoint(triangle.C);
}

void printTriangle(const Triangle& triangle)
{
    std::cout << "(";
    printPoint(triangle.A);
    std::cout << ", ";
    printPoint(triangle.B);
    std::cout << ", ";
    printPoint(triangle.C);
    std::cout << ")";
}

double getPerimeter(const Triangle& triangle)
{
    double sideA = getDistanceBetweenTwoPoints(triangle.B, triangle.C);
    double sideB = getDistanceBetweenTwoPoints(triangle.A, triangle.C);
    double sideC = getDistanceBetweenTwoPoints(triangle.A, triangle.B);

    return sideA + sideB + sideC;
}
double getArea(const Triangle& triangle)
{
    double sideA = getDistanceBetweenTwoPoints(triangle.B, triangle.C);
    double sideB = getDistanceBetweenTwoPoints(triangle.A, triangle.C);
    double sideC = getDistanceBetweenTwoPoints(triangle.A, triangle.B);

    double perimeter = sideA + sideB + sideC;
    double halfPerimeter = perimeter / 2;

    return sqrt(halfPerimeter * (halfPerimeter - sideA) * (halfPerimeter - sideB) * (halfPerimeter - sideC));
}

enum class TriangleType
{
    Equilateral,
    Isosceles,
    Scalene
};

TriangleType getTriangleType(const Triangle& triangle)
{
    double sideA = getDistanceBetweenTwoPoints(triangle.B, triangle.C);
    double sideB = getDistanceBetweenTwoPoints(triangle.A, triangle.C);
    double sideC = getDistanceBetweenTwoPoints(triangle.A, triangle.B);

    if (sideA == sideB && sideB == sideC)
    {
        return TriangleType::Equilateral;
    }
    else if (sideA == sideB && sideA != sideC || sideB == sideC && sideB != sideA || sideA == sideC && sideA != sideB)
    {
        return TriangleType::Isosceles;
    }
    else
    {
        return TriangleType::Scalene;
    }
}

Triangle* initializeTriangles(int size)
{
    Triangle* triangles = new Triangle[size];

    for (int i = 0; i < size; i++)
    {
        readTriangle(triangles[i]);
    }

    return triangles;
}

void swapTriangles(Triangle* triangles, unsigned firstPosition, unsigned secondPosition)
{
    Triangle temp = triangles[firstPosition];
    triangles[firstPosition] = triangles[secondPosition];
    triangles[secondPosition] = temp;
}

void sortTriangles(Triangle* triangles, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int current = i;
        for (int j = i + 1; j < size; j++)
        {
            double secondTriangleArea = getArea(triangles[j]);
            double firstTriangleArea = getArea(triangles[current]);

            if (secondTriangleArea < firstTriangleArea)
            {
                current = j;
            }
        }

        swapTriangles(triangles, i, current);
    }
}

void printTriangles(const Triangle* triangles, int size)
{
    for (int i = 0; i < size; i++)
    {
        printTriangle(triangles[i]);
        std::cout << std::endl;
    }
}

int main()
{
    int size;
    std::cin >> size;

    Triangle* triangles = initializeTriangles(size);

    sortTriangles(triangles, size);

    printTriangles(triangles, size);

    delete[] triangles;
}