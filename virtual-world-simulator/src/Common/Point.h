#ifndef POINT_H
#define POINT_H

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
};

#endif