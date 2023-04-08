#ifndef POINT_H
#define POINT_H

class Point
{
private:
	int x;
	int y;
	
public:
	Point();
	Point(int x, int y);
	Point(const Point& point);

	int getX();
	int getY();

	Point& operator=(const Point& point);
	Point& operator+(const Point& point);
	Point& operator-(const Point& point);
	bool operator==(const Point& point);
};

#endif