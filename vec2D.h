#pragma once

class vec2D
{
public:

	// Constructor
	vec2D(double ix=0, double iy=0);

	inline double &x() { return mX; }
	inline double &y() { return mY; }

	 vec2D& operator+(const vec2D &rhs); 
	 vec2D& operator*(const double &rhs); 
	 vec2D& operator/(const double &rhs); 
	 vec2D& operator=(const vec2D &rhs); 
	 vec2D& operator+=(const vec2D &rhs); 

private:
	double mX;
	double mY;
};
