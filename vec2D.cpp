#include "vec2D.h"

vec2D::vec2D(double ix, double iy)
{
	mX=ix;
	mY=iy;
}

vec2D& vec2D::operator+(const vec2D &rhs)
{
	vec2D *result = new vec2D(mX+rhs.mX,mY+rhs.mY);
	return *result;
}

vec2D& vec2D::operator-(const vec2D &rhs)
{
	vec2D *result = new vec2D(mX-rhs.mX,mY-rhs.mY);
	return *result;
}

vec2D& vec2D::operator=(const vec2D &rhs)
{
	mX = rhs.mX;
	mY = rhs.mY;
	
	return *this;
}

vec2D& vec2D::operator+=(const vec2D &rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	
	return *this;
}

vec2D& vec2D::operator*(const double &rhs)
{
	vec2D *result = new vec2D(mX*rhs,mY*rhs);
	return *result;
}

vec2D& vec2D::operator/(const double &rhs)
{
	vec2D *result = new vec2D(mX/rhs,mY/rhs);
	return *result;
}