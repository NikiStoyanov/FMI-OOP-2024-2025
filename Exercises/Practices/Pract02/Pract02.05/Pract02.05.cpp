#include <iostream>
#include <fstream>

namespace Constants
{
    constexpr char DESTINATION_FILE_NAME[] = "output.txt";
    constexpr char ORIGIN_FILE_NAME[] = "input.txt";
}
struct Point
{
    int X;
    int Y;
};

void readPointFromFile(Point& point, std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
        return;
	}

    ifs >> point.X >> point.Y;
}

Point* readPointArrayFromFile(const char* filename, size_t size)
{
    std::ifstream ifs(filename);

    Point* points = new Point[size];

    if (!ifs.is_open())
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        readPointFromFile(points[i], ifs);
    }

    ifs.close();

    return points;
}

void writePointToFile(const Point& point, std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
        return;
	}

    ofs << point.X << " " << point.Y << '\n';
}

void writePointArrayToFile(const char* filename, const Point* points, size_t size)
{
    std::ofstream ofs(filename);

    if (!ofs.is_open())
    {
        return;
    }

    for (size_t i = 0; i < size; ++i)
    {
        writePointToFile(points[i], ofs);
    }

    ofs.close();
}

struct Triangle
{
    Point A;
    Point B;
    Point C;
};

void readTriangleFromFile(Triangle& triangle, std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
        return;
	}

    readPointFromFile(triangle.A, ifs);
    readPointFromFile(triangle.B, ifs);
    readPointFromFile(triangle.C, ifs);
}

Triangle* readTrianglesArrayFromFile(const char* filename, size_t pointsCount)
{
    std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
        return nullptr;
	}

    size_t trianglesCount = pointsCount / 3;

    Triangle* triangles = new Triangle[trianglesCount];

    for (size_t i = 0; i < trianglesCount; ++i)
    {
        readTriangleFromFile(triangles[i], ifs);
    }

    ifs.close();

    return triangles;
}

int main()
{
    size_t pointsCount = 8;
    Point* points = readPointArrayFromFile(Constants::ORIGIN_FILE_NAME, pointsCount);

    writePointArrayToFile(Constants::DESTINATION_FILE_NAME, points, pointsCount);

    Triangle* triangles = readTrianglesArrayFromFile(Constants::DESTINATION_FILE_NAME, pointsCount);

	delete[] points;
    delete[] triangles;
}