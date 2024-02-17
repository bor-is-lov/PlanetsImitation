#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Position2D
{
public:
	float x, y;
	// x and y are center positions (rotation applying around it)
	// positive speed == rotation to left
	void Rotate(float x, float y, float speed)
	{
		// from Cartesian coordinate system to polar
		float r = sqrt(pow(this->x - x, 2) + pow(this->y - y, 2)), ang;

		// for ang not to be a NaN
		if (r == 0)
			ang = 0;
		else
			ang = atan((this->y - y) / (this->x - x)) +
			((this->y > y) && (this->x < x) ? M_PI : (this->y < y) && (this->x < x) ? -M_PI : 0);

		// applying rotation
		ang += speed;

		//back to Cartesian
		this->x = x + r * cos(ang);
		this->y = y + r * sin(ang);
	}
};