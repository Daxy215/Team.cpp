#ifndef MATHA_H
#define MATHA_H

#include <maths/matrix44.h>

class MathA {
public:
	static gef::Matrix44 multiply(const gef::Matrix44& matrix, const gef::Matrix44& other);
};

#endif // !MATHA_H
