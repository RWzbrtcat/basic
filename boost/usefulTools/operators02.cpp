#include <iostream>
#include <boost/operators.hpp>
#include <cassert>

class point : boost::totally_ordered<point, boost::additive<point> >
{
	int x, y, z;
public:
	explicit point(int a = 0, int b = 0, int c = 0) : x(a), y(b), z(c) {}
	void print() const
	{
		std::cout << x << ", " << y << ", " << z << std::endl;
	}
	
	// 假定大小关系由 三个坐标值的平方和决定的
	friend bool operator<(const point& l, const point& r)
	{
		return (l.x * l.x + l.y * l.y + l.z * l.z < r.x * r.x + r.y * r.y + r.z * r.z);
	}

	friend bool operator==(const point& l, const point& r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z;
	}

	point& operator+=(const point& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;	
	}

	point& operator-=(const point& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
};


int main()
{
	point p0, p1(1, 2, 3), p2(3, 0, 5);

	assert(p0 < p1);
	assert(p1 <= p2);
	
	p0 += p1;
	p0.print();

	p2 -= p1;
	p2.print();

	return 0;
}
