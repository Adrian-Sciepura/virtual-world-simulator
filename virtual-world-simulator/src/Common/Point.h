#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
	int x;
	int y;
	
	Point();
	Point(int x, int y);
	Point(const Point& point);

	Point& operator=(const Point& point);
	Point& operator+(const Point& point);
	Point& operator-(const Point& point);
	bool operator==(const Point& point) const;
	friend std::ostream& operator<<(std::ostream& os, const Point& point);
	friend std::istream& operator>>(std::istream& is, Point& point);
};

#endif