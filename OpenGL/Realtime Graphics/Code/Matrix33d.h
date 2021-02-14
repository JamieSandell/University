#pragma once

#include "Vector3d.h"

class Matrix33d
{
public:
	Matrix33d();
	Matrix33d(double a11, double a12, double a13,
		double a21, double a22, double a23,
		double a31, double a32, double a33);
	Matrix33d(const Vector3d& row1, const Vector3d& row2, const Vector3d& row3);

	const Vector3d& getRow1() const;
	const Vector3d& getRow2() const;
	const Vector3d& getRow3() const;

	Matrix33d scaledBy(double scale) const;
	Matrix33d Add(const Matrix33d &m) const;
	Matrix33d Subtract(const Matrix33d &m) const;

private:
	Vector3d row1, row2, row3;
};
